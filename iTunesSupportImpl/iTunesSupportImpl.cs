using System;
using iTunesLib;
using System.Collections.Generic;
using System.IO;
using System.Text;
using System.Text.RegularExpressions;
using System.Runtime.InteropServices;
using System.Diagnostics;
using System.Threading.Tasks;

namespace iTunesSupportImpl
{
    public class iTunesSupportImplWrapper
    {
        private iTunesSupportImplWrapper() {}
        private static iTunesSupportImplWrapper instance;

        public static iTunesSupportImplWrapper getInstance()
        {
            if (instance == null) instance = new iTunesSupportImplWrapper();
            return instance;
        }

        public string artworkRootPath;
        public const int SUCCESS = 1;
        public const int FAIL = 0;
        public static LyricEntry ERROR_ENTRY = new LyricEntry(0, "当前没有正在播放的曲目或曲目歌词标签不是LRC格式...", "");
        
        private IiTunes iTunes;
        private IITTrack currentTrack;
        private bool connectDown;
        private int pid;

        private int updateTimes = 0;

        private string _trackName = "";
        private string _trackArtist = "";
        private string _trackAlbum = "";
        private int _volume = 0;
        private int _progressSecond = 0;
        private int _trackLength = 0;
        private string _progressFormatted = "";
        private LyricEntry _lyric = ERROR_ENTRY;
        private string _cover = "";

        public string trackName { get { return _trackName; } private set { _trackName = value; } }
        public string trackArtist { get { return _trackArtist; } private set { _trackArtist = value; } }
        public string trackAlbum { get { return _trackAlbum; } private set { _trackAlbum = value; } }
        public int volume { get { return _volume; } private set { _volume = value; } }
        public int progressSecond { get { return _progressSecond; } private set { _progressSecond = value; } }
        public int trackLength { get { return _trackLength; } private set { _trackLength = value; } }
        public string progressFormatted { get { return _progressFormatted; } private set { _progressFormatted = value; } }
        public LyricEntry lyric { get { return _lyric; } private set { _lyric = value; } }
        public string cover { get { return _cover; } private set { _cover = value; } }

        private Regex lyricWordRegex = new Regex(@".*\](.*)", RegexOptions.Compiled);
        private Regex lyricTimeRegex = new Regex(@"\[([0-9.:]*)\]+(.*)", RegexOptions.Compiled);
        private double lyricOffset;
        public List<LyricEntry> currentTrackLyrics;

        public int init(string rootpath)
        {
            try
            {
                tryEstablishConnect();
                artworkRootPath = rootpath + "\\artworks\\";
            } catch (Exception)
            {
                return FAIL;
            }
            return SUCCESS;
        }

        public int destroy()
        {
            return SUCCESS;
        }
       
        public void update(int index, string param)
        {
            if (connectDown) tryEstablishConnect();
            if (connectDown) return;
            new Task(() =>
            {
                try
                {
                    updateCurrentTrackAndUpdateLyric();
                    updateTimes++;
                    if (updateTimes >= 1000)
                    {
                        GC.Collect();
                        updateTimes = 0;
                    }

                    updateFields(index, param);
                }
                catch (Exception ex)
                {
                    if (ex is COMException)
                    {
                        connectDown = true;
                        if (index == 2)
                            trackName = getTrackNameInternal();
                    }
                }
            }).Start();
        }

        private void updateFields(int index, string param)
        {
            switch (index)
            {
                case 0: progressSecond = getPlaybackProgressInSecondInternal(); trackLength = getTrackLengthInSecondInternal(); break;
                case 1: progressFormatted = getPlaybackProgressFormattedInternal(); break;
                case 2: trackName = getTrackNameInternal(); processTrackNameRollSetting(param); break;
                case 3: trackArtist = getTrackArtistInternal(); processTrackArtistRollSetting(param); break;
                case 4: trackAlbum = getTrackAlbumInternal(); processTrackAlbumRollSetting(param); break;
                case 5: volume = getVolumeInternal(); break;
                case 6:
                case 7: lyric = getLyricInternal(); break;
                case 8: cover = getArtworkFileNameInternal(); break;
            }
        }

        private void updateCurrentTrackAndUpdateLyric()
        {
            IITTrack prev = currentTrack;
            currentTrack = iTunes.CurrentTrack;
            if (updateTimes >= 100 || (prev != null && currentTrack != null && (currentTrack.Name != prev.Name || currentTrack.Size != prev.Size)))
            {
                updateLyrics();
            }
        }

        private void tryEstablishConnect()
        {
            Process[] processes = Process.GetProcessesByName("iTunes");
            if (processes.Length != 0 && processes[0].Id != pid)
            {
                pid = processes[0].Id;
                createiTunesAsync().Start();
            } else
            {
                connectDown = true;
                trackName = getTrackNameInternal();
            }
        }

