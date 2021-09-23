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
using uPLibrary.Networking.M2Mqtt;
using uPLibrary.Networking.M2Mqtt.Messages;

namespace mqttBasic
{
    /// <summary>
    /// https://mosquitto.org/download/ 모스키토 mqtt broker 및 publisher & subscriber
    /// https://www.joinc.co.kr/w/man/12/MQTT/Tutorial#toc mqtt 관련 설명 및 튜토리얼
    /// </summary>
    public partial class MainWindow : Window
    {
        static MqttClient client;

        public MainWindow()
        {
            InitializeComponent();

            string mqttAddress = "127.0.0.1";
            //string mqttTopic = "#";
            //string mqttTopic = "test";
            string mqttTopic = "test/#";
            //string mqttTopic = "test/+/third";
            //string mqttTopic = "test/topic1";
            try
            {
                /*****************************************************************/
                /*mqtt Client & device ID setting                                */
                client = new MqttClient(mqttAddress); //새 mqtt client 생성
                client.MqttMsgPublishReceived += Client_MqttMsgPublishReceived; //mqtt client 에서 MqttMsgPublishReceived 이벤트 발생시 처리할 핸들러 등록
                string clientId_sub = Guid.NewGuid().ToString(); // 유니크 ID 생성

                //client.Connect(clientId_sub, "id", "password"); //브로커 접속에 ID 와 PASSWORD 가 필요한 경우
                client.Connect(clientId_sub); //설정된 정보로 접속

                client.Subscribe(new string[] { mqttTopic }, new byte[] { MqttMsgBase.QOS_LEVEL_AT_MOST_ONCE }); //구독 정보 등록

                txtBlock.Text += "\n";

                if (client.IsConnected)
                {
                    txtBlock.Text += $"starting mqtt on " + mqttAddress +"\n";
                }
                else
                {
                    txtBlock.Text += $"fail to connect mqtt on " + mqttAddress + "\n";
                }
                /*****************************************************************/
            }
            catch
            {
                txtBlock.Text += $"fail to connect mqtt on " + mqttAddress + "\n";
            }
        }

        private void Client_MqttMsgPublishReceived(object sender, MqttMsgPublishEventArgs e)
        {
            string receivedMessage = Encoding.UTF8.GetString(e.Message);
            string receivedTopic = e.Topic;

            Dispatcher.Invoke(delegate {
                txtBlock.Text += receivedTopic + "<< " + receivedMessage + "\n";
            });
            
        }

        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            client.Disconnect();
        }

        private void send_Click(object sender, RoutedEventArgs e)
        {
            client.Publish("test/topic1", Encoding.Default.GetBytes("aaaa test message!"));
        }
    }
}
