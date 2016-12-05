using iTunesSupportImpl;
using System;
using System.Threading;

namespace iTunesSupportImplDebug
{
    class Program
    {
        static void Main(string[] args)
        {
            iTunesSupportImplWrapper wrapper = iTunesSupportImplWrapper.getInstance();
            wrapper.init();
            wrapper.update();
            wrapper.updateLyrics();
            /*foreach(LyricEntry entry in wrapper.currentTrackLyrics) {
                Console.Write(entry);
            }*/
            while(true)
            {
                Console.Write(wrapper.currentTrackLyrics.Count + " "  + wrapper.getLyric());
                Thread.Sleep(50);
            }
        }
    }
}
