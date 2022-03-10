using System;

namespace Managed
{
    internal static class ExceptionGate
    {
        internal static void Gaurd(Action act)
        {
            try { act(); }
            catch (Exception e) { Log.Error(e.Message); }
        }

        internal static void Gaurd(Action act, Action onFailure)
        {
            try { act(); }
            catch (Exception e) { Log.Error(e.Message); onFailure(); }
        }

        internal static void Guard<T>(Func<T> func, Func<T> onFailure)
        {
            try { func(); }
            catch (Exception e) { Log.Error(e.Message); onFailure(); }
        }
    }
}
