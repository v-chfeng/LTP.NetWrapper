using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace DU.LTPNer
{
    public class LTPNerWrapper
    {
        [DllImport("DU.LTPNer.Lib.dll")]
        public extern static int ltp_ner_wrapper(byte[] data, ref StringBuilder result);

        /// <summary>
        /// wordBreakerStr. eg 中国#N#国际#N#广播#N#电台#N#创办#N#于#N#1941年#N#12月#N#3日#N#。\0
        /// \0 must be contained.
        /// return 中国||B-i;国际||N-ii
        /// </summary>
        /// <param name="wordBreakerStr"></param>
        /// <returns></returns>
        public static string GetNerResult(string wordBreakerStr)
        {
            StringBuilder ner_result = new StringBuilder();
            int resultcode;

            try
            {
                resultcode = ltp_ner_wrapper(Encoding.UTF8.GetBytes(wordBreakerStr), ref ner_result);
            }
            catch
            {
                return string.Empty;
            }

            if (resultcode == -1)
                return string.Empty;
            
            string result = ner_result.ToString();
            byte[] rawutf8 = Encoding.Default.GetBytes(ner_result.ToString());
            string unicodeStr = Encoding.UTF8.GetString(rawutf8);
            return string.IsNullOrEmpty(unicodeStr) ? string.Empty : unicodeStr;
        }
    }
}