        private Task createiTunesAsync()
        {
            return new Task(() =>
            {
                iTunes = new iTunesAppClass();
                connectDown = false;
            });
        }

        private void processRollSetting(string param, out bool roll, out int limit)
        {
            if (param.StartsWith("roll"))
            {
                roll = true;
                if (param.Length > 4)
                {
                    string rollLen = param.Substring(4);
                    int len;
                    bool success = int.TryParse(rollLen, out len);
                    if (success)
                    {
                        limit = len;
                        return;
                    }
                }
                limit = 10;
                return;
            }
            roll = false;
            limit = 10;
        }

        private void processTrackAlbumRollSetting(string param)
        {
            processRollSetting(param, out rollAlbum, out rollAlbumLimit);
        }

        private void processTrackArtistRollSetting(string param)
        {
            processRollSetting(param, out rollArtist, out rollArtistLimit);
        }

        private void processTrackNameRollSetting(string param)
        {
            processRollSetting(param, out rollTrackName, out rollTrackNameLimit);
        }

        public void updateLyrics()
        {
            if (!(currentTrack is IITFileOrCDTrack))
            {
                currentTrackLyrics = null;
                return;
            }

            try
            {
                string lyric = ((IITFileOrCDTrack)currentTrack).Lyrics;
                parseLyric(lyric);
            }
            catch (Exception ex)
            {
                currentTrackLyrics = null;
#if DEBUG
                File.WriteAllText("error.txt", ex.ToString() + "\n");
                File.WriteAllText("error.txt", ex.StackTrace + "\n");
                Console.WriteLine(ex.ToString());
                Console.WriteLine(ex.StackTrace);
#endif
                return;
            }
        }

        private void parseLyric(string lyric)
        {
            if (lyric == null || lyric.Trim().Length == 0)
            {
                currentTrackLyrics = null;
                return;
            }
            List<RawLyricEntry> rawLyrics = new List<RawLyricEntry>();
            using (StreamReader reader = new StreamReader(new MemoryStream(Encoding.UTF8.GetBytes(lyric))))
            {
                currentTrackLyrics = new List<LyricEntry>();
                string line;
                lyricOffset = 0;
                while ((line = reader.ReadLine()) != null)
                {
                    if (!line.StartsWith("[")) continue;
                    if (line.StartsWith("[ti:") ||
                        line.StartsWith("[ar:") ||
                        line.StartsWith("[al:") ||
                        line.StartsWith("[by:")) continue;
                    if (line.StartsWith("[offset:"))
                    {
                        processOffset(line);
                        return;
                    }
                    Match wordMatch = lyricWordRegex.Match(line);
                    string word = wordMatch.Groups[1].Value;

                    if (word.Length == 0) word = " ";

                    MatchCollection timeMatch = lyricTimeRegex.Matches(line);
                    
                    foreach (Match item in timeMatch)
                    {
                        double time = TimeSpan.Parse("00:" + item.Groups[1].Value).TotalSeconds;
                        rawLyrics.Add(new RawLyricEntry(time, word));
                    }
                }
            }
            collapseLyric(rawLyrics);
        }

        private void collapseLyric(List<RawLyricEntry> rawLyrics)
        {
            foreach(RawLyricEntry rawLyricEntry in rawLyrics) {
                foreach (LyricEntry temp in currentTrackLyrics)
                {
                    if (temp.Time == rawLyricEntry.Time)
                    {
                        temp.LyricLine2 = rawLyricEntry.LyricLine;
                        goto outloop;
                    }
                }
                currentTrackLyrics.Add(new LyricEntry(rawLyricEntry.Time, rawLyricEntry.LyricLine, " "));
            outloop:;
            }
            currentTrackLyrics.Sort(new LyricEntry.LyricEntryComparer());
        }

        private void processOffset(string line)
        {
            double.TryParse(line.Substring(line.IndexOf(':') + 1).TrimEnd(']'), out lyricOffset);
        }

        private string processRoll(string original, bool roll, int limit, ref int rollProgress)
        {
            if (!roll) return original;
            if (original.Length < limit) return original;
            string temp = original;
            if (rollProgress > temp.Length)
                rollProgress = 0;
            string final = temp.Substring(rollProgress) + "   " + temp.Substring(0, rollProgress);
            rollProgress++;
            return final;
        }

        int trackNameRollProgress = 0;
        public bool rollTrackName = false;
        public int rollTrackNameLimit = 10;
        private string getTrackNameInternal()
        {
            try
            {
                if (connectDown)
                    return "与iTunes断开连接...";
                if (currentTrack == null)
                    return "当前没有正在播放的曲目...";
                else
                {
                    return processRoll(currentTrack.Name, rollTrackName, rollTrackNameLimit, ref trackNameRollProgress);
                }
            } catch (Exception ex)
            {
#if DEBUG
                File.WriteAllText("error.txt", ex.ToString() + "\n");
                File.WriteAllText("error.txt", ex.StackTrace + "\n");
                Console.WriteLine(ex.ToString());
                Console.WriteLine(ex.StackTrace);
#endif
            }
            return "";
        }
        
