using System;
using iTunesLib;
using System.Collections.Generic;
using System.IO;
using System.Text;
using System.Text.RegularExpressions;

namespace iTunesSupportImpl
{
    public class iTunesSupportImplWrapper
    {
        private iTunesSupportImplWrapper() {
            init();
        }
        private static iTunesSupportImplWrapper instance;

        public static iTunesSupportImplWrapper getInstance()
        {
            if (instance == null) instance = new iTunesSupportImplWrapper();
            return instance;
        }
        public const int SUCCESS = 1;
        public const int FAIL = 0;
        public LyricEntry ERROR_ENTRY = new LyricEntry(0, "当前没有正在播放的曲目或曲目歌词标签不是LRC格式...", "");

        private Regex lyricWordRegex = new Regex(@".*\](.*)", RegexOptions.Compiled);
        private Regex lyricTimeRegex = new Regex(@"\[([0-9.:]*)\]+(.*)", RegexOptions.Compiled);

        private IiTunes iTunes;
        private IITTrack currentTrack;

        private int updateTimes = 0;

        //private IITTrack currentLyricsDictionaryTrack;
        private double lyricOffset;
        public List<LyricEntry> currentTrackLyrics;
        public int init()
        {
            try
            {
                iTunes = new iTunesAppClass();
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

        public int update()
        {
            try
            {
                IITTrack prev = currentTrack;
                currentTrack = iTunes.CurrentTrack;
                if (prev != null && currentTrack != null && (currentTrack.Name != prev.Name || currentTrack.Size != prev.Size))
                    updateLyrics();
                updateTimes++;
                if (updateTimes >= 100)
                {
                    updateTimes = 0;
                    updateLyrics();
                }
                return SUCCESS;
            } catch (Exception ex)
            {
                Console.WriteLine(ex.ToString());
                Console.WriteLine(ex.StackTrace);
                return FAIL;
            }
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
        public int rollTrackLimit = 10;
        public string getTrackName()
        {
            try
            {
                if (currentTrack == null)
                    return "当前没有正在播放的曲目...";
                else
                {
                    if (!rollTrackName) return currentTrack.Name;
                    if (currentTrack.Name.Length < rollTrackLimit) return currentTrack.Name;
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
        public string getTrackArtist()
        {
            try
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

        int trackAlbumRoll = 0;
        public bool rollAlbum = false;
        public int rollAlbumLimit = 10;
        public string getTrackAlbum()
        {
            try
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

        public int getPlaybackProgressInSecond()
        {
            if (currentTrack == null)
                return 0;
            else
            {
                return iTunes.PlayerPosition;
            }
        }

        public string getPlaybackProgressFormatted()
        {
            if (currentTrack == null)
                return "00:00";
            else
            {
                TimeSpan time = TimeSpan.FromSeconds(iTunes.PlayerPosition);
                return (time.Minutes < 10 ? "0" : "") + (time.Minutes - time.Seconds / 60) + ":" + time.Seconds;
            }
        }

        public int getTrackLengthInSecond()
        {
            if (currentTrack == null)
                return 0;
            else
            {
                TimeSpan timespan = TimeSpan.Parse("00:" + currentTrack.Time);
                return (int) timespan.TotalSeconds;
            }
        }

        public int getVolume()
        {
            return iTunes.SoundVolume;
        }

        public LyricEntry getLyric()
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

        public string getArtworkFileName(string rootpath)
        {
            try
            {
                if (currentTrack == null)
                    return "";
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
                string filepath = rootpath + replaceInvalidChars(currentTrack.Artist) + " - " +
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
            iTunes.PlayPause();
        }

        public void previous()
        {
            iTunes.BackTrack();
        }

        public void next()
        {
            iTunes.NextTrack();
        }

        public void volPlus()
        {
            if (iTunes.SoundVolume > 90)
                iTunes.SoundVolume = 100;
            else
                iTunes.SoundVolume += 10;
        }

        public void volSub()
        {
            if (iTunes.SoundVolume < 10)
                iTunes.SoundVolume = 0;
            else
                iTunes.SoundVolume -= 10;
        }

        public void activePointer()
        {}
    }
}
