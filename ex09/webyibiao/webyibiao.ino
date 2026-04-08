#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "Redmi";
const char* password = "17343998649";

#define TOUCH_PIN 4

WebServer server(80);

void handleRoot() {
  String html = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>Touch</title>
</head>
<body style="text-align:center;">
<h1>触摸显示</h1>
<div id="val" style="font-size:40px;">0</div>
<br>
<div style="width:80%; height:30px; background:#ddd; margin:0 auto;">
  <div id="bar" style="width:0%; height:100%; background:#2196F3;"></div>
</div>

<script>
function update(){
  fetch('/data').then(r=>r.text()).then(v=>{
    document.getElementById('val').innerText = v;
    let p = 100 - (v/80*100);
    if(p<0)p=0;
    document.getElementById('bar').style.width = p+'%';
  })
}
setInterval(update,100);
</script>
</body>
</html>
)rawliteral";
  server.send(200, "text/html", html);
}

void handleData() {
  int val = touchRead(TOUCH_PIN);
  server.send(200, "text/plain", String(val));
}

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi OK");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/data", handleData);
  server.begin();
}

void loop() {
  server.handleClient();
}