        int trackArtistRollProgress = 0;
        public bool rollArtist = false;
        public int rollArtistLimit = 10;
        private string getTrackArtistInternal()
        {
            if (currentTrack == null)
                return "";
            else
            {
                return processRoll(currentTrack.Artist, rollArtist, rollArtistLimit, ref trackArtistRollProgress);
            }
        }

        int trackAlbumRollProgress = 0;
        public bool rollAlbum = false;
        public int rollAlbumLimit = 10;
        private string getTrackAlbumInternal()
        {
            if (currentTrack == null)
                return "";
            else
            {
                return processRoll(currentTrack.Album, rollAlbum, rollAlbumLimit, ref trackAlbumRollProgress);
            }
        }

        private int getPlaybackProgressInSecondInternal()
        {
            if (currentTrack == null)
                return 0;
            else
            {
                return iTunes.PlayerPosition;
            }
        }

        private string getPlaybackProgressFormattedInternal()
        {
            if (currentTrack == null)
                return "00:00";
            else
            {
                TimeSpan time = TimeSpan.FromSeconds(iTunes.PlayerPosition);
                return (time.Minutes < 10 ? "0" : "") + (time.Minutes - time.Seconds / 60) + ":" + time.Seconds;
            }
        }

        private int getTrackLengthInSecondInternal()
        {
            if (currentTrack == null)
                return 0;
            else
            {
                TimeSpan timespan = TimeSpan.Parse("00:" + currentTrack.Time);
                return (int) timespan.TotalSeconds;
            }
        }

        private int getVolumeInternal()
        {
            return iTunes.SoundVolume;
        }

        private LyricEntry getLyricInternal()
        {
            if (currentTrackLyrics == null || currentTrackLyrics.Count == 0)
                return ERROR_ENTRY;
            else
            {
                for (int i = 0; i < currentTrackLyrics.Count; i++)
                {
                    if (currentTrackLyrics[i].Time > ((double)(iTunes.PlayerPositionMS) / 1000 + lyricOffset))
                    {
                        return currentTrackLyrics[i - 1];
                    }
                }
                return currentTrackLyrics[currentTrackLyrics.Count - 1];
            }
        }

        private string getArtworkFileNameInternal()
        {
            try
            {
                if (currentTrack == null)
                    return " ";
                IITArtworkCollection artworks = currentTrack.Artwork;
                if (artworks.Count == 0) return "";
                string suffix;
                switch (artworks[1].Format)
                {
                    case ITArtworkFormat.ITArtworkFormatBMP: suffix = ".bmp"; break;
                    case ITArtworkFormat.ITArtworkFormatJPEG: suffix = ".jpg"; break;
                    case ITArtworkFormat.ITArtworkFormatPNG: suffix = ".png"; break;
                    default: suffix = ".jpg"; break;
                }
                string filepath = artworkRootPath + replaceInvalidChars(currentTrack.Artist) + " - " +
                    replaceInvalidChars(currentTrack.Album) + suffix;
                if (!File.Exists(filepath))
                    artworks[1].SaveArtworkToFile(filepath);
                return filepath;
            }
            catch (Exception)
            { }
            return "";
        }

        private string replaceInvalidChars(string originStr)
        {
            StringBuilder str = new StringBuilder(originStr);
            str.Replace('\\', '_');
            str.Replace('/', '_');
            str.Replace('|', '_');
            str.Replace(':', '_');
            str.Replace('?', '_');
            str.Replace('\"', '_');
            str.Replace('<', '_');
            str.Replace('>', '_');
            str.Replace('*', '_');
            return str.ToString();
        }

        public void playPause()
        {
            new Task(() =>
            {
                try
                {
                    iTunes.PlayPause();
                }
                catch (Exception) { }
            }).Start();
        }

        public void previous()
        {
            new Task(() =>
            {
                try
                {
                    iTunes.BackTrack();
                }
                catch (Exception) { }
            }).Start();
        }

        public void next()
        {
            new Task(() =>
            {
                try
                {
                    iTunes.NextTrack();
                }
                catch (Exception) { }
            }).Start();
        }

        public void volPlus()
        {
            new Task(() =>
            {
                try
                {
                    if (iTunes.SoundVolume > 90)
                        iTunes.SoundVolume = 100;
                    else
                        iTunes.SoundVolume += 10;
                }
                catch (Exception) { }
            }).Start();
        }

        public void volSub()
        {
            new Task(() =>
            {
                try
                {
                    if (iTunes.SoundVolume < 10)
                        iTunes.SoundVolume = 0;
                    else
                        iTunes.SoundVolume -= 10;
                }
                catch (Exception) { }
            }).Start();
        }

        public void activePointer()
        {}
    }
}
