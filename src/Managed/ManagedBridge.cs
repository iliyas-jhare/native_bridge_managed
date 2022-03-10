using Prism.Events;
using System;
using System.Windows.Threading;

namespace Managed
{
    public static class ManagedBridge
    {
        private static IEventAggregator eventAggregator = default;
        private static Dispatcher dispatcher = default;

        [STAThread]
        public static void Show(IManagedCallbacks callbacks) =>
            ExceptionGate.Gaurd(() =>
            {
                eventAggregator = new EventAggregator();
                dispatcher = Dispatcher.CurrentDispatcher;
                new Factory(callbacks, eventAggregator, dispatcher).Show();
                Dispatcher.Run();
            });

        public static void Greet(string message) =>
            ExceptionGate.Gaurd(() =>
                dispatcher.Invoke(() =>
                    { eventAggregator.GetEvent<GreetManagedEvent>().Publish(message); }));
    }
}
