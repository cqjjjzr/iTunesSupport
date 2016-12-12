using System;
using iTunesLib;
using System.Collections.Generic;
using System.IO;
using System.Text;
using System.Text.RegularExpressions;
using System.Runtime.InteropServices;
using System.Diagnostics;
using System.Threading;

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
        public LyricEntry ERROR_ENTRY = new LyricEntry(0, "当前没有正在播放的曲目或曲目歌词标签不是LRC格式...", "");
        
        private IiTunes iTunes;
        private IITTrack currentTrack;
        private bool connectDown;
        private int pid;

        private int updateTimes = 0;

        public string trackName { get; private set; }
        public string trackArtist { get; private set; }
        public string trackAlbum { get; private set; }
        public int volume { get; private set; }
        public int progressSecond { get; private set; }
        public int trackLength { get; private set; }
        public string progressFormatted { get; private set; }
        public LyricEntry lyric { get; private set; }
        public string cover { get; private set; }
        
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

        public int update(int index, string param)
        {
            try
            {
                if (connectDown)
                {
                    tryEstablishConnect();
                }

                IITTrack prev = currentTrack;
                currentTrack = iTunes.CurrentTrack;
                if (prev != null && currentTrack != null && (currentTrack.Name != prev.Name || currentTrack.Size != prev.Size))
                {
                    updateLyrics();
                }
                updateTimes++;
                if (updateTimes >= 100)
                {
                    GC.Collect();
                    updateTimes = 0;
                    updateLyrics();
                }

                switch (index)
                {
                    case 0: progressSecond = getPlaybackProgressInSecondInternal(); trackLength = getTrackLengthInSecondInternal(); break;
                    case 1: progressFormatted = getPlaybackProgressFormattedInternal(); break;
                    case 2: trackName = getTrackNameInternal(); processTrackNameRoll(param); break;
                    case 3: trackArtist = getTrackArtistInternal(); processTrackArtistRoll(param); break;
                    case 4: trackAlbum = getTrackAlbumInternal(); processTrackAlbumRoll(param); break;
                    case 5: volume = getVolumeInternal(); break;
                    case 6:
                    case 7: lyric = getLyricInternal(); break;
                    case 8: cover = getArtworkFileNameInternal(); break;
                }
                return SUCCESS;
            } catch (Exception ex)
            {
                if (ex is COMException)
                {
                    connectDown = true;
                    if (index == 2)
                    {
                        trackName = getTrackNameInternal();
                        return SUCCESS;
                    }//DISPLAY CONNECT DOWN MESSAGE
                    return FAIL;
                }
                return FAIL;
            }
        }

        private void tryEstablishConnect()
        {
            Process[] processes = Process.GetProcessesByName("iTunes");
            if (processes.Length != 0 && processes[0].Id != pid)
            {
                pid = processes[0].Id;
                iTunes = new iTunesAppClass();
                connectDown = false;
            } else
            {
                connectDown = true;
                trackName = getTrackNameInternal();
            }
        }

        private void processRoll(string param, out bool roll, out int limit)
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

        private void processTrackAlbumRoll(string param)
        {
            processRoll(param, out rollAlbum, out rollAlbumLimit);
        }

        private void processTrackArtistRoll(string param)
        {
            processRoll(param, out rollArtist, out rollArtistLimit);
        }

        private void processTrackNameRoll(string param)
        {
            processRoll(param, out rollTrackName, out rollTrackNameLimit);
        }

        public int updateLyrics()
        {
            if (!(currentTrack is IITFileOrCDTrack))
            {
                currentTrackLyrics = null;
                return SUCCESS;
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
                return SUCCESS;
            }
            return SUCCESS;
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

        int trackNameRoll = 0;
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
                    if (!rollTrackName) return currentTrack.Name;
                    if (currentTrack.Name.Length < rollTrackNameLimit) return currentTrack.Name;
                    string temp = currentTrack.Name;
                    if (trackNameRoll > temp.Length)
                        trackNameRoll = 0;
                    string final = temp.Substring(trackNameRoll) + "   " + temp.Substring(0, trackNameRoll);
                    trackNameRoll++;
                    return final;
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
        
        int trackArtistRoll = 0;
        public bool rollArtist = false;
        public int rollArtistLimit = 10;
        private string getTrackArtistInternal()
        {
            if (currentTrack == null)
                return "";
            else
            {
                if (!rollArtist) return currentTrack.Artist;
                if (currentTrack.Artist.Length < rollArtistLimit) return currentTrack.Artist;
                string temp = currentTrack.Artist;
                if (trackArtistRoll > temp.Length)
                    trackArtistRoll = 0;
                string final = temp.Substring(trackArtistRoll) + "   " + temp.Substring(0, trackArtistRoll);
                trackArtistRoll++;
                return final;
            }
        }

        int trackAlbumRoll = 0;
        public bool rollAlbum = false;
        public int rollAlbumLimit = 10;
        private string getTrackAlbumInternal()
        {
            if (currentTrack == null)
                return "";
            else
            {
                if (!rollAlbum) return currentTrack.Album;
                if (currentTrack.Album.Length < rollAlbumLimit) return currentTrack.Album;
                string temp = currentTrack.Album;
                if (trackAlbumRoll > temp.Length)
                    trackAlbumRoll = 0;
                string final = temp.Substring(trackAlbumRoll) + "   " + temp.Substring(0, trackAlbumRoll);
                trackAlbumRoll++;
                return final;
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
            try
            {
                iTunes.PlayPause();
            } catch (Exception) { }
        }

        public void previous()
        {
            try
            {
                iTunes.BackTrack();
            }
            catch (Exception) { }
        }

        public void next()
        {
            try
            {
                iTunes.NextTrack();
            }
            catch (Exception) { }
        }

        public void volPlus()
        {
            try
            {
                if (iTunes.SoundVolume > 90)
                    iTunes.SoundVolume = 100;
                else
                    iTunes.SoundVolume += 10;
            }
            catch (Exception) { }
        }

        public void volSub()
        {
            try
            {
                if (iTunes.SoundVolume < 10)
                    iTunes.SoundVolume = 0;
                else
                    iTunes.SoundVolume -= 10;
            }
            catch (Exception) { }
        }

        public void activePointer()
        {}
    }
}
