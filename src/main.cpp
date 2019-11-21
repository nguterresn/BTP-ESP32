#include "esp_wpa2.h"
#include <WiFi.h>
#include <Arduino.h>

// WiFi network name and password:
const char* SSID = "eduroam"; // your ssid
#define EAP_ID "up201808899@fe.up.pt"  // your identity
#define EAP_USERNAME "" // your user id or username try email here aswell if not working otherwise blank ""
#define EAP_PASSWORD "" // your password

// Internet domain to request from:
const char * hostDomain = "google.com";
const int hostPort = 80;

const int BUTTON_PIN = 0;
const int LED_PIN = 2;

void setup() {
// Initilize hardware:
Serial.begin(115200);
delay(10);
pinMode(BUTTON_PIN, INPUT_PULLUP);
pinMode(LED_PIN, OUTPUT);

// Connect to the WiFi network (see function below loop)
connectToWiFi(SSID, EAP_ID, EAP_USERNAME, EAP_PASSWORD);

digitalWrite(LED_PIN, LOW); // LED off
Serial.print("Press button 0 to connect to ");
Serial.println(hostDomain);

}

void loop()
{
  if (digitalRead(BUTTON_PIN) == LOW)
  { // Check if button has been pressed
    while (digitalRead(BUTTON_PIN) == LOW)
      ; // Wait for button to be released

    digitalWrite(LED_PIN, HIGH); // Turn on LED
    requestURL(hostDomain, hostPort); // Connect to server
    digitalWrite(LED_PIN, LOW); // Turn off LED
  }
}

void connectToWiFi(const char * ssid, const char * id, const char * username, const char * password)
{
int ledState = 0;
printLine();
Serial.println("Connecting to WiFi network: " + String(ssid) + " ....with User Identity " + String(EAP_ID));

// WPA2 enterprise magic starts here
WiFi.disconnect(true); 
esp_wifi_sta_wpa2_ent_set_identity((uint8_t *)id, strlen(id));
esp_wifi_sta_wpa2_ent_set_username((uint8_t *)username, strlen(username));
esp_wifi_sta_wpa2_ent_set_password((uint8_t *)password, strlen(password));
// esp_wifi_sta_wpa2_ent_enable();
esp_wpa2_config_t config = WPA2_CONFIG_INIT_DEFAULT(); 
esp_wifi_sta_wpa2_ent_enable(&config);
// WPA2 enterprise magic ends here


WiFi.begin(ssid);

while (WiFi.status() != WL_CONNECTED) {
// Blink LED while we're connecting:
digitalWrite(LED_PIN, ledState);
ledState = (ledState + 1) % 2; // Flip ledState
delay(500);
Serial.print(".");
}
Serial.println();
Serial.println("WiFi connected!");
Serial.print("IP address: ");
Serial.println(WiFi.localIP());
}

/* 
* everyhting below this, is just a standard request to a webserver to show that the wifi connection works.
* 
*/ 

void requestURL(const char * host, uint8_t port)
{
  printLine();
  Serial.println("Connecting to domain: " + String(host));

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  if (!client.connect(host, port))
  {
    Serial.println("connection failed");
    return;
  }
  Serial.println("Connected!");
  printLine();

// We now create a URI for the request
String url = "/index.htm";

Serial.print("Requesting URL: ");
Serial.println(url);

  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + String(host) + "\r\n" +
               "Connection: close\r\n\r\n");
  unsigned long timeout = millis();
  while (client.available() == 0) 
  {
    if (millis() - timeout > 5000) 
    {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }

  // Read all the lines of the reply from server and print them to Serial
  while (client.available()) 
  {
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }

  Serial.println();
  Serial.println("closing connection");
  client.stop();
}

void printLine()
{
  Serial.println();
  for (int i=0; i<30; i++)
    Serial.print("-");
  Serial.println();
}