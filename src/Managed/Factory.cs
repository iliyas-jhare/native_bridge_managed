using Prism.Events;
using System;
using System.Windows;
using System.Windows.Threading;

namespace Managed
{
    public interface IFactory
    {
        void Show();
    }

    internal class Factory : IFactory
    {
        private readonly IManagedCallbacks callbacks;
        private readonly IEventAggregator eventAggregator;
        private readonly Dispatcher dispatcher;

        public Factory(IManagedCallbacks callbacks,
            IEventAggregator eventAggregator,
            Dispatcher dispatcher)
        {
            this.callbacks = callbacks;
            this.eventAggregator = eventAggregator;
            this.dispatcher = dispatcher;
        }

        public void Show()
        {
            Log.Init(callbacks.Log);
            CreateShellWindow().Show();
            Log.Info("Window opened.");
        }

        private Window CreateShellWindow()
        {
            var viewModel = new ShellViewModel(eventAggregator);
            var window = new Shell(viewModel);
            WindowHelper.SetOwner(window, callbacks.OwnerHandle());
            window.Closed += OnClosed;
            return window;
        }

        private static void OnClosed(object sender, EventArgs e) =>
            Log.Info("Window closed.");
    }
}
