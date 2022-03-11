using Prism.Events;
using System.Threading;
using System.Windows.Threading;

namespace Managed
{
    public static class ManagedBridge
    {
        private static IEventAggregator eventAggregator = default;
        private static Dispatcher dispatcher = default;

        public static void Show(IManagedCallbacks callbacks) =>
            ExceptionGate.Gaurd(() =>
            {
                var thread = new Thread(new ThreadStart(() =>
                {
                    eventAggregator = new EventAggregator();
                    dispatcher = Dispatcher.CurrentDispatcher;
                    new Factory(callbacks, eventAggregator, dispatcher).Show();
                    Dispatcher.Run();
                }));
                thread.SetApartmentState(ApartmentState.STA);
                thread.Start();
            });

        public static void Greet(string message) =>
            ExceptionGate.Gaurd(() =>
                dispatcher.Invoke(() =>
                    { eventAggregator.GetEvent<GreetManagedEvent>().Publish(message); }));
    }
}
