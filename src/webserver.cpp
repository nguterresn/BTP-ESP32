#include <WiFi.h>
#include <ESPAsyncWebServer.h>
  
const char* ssid = "yourNetworkName";
const char* password =  "pass";
  
AsyncWebServer server(80);
  
void setup(){
   
  Serial.begin(115200);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  
  Serial.println(WiFi.localIP());
  
  server.on("/test", HTTP_GET, [](AsyncWebServerRequest *request){
    Serial.println("Request received");
    request->send(200, "text/plain", "Hello from server");
  });
  
  server.begin();
}
  
void loop(){}