#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

const char* ssid = "your network name";
const char* password = "password to the network";

String serverName = "http://dlb.com.pl/api.php";

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println(".");
  }
  
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {

    if(WiFi.status()== WL_CONNECTED){
      WiFiClient client;
      HTTPClient http;

      Serial.print("[HTTP] begin...\n");

      //user -> username registered on dlb.one
      //port -> port number, 3 ports available
      String serverPath = serverName + "?user_name=user&port=1";

      http.begin(client, serverPath.c_str());
      http.setTimeout(2000);  
      

      Serial.print("[HTTP] GET...\n");
      
      int httpResponseCode = http.GET();
      
     if (httpResponseCode > 0) {
      Serial.printf("[HTTP] GET... code: %d\n", httpResponseCode);

      if (httpResponseCode == HTTP_CODE_OK) {
        const String& buff = http.getString();
        //String buff = http.getString();
        Serial.println("received payload:\n<<");
        Serial.println(buff);
        Serial.println(">>");
      }
    } 
    else {
      Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpResponseCode).c_str());
    }
    http.end();
  }
  else {
      Serial.println("WiFi Disconnected");
    }
  delay(5000);
}
