using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace DU.LTPNer
{
    class Program
    {
        //[DllImport("segmentor.dll")]
        //extern static

        [DllImport("DU.LTPNer.Lib.dll")]
        public extern static int ltp_ner_wrapper(byte[] data, ref StringBuilder result);

        
       static void Main(string[] args)
       {
            //Console.OutputEncoding = Encoding.UTF8;
            //   var inputTsvPath = @"D:\DataInputs&Outputs\DU\DownloadCleanedArticles_20171231.tsv";
            string testWB = "中国#N#国际#N#广播#N#电台#N#创办#N#于#N#1941年#N#12月#N#3日#N#。\0";
            StringBuilder ner_result = new StringBuilder();
            ltp_ner_wrapper(Encoding.UTF8.GetBytes(testWB), ref ner_result);
            //Console.WriteLine(ltp_ner_wrapper(Encoding.UTF8.GetBytes(testWB), ref ner_result));
            string result = ner_result.ToString();
            byte[] rawutf8 = Encoding.Default.GetBytes(ner_result.ToString());
            string unicodeStr = Encoding.UTF8.GetString(rawutf8);
            Console.WriteLine(unicodeStr);
            Console.ReadKey();

            Console.WriteLine(LTPNerWrapper.GetNerResult(testWB));
            Console.ReadKey();
        }

    }
    
}
