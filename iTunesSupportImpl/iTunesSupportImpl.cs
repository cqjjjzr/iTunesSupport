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
#if DEBUG
                File.AppendAllText("Error.txt", "Entry update()");
#endif
                IITTrack prev = currentTrack;
                currentTrack = iTunes.CurrentTrack;
                if (prev != null && currentTrack != null && (currentTrack.Name != prev.Name || currentTrack.Size != prev.Size))
                    updateLyrics();
#if DEBUG
                File.AppendAllText("Error.txt", "Exit update()");
#endif
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
#if DEBUG
                Console.WriteLine("!(currentTrack is IITFileOrCDTrack)");
#endif
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
                while((line = reader.ReadLine()) != null)
                {
                    if(!line.StartsWith("l1") && !line.StartsWith("l2"))
                    {
                        if (!line.StartsWith("[")) continue;
                        line = "l1" + line;
                    }
                    string linesub = line.Substring(2);
                    if (linesub.StartsWith("[ti:") ||
                        linesub.StartsWith("[ar:") ||
                        linesub.StartsWith("[al:") ||
                        linesub.StartsWith("[by:")) continue;
                    if (linesub.StartsWith("[offset:"))
                    {
                        processOffset(linesub);
                        return;
                    }
                    Match wordMatch = lyricWordRegex.Match(line);
                    string word = wordMatch.Groups[1].Value;

                    if (word.Length == 0) word = " ";

                    MatchCollection timeMatch = lyricTimeRegex.Matches(line);
                    
                    foreach (Match item in timeMatch)
                    {
                        double time = TimeSpan.Parse("00:" + item.Groups[1].Value).TotalSeconds;
                        RawLyricEntry.Line lineNumber = line.StartsWith("l1") ? RawLyricEntry.Line.LINE1 : RawLyricEntry.Line.LINE2;
                        rawLyrics.Add(new RawLyricEntry(time, word, lineNumber));
                    }
                }
            }
            collapseLyric(rawLyrics);
        }

        private void collapseLyric(List<RawLyricEntry> rawLyrics)
        {
            rawLyrics.Sort(new RawLyricComparer());
            foreach(RawLyricEntry rawLyricEntry in rawLyrics) {
                foreach (LyricEntry temp in currentTrackLyrics)
                {
                    if (temp.Time == rawLyricEntry.Time)
                    {
                        if (rawLyricEntry.LineNumber == RawLyricEntry.Line.LINE1)
                        {
                            temp.LyricLine1 = rawLyricEntry.LyricLine;
                        }
                        else
                        {
                            temp.LyricLine2 = rawLyricEntry.LyricLine;
                        }
                        goto outloop;
                    }
                }
                if (rawLyricEntry.LineNumber == RawLyricEntry.Line.LINE1)
                {
                    currentTrackLyrics.Add(new LyricEntry(rawLyricEntry.Time, rawLyricEntry.LyricLine, " "));
                }
                else
                {
                    currentTrackLyrics.Add(new LyricEntry(rawLyricEntry.Time, " ", rawLyricEntry.LyricLine));
                }
            outloop:;
            }
        }

        private void processOffset(string line)
        {
            double.TryParse(line.Substring(line.IndexOf(':') + 1).TrimEnd(']'), out lyricOffset);
        }

        public string getTrackName()
        {
            if (currentTrack == null)
                return "当前没有正在播放的曲目...";
            else
                return currentTrack.Name;
        }

        public string getTrackArtist()
        {
            if (currentTrack == null)
                return "";
            else
                return currentTrack.Artist;
        }

        public string getTrackAlbum()
        {
            if (currentTrack == null)
                return "";
            else
                return currentTrack.Album;
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
                return (time.Minutes - time.Seconds / 60) + ":" + time.Seconds;
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
                    if (currentTrackLyrics[i].Time > (double)iTunes.PlayerPositionMS / 1000)
                    {
                        return currentTrackLyrics[i - 1];
                    }
                }
                return currentTrackLyrics[currentTrackLyrics.Count - 1];
            }
        }

        public void activePointer()
        {}
    }
}
