using System;

namespace Managed
{
    public interface IManagedCallbacks
    {
        void Log(string message);
        IntPtr OwnerHandle();
    }

    internal class EmptyManagedCallbacks : IManagedCallbacks
    {
        public void Log(string message) => throw new System.NotImplementedException();

        public IntPtr OwnerHandle() => throw new NotImplementedException();
    }
}
