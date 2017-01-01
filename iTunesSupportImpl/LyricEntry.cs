using System;
using System.Collections.Generic;

namespace iTunesSupportImpl
{
    public class LyricEntry
    {
        public double Time { get; set; }
        private string _line1 = "";
        private string _line2 = "";
        public string LyricLine1 {
            get
            {
                return _line1;
            }
            set
            {
                _line1 = value;
            }
        }
        public string LyricLine2 {
            get
            {
                return _line2;
            }
            set
            {
                _line2 = value;
            }
        }

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

        public class LyricEntryComparer : Comparer<LyricEntry>
        {
            public override int Compare(LyricEntry x, LyricEntry y)
            {
                return (int)(x.Time - y.Time);
            }
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
}
