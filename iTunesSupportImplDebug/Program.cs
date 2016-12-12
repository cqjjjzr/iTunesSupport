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
            //wrapper.init();
            //wrapper.update();
            //Console.WriteLine(wrapper.getArtworkFileName("E:\\iTunes\\"));
        }
    }
}
