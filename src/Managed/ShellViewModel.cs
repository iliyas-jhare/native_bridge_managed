using Prism.Commands;
using Prism.Events;
using Prism.Mvvm;
using System.Collections.ObjectModel;

namespace Managed
{
    public class ShellViewModel : BindableBase
    {
        private ObservableCollection<string> greetings;

        public ShellViewModel(IEventAggregator eventAggregator)
        {
            GreetButtonText = "Greet Native";
            GreetCommand = new DelegateCommand(OnGreet);
            Greetings = new ObservableCollection<string>();

            eventAggregator.GetEvent<GreetManagedEvent>().Subscribe(OnGreetManaged);
        }

        public string GreetButtonText { get; }

        public DelegateCommand GreetCommand { get; }

        public ObservableCollection<string> Greetings
        {
            get => greetings;
            private set => SetProperty(ref greetings, value);
        }

        private void OnGreetManaged(string message) =>
            Greetings.Add(Log.BuildMessage(message, Log.InfoText));

        private void OnGreet()
        {
            var message = "Greetings from Managed";
            Greetings.Add(Log.BuildMessage(message, Log.InfoText));
            Log.Info(message);
        }
    }
}
