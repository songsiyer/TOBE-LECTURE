// Updated by XamlIntelliSenseFileGenerator 2021-09-02 오후 5:46:42
#pragma checksum "..\..\MainWindow.xaml" "{8829d00f-11b8-4213-878b-770e8597ac16}" "8AE987C5E33C7E677BDDB3AD66B70456B9688F766241D2491C654ED78A0C395E"
//------------------------------------------------------------------------------
// <auto-generated>
//     이 코드는 도구를 사용하여 생성되었습니다.
//     런타임 버전:4.0.30319.42000
//
//     파일 내용을 변경하면 잘못된 동작이 발생할 수 있으며, 코드를 다시 생성하면
//     이러한 변경 내용이 손실됩니다.
// </auto-generated>
//------------------------------------------------------------------------------

using System;
using System.Diagnostics;
using System.Windows;
using System.Windows.Automation;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Ink;
using System.Windows.Input;
using System.Windows.Markup;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Media.Effects;
using System.Windows.Media.Imaging;
using System.Windows.Media.Media3D;
using System.Windows.Media.TextFormatting;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Shell;
using calculator;


namespace calculator
{


    /// <summary>
    /// MainWindow
    /// </summary>
    public partial class MainWindow : System.Windows.Window, System.Windows.Markup.IComponentConnector
    {


#line 10 "..\..\MainWindow.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.TextBox num_textbox;

#line default
#line hidden


#line 12 "..\..\MainWindow.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button num7;

#line default
#line hidden


#line 13 "..\..\MainWindow.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button num4;

#line default
#line hidden


#line 14 "..\..\MainWindow.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button num1;

#line default
#line hidden


#line 17 "..\..\MainWindow.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button num8;

#line default
#line hidden


#line 18 "..\..\MainWindow.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button num5;

#line default
#line hidden


#line 19 "..\..\MainWindow.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button num2;

#line default
#line hidden


#line 20 "..\..\MainWindow.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button num0;

#line default
#line hidden


#line 35 "..\..\MainWindow.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button num9;

#line default
#line hidden


#line 36 "..\..\MainWindow.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button num6;

#line default
#line hidden


#line 37 "..\..\MainWindow.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button num3;

#line default
#line hidden

        private bool _contentLoaded;

        /// <summary>
        /// InitializeComponent
        /// </summary>
        [System.Diagnostics.DebuggerNonUserCodeAttribute()]
        [System.CodeDom.Compiler.GeneratedCodeAttribute("PresentationBuildTasks", "4.0.0.0")]
        public void InitializeComponent()
        {
            if (_contentLoaded)
            {
                return;
            }
            _contentLoaded = true;
            System.Uri resourceLocater = new System.Uri("/calculator;component/mainwindow.xaml", System.UriKind.Relative);

#line 1 "..\..\MainWindow.xaml"
            System.Windows.Application.LoadComponent(this, resourceLocater);

#line default
#line hidden
        }

        [System.Diagnostics.DebuggerNonUserCodeAttribute()]
        [System.CodeDom.Compiler.GeneratedCodeAttribute("PresentationBuildTasks", "4.0.0.0")]
        [System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Never)]
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Design", "CA1033:InterfaceMethodsShouldBeCallableByChildTypes")]
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Maintainability", "CA1502:AvoidExcessiveComplexity")]
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1800:DoNotCastUnnecessarily")]
        void System.Windows.Markup.IComponentConnector.Connect(int connectionId, object target)
        {
            switch (connectionId)
            {
                case 1:
                    this.num_textbox = ((System.Windows.Controls.TextBox)(target));
                    return;
                case 2:
                    this.num7 = ((System.Windows.Controls.Button)(target));

#line 12 "..\..\MainWindow.xaml"
                    this.num7.Click += new System.Windows.RoutedEventHandler(this.numPadClick);

#line default
#line hidden
                    return;
                case 3:
                    this.num4 = ((System.Windows.Controls.Button)(target));

#line 13 "..\..\MainWindow.xaml"
                    this.num4.Click += new System.Windows.RoutedEventHandler(this.numPadClick);

#line default
#line hidden
                    return;
                case 4:
                    this.num1 = ((System.Windows.Controls.Button)(target));

#line 14 "..\..\MainWindow.xaml"
                    this.num1.Click += new System.Windows.RoutedEventHandler(this.numPadClick);

#line default
#line hidden
                    return;
                case 5:
                    this.num8 = ((System.Windows.Controls.Button)(target));

#line 17 "..\..\MainWindow.xaml"
                    this.num8.Click += new System.Windows.RoutedEventHandler(this.numPadClick);

#line default
#line hidden
                    return;
                case 6:
                    this.num5 = ((System.Windows.Controls.Button)(target));

#line 18 "..\..\MainWindow.xaml"
                    this.num5.Click += new System.Windows.RoutedEventHandler(this.numPadClick);

#line default
#line hidden
                    return;
                case 7:
                    this.num2 = ((System.Windows.Controls.Button)(target));

#line 19 "..\..\MainWindow.xaml"
                    this.num2.Click += new System.Windows.RoutedEventHandler(this.numPadClick);

#line default
#line hidden
                    return;
                case 8:
                    this.num0 = ((System.Windows.Controls.Button)(target));

#line 20 "..\..\MainWindow.xaml"
                    this.num0.Click += new System.Windows.RoutedEventHandler(this.numPadClick);

#line default
#line hidden
                    return;
                case 9:
                    this.num9 = ((System.Windows.Controls.Button)(target));

#line 35 "..\..\MainWindow.xaml"
                    this.num9.Click += new System.Windows.RoutedEventHandler(this.numPadClick);

#line default
#line hidden
                    return;
                case 10:
                    this.num6 = ((System.Windows.Controls.Button)(target));

#line 36 "..\..\MainWindow.xaml"
                    this.num6.Click += new System.Windows.RoutedEventHandler(this.numPadClick);

#line default
#line hidden
                    return;
                case 11:
                    this.num3 = ((System.Windows.Controls.Button)(target));

#line 37 "..\..\MainWindow.xaml"
                    this.num3.Click += new System.Windows.RoutedEventHandler(this.numPadClick);

#line default
#line hidden
                    return;
            }
            this._contentLoaded = true;
        }

        internal System.Windows.Controls.Button clear;
        internal System.Windows.Controls.Button back;
    }
}
