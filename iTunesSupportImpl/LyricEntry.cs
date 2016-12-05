using System;
using System.Collections.Generic;

namespace iTunesSupportImpl
{
    public class LyricEntry
    {
        public double Time { get; set; }
        public string LyricLine1 { get; set; }
        public string LyricLine2 { get; set; }

        public LyricEntry(double time, string lyricLine1, string lyricLine2)
        {
            Time = time;
            LyricLine1 = lyricLine1;
            LyricLine2 = lyricLine2;
        }

        public override string ToString()
        {
            return "[Lyric time=" + Time + " line1=" + LyricLine1 + " line2=" + LyricLine2 + "]\r";
        }
    }
    
    public class RawLyricEntry
    {
        public double Time { get; set; }
        public string LyricLine { get; set; }

        public RawLyricEntry(double time, string lyricLine)
        {
            Time = time;
            LyricLine = lyricLine;
        }
    }

    public class RawLyricComparer : IComparer<RawLyricEntry>
    {
        public int Compare(RawLyricEntry x, RawLyricEntry y)
        {
            return (int) (x.Time - y.Time);
        }
    }
}
