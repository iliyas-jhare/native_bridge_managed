using System;

namespace Managed
{
    internal static class Log
    {
        private static Action<string> log = s => { };

        internal static string InfoText = "INFO";
        internal static string ErrorText = "ERROR";

        internal static void Init(Action<string> native_log)
        {
            log = native_log;
        }

        internal static string BuildMessage(string message, string category) =>
            $"[{category}] {message}";

        internal static void Info(string message) => log(BuildMessage(message, InfoText));

        internal static void Error(string message) => log(BuildMessage(message, ErrorText));
    }
}
