using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using calculator;
using Newtonsoft.Json;

namespace calculator
{
    /// <summary>
    /// MainWindow.xaml에 대한 상호 작용 논리
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void numPadClick(object sender, RoutedEventArgs e)
        {
            string clicked = ((Button)sender).Tag.ToString();
            if(num_textbox.Text == "0")
            {
                num_textbox.Text = clicked;
            }
            else
            {
                num_textbox.Text += clicked;
            }
        }

        private void clear_Click(object sender, RoutedEventArgs e)
        {
            num_textbox.Text = "0";
        }

        private void back_Click(object sender, RoutedEventArgs e)
        {
            string tmp = num_textbox.Text;
            num_textbox.Text = tmp.Substring(0,tmp.Length-1);
        }
    }
}
