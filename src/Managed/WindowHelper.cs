using System;
using System.Windows;
using System.Windows.Interop;

namespace Managed
{
    internal static class WindowHelper
    {
        internal static void SetOwner(Window window, IntPtr ownerHandle)
        {
            if (window is not null)
            {
                ExceptionGate.Guard(
                        () => new WindowInteropHelper(window) { Owner = ownerHandle },
                        () => new WindowInteropHelper(window) { Owner = IntPtr.Zero }
                    );
            }
        }
    }
}
