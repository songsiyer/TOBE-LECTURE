using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Web.Script.Serialization;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using Microsoft.Web.WebView2.Wpf;
using System.Net;

namespace RandomLunch
{
    /// <summary>
    /// https://apis.map.kakao.com/ 에서 API 관련된 내용 확인
    /// https://github.com/cefsharp/CefSharp/tree/master/CefSharp.Wpf.Example 에서 cefSharp 크롬브라우저 사용하려 할떄 관련 샘플 확인
    /// https://devstarsj.github.io/development/2016/06/11/CSharp.NewtonJSON/ newtonsoft JSON 사용법
    /// https://developer.microsoft.com/en-us/microsoft-edge/webview2/#download-section microsoft edge webview2 사용시 필요한 런타임
    /// </summary>
    public partial class MainWindow : Window
    {
        object[] arr;
        public MainWindow()
        {
            InitializeComponent();

            int a = 3;
            string html = "kakaoMap.html";
            string curDir = Directory.GetCurrentDirectory();
            mapBrowser.Navigate(new Uri(String.Format("file:///{0}/" + html, curDir)));
            mapBrowser2.Source = new Uri(String.Format("file:///{0}/" + html, curDir));
        }

        public void Search(string area) // 지역 검색
        {
            string site = "https://dapi.kakao.com/v2/local/search/address.json";
            string query = string.Format("{0}?query={1}", site, area);

            WebRequest request = WebRequest.Create(query); // 요청 생성. 
            string api_key = "90d9791d2ef73b7bae5812948708898f"; // Rest API 인증키 입력.
            string header = "KakaoAK " + api_key;

            request.Headers.Add("Authorization", header); // HTTP 헤더 "Authorization" 에 header 값 설정. 
            WebResponse response = request.GetResponse(); // 요청을 보내고 응답 객체를 받는다. 

            Stream stream = response.GetResponseStream(); // 응답객체의 결과물
            StreamReader reader = new StreamReader(stream, Encoding.UTF8);
            String json = reader.ReadToEnd(); // JOSN 포멧 문자열


            // json 형식으로 처리하기
            JObject jobject = JObject.Parse(json);
            Console.WriteLine(jobject["documents"]);
            JArray jArray = JArray.Parse(jobject["documents"].ToString());
            Console.WriteLine("위도 :" + jArray[0]["x"] + "경도 :" + jArray[0]["y"]);
            arr = new object[] { jArray[0]["y"].ToString(), jArray[0]["x"].ToString() }; // 위도, 경도


            // document 형식으로 처리하기
            JavaScriptSerializer js = new JavaScriptSerializer(); // (Reference 에 System.Web.Extensions.dll 을 추가해야한다)
            var dob = js.Deserialize<dynamic>(json);
            var docs = dob["documents"];
            object[] buf = docs;
            int length = buf.Length;
            for (int i = 0; i < length; i++)
            {
                string address_name = docs[i]["address_name"];
                double x = double.Parse(docs[i]["x"]);
                double y = double.Parse(docs[i]["y"]);
            }
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            Search("경기도 성남시 중원구 성남동 3438");
            mapBrowser2.ExecuteScriptAsync("panTo('" + arr [0]+ "','" + arr[1] + "')");
            mapBrowser.InvokeScript("panTo", arr);
        }
    }
}
