using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Mocktail_Arduino_WPF_Prototype
{
    public partial class MainWindow : Window
    {
        public List<Mocktail> mocktails = new List<Mocktail>()
        {
            new Mocktail() {Name = "Test1", Ingredients = {Outputs.Sirup, Outputs.Water}, Amounts = {30, 30}},
            new Mocktail() {Name = "Test2", Ingredients = {Outputs.Sirup, Outputs.Water, Outputs.Juice}, Amounts = {20,60,10}},
            new Mocktail() {Name = "Test3", Ingredients = {Outputs.Juice, Outputs.Beer, Outputs.Coffee}, Amounts = {20,60,10}},
        };
        public const float cupSize = 250;
        public int flowSpeed = 50; // Milliliters per second
        public bool isPouring;
        public MainWindow()
        {
            InitializeComponent();
            InitializeListBox();
            Cup.Maximum = cupSize;
            CupLabel.Content = 0;
        }

        private async void Pour(int index, int time)
        {
            int delay = 100;
            isPouring = true;
            SolidColorBrush onColor = new SolidColorBrush(Colors.Green);
            SolidColorBrush offColor = new SolidColorBrush(Colors.White);
            switch (index)
            {
                case 0:
                    First.Background = onColor;
                    break;
                case 1:
                    Second.Background = onColor;
                    break;
                case 2:
                    Third.Background = onColor;
                    break;
                case 3:
                    Fourth.Background = onColor;
                    break;
                case 4:
                    Fifth.Background = onColor;
                    break;
                case 5:
                    Sixth.Background = onColor;
                    break;
                case 6:
                    Seventh.Background = onColor;
                    break;
                case 7:
                    Eighth.Background = onColor;
                    break;
            }

            Cup.Value += Math.Round((double)flowSpeed / delay * 10);
            CupLabel.Content = Math.Round(Cup.Value);

            if (time > delay)
            {
                await Task.Delay(delay);
                Pour(index, time - delay);
            }
            else
            {
                isPouring = false;

                First.Background = offColor;
                Second.Background = offColor;
                Third.Background = offColor;
                Fourth.Background = offColor;
                Fifth.Background = offColor;
                Sixth.Background = offColor;
                Seventh.Background = offColor;
                Eighth.Background = offColor;
            }
        }

        private void InitializeListBox()
        {
            for (int i = 0; i < mocktails.Count; i++)
            {
                Mocktails_Listbox.Items.Add(CreateListItem(mocktails[i].Name, mocktails[i].ImagePath, mocktails[i].Ingredients));
            }
        }

        private ListBoxItem CreateListItem(string name, string imagePath, List<Outputs> ingredients)
        {
            ListBoxItem item = new ListBoxItem();

            item.Height = 40;
            item.Width = double.NaN;
            item.BorderThickness = new Thickness(1);
            item.BorderBrush = new SolidColorBrush(Color.FromArgb(255,171,173,179));
            item.Margin = new Thickness(0,0,0,1);

            StackPanel mainStack = new StackPanel();

            mainStack.Width = double.NaN;
            mainStack.Height = double.NaN;

            mainStack.HorizontalAlignment = HorizontalAlignment.Left;
            mainStack.VerticalAlignment = VerticalAlignment.Center;
            mainStack.Orientation = Orientation.Horizontal;

            Image image = new Image();

            image.Width = 30;
            image.Height = 30;

            if (imagePath != null)
            {
                BitmapImage source = new BitmapImage();
                source.BeginInit();
                source.UriSource = new Uri(imagePath);
                source.EndInit();

                image.Source = source;
            }

            mainStack.Children.Add(image);

            Rectangle rectangle = new Rectangle();

            rectangle.Margin = new Thickness(5,0,5,0);
            rectangle.Height = 26;
            rectangle.Width = 1;
            rectangle.Fill = Brushes.Black;

            mainStack.Children.Add(rectangle);

            StackPanel labelStack = new StackPanel();

            Label title = new Label();

            title.Width = double.NaN;
            title.Height = 16;
            title.Content = name;
            title.FontSize = 14;
            title.Padding = new Thickness(0);

            labelStack.Children.Add(title);

            Label desc = new Label();

            desc.Width = double.NaN;
            desc.Height = 15;
            desc.Margin = new Thickness(0,0,0,3);
            for (int i = 0; i < ingredients.Count; i++)
            {
                desc.Content += ingredients[i].ToString();
                if (i != ingredients.Count - 1)
                {
                    desc.Content += ", ";
                }
            }
            desc.FontSize = 11;
            desc.Padding = new Thickness(0);

            labelStack.Children.Add(desc);

            mainStack.Children.Add(labelStack);

            item.Content = mainStack;

            return item;
        }

        private async void PourButton_Click(object sender, RoutedEventArgs e)
        {
            if (Mocktails_Listbox.SelectedItem != null && Cup.Value == 0)
            {
                Mocktail mocktail = mocktails[Mocktails_Listbox.SelectedIndex];
                PourButton.IsEnabled = false;
                ResetButton.IsEnabled = false;
                for (int i = 0; i < mocktail.Ingredients.Count; i++)
                {
                    Outputs[] values = (Outputs[])Enum.GetValues(typeof(Outputs));

                    int index = Array.IndexOf(values, mocktail.Ingredients[i]);
                    Pour(index, (int)Math.Round((double)mocktail.Amounts[i] * 1000) / flowSpeed);
                    while (isPouring) await Task.Delay(10);
                    await Task.Delay(1000);
                }
                PourButton.IsEnabled = true;
                ResetButton.IsEnabled = true;
            }
        }

        private void ResetButton_Click(object sender, RoutedEventArgs e)
        {
            Cup.Value = 0;
            CupLabel.Content = 0;
        }
    }

    public enum Outputs
    {
        Sirup,
        Juice,
        Water,
        Soda,
        Alcohol,
        Beer,
        Coffee,
        Cocoa
    }
}