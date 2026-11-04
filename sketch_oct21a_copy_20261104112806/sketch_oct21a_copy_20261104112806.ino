#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <TM1638.h>

TM1638 aaa(D2,D1,D0);

//SoftAP
const char* ssid="김승혁";
const char* password="12341234";

ESP8266WebServer server(80);//1. 서버 객체(인스턴스) 생성

void setup() {
 Serial.begin(9600);
 WiFi.softAP(ssid,password);
 Serial.println();
 Serial.print("AP IP Address");
 Serial.println(WiFi.softAPIP());

 server.on("/",handleRoot);//2. 핸들러 등록
 server.begin();//3.웹 서버 시작

}

void loop() {
  server.handleClient();//4. 주기적인 웹 서버 기능 수행
}

const char MAIN_page[] PROGMEM = R"rawliteral(
  <html>
	<head>
    <meta charset='utf-8'>
		<style>
			#div1{
				height:20%;
				background-color:lightgreen;
				display:flex;
				justify-content:center;
				align-items:center;
				font-size:4em;
				color:green;
			}
			#div2{
				height:60%;
				background-color:lightblue;
				text-align:center;
			}
			#div3{
				height:16%;
				background-color:orange;
				text-align:center;
				font-size:2em;
				color:blue;
			}
			#txt1{
				width:60%;
				font-size:3em;
				background-color:red;
				color:white;
				text-align:center;
			}
			#sd1{
				width:60%;
			}
		</style>
		<script>
			function slider( )
			{
				document.getElementById('txt1').value = document.getElementById('sd1').value;
        fndvalue = document.getElementById('sd1').value;

        fetch('/?FND=' + fndvalue, {method: 'GET'});
			}
		</script>
	</head>
	<body>
		<div id='div1'>슬라이더 제어</div>
		<div id='div2'>
			<br><br><br>
			<input type='text' id='txt1'>
			<br><br><br>
			<br><br><br>
			<br><br><br>
			<input type='range' id='sd1' oninput='slider();'min='0'max='10000000'>
		</div>
		<div id='div3'>한국폴리텍대학<br>메카트로닉스과<br>김승혁</div>
	</body>
</html>
// 이곳에 여러분이 작성한 html 코드를 직접 넣습니다.

)rawliteral";

void handleRoot()
{
  if(server.hasArg("FND")){
    String fnd = server.arg("FND");
    int fndvalue = fnd.toInt();//문자열을 숫자로 바꾼다
    aaa.setDisplayToDecNumber(fndvalue,0);
  }
  server.send(200,"text/html",MAIN_page);
}
