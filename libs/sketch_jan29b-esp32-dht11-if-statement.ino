/*
  * ESP32 Web Server - STATION Mode
*/
//===============================================================
// Load Libraries
//===============================================================

#include <WiFi.h> //WiFi library
#include <WebServer.h>

#include <ESPmDNS.h>

#include <dht11.h>
dht11 DHT;
#define DHT11_PIN 4

//===============================================================
// Initialization
//===============================================================

// enter your SSID and PASSWORD
const char* ssid = "ua123";  // Enter WiFi SSID here
const char* password = "123456788";  //Enter WiFi Password here

WebServer server(80);  // port 80 is default website port

//===============================================================
// Setup Function
//===============================================================

void setup() {
  Serial.begin(115200);
  Serial.println("Connecting to ");
  Serial.println(ssid);

  // set ESP32 as web server
  WiFi.mode(WIFI_STA);   
  
  // connect to your WiFi modem with SSID & PASSWORD
  WiFi.begin(ssid, password);  

  // wait for ESP32 connected to WiFi network
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected successfully");
  Serial.print("Your ESP32 IP: ");
  
  // display "ESP32 IP Address" at Serial Monitor
  Serial.println(WiFi.localIP());  

  // set up mDNS responder:
  // may use "esp32.local" instead of "ESP32 IP Address"
  if (MDNS.begin("esp32")) {
    Serial.println("MDNS responder started");
  }
 
  // attach handles
  server.on("/", handle_root);
  
  // type "ipaddress/inline" OR "esp32.local/inline" at browser
  server.on("/inline", []() { 
    server.send(200, "text/plain", "this works as well");
  });
 
  // start web server
  server.begin();
  Serial.println("HTTP server started");
  delay(100); 
} // end of setup function

//===============================================================
// Loop Function
//===============================================================

void loop() {
  server.handleClient();
} //end of loop function

//===============================================================
// Other Functions
//===============================================================

// HTML & CSS contents which display on web server
String SendHTML(float Temperaturestat,float Humiditystat){
  int sec = millis() / 1000;
  int min = sec / 60;
  int hr = min / 60;
  //Serial.print(sec);
int  chk = DHT.read(DHT11_PIN);    // READ DATA
    Serial.print(" ");
  String warn;
  if (DHT.temperature>27)
  {
    warn = "danger"; 
    Serial.println(warn);
    //digitalWrite(pinGreen,LOW);
    //digitalWrite(pinRed,HIGH);
  } else
  {
    warn = "normal";
    Serial.println(warn);
    //digitalWrite(pinGreen,HIGH);
    //digitalWrite(pinRed,LOW);
  }
  
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>ESP32 Weather Report</title>\n";
  ptr +="<meta http-equiv=refresh content=5>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;}\n";
  ptr +="p {font-size: 24px;color: #444444;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<div id=\"webpage\">\n";
  ptr += "Server Up Time: <b>";
  ptr += hr;
  ptr += "h:";
  ptr += min % 60;
  ptr += "m:";
  ptr +=  sec % 60;
  ptr += "s </b>\n";
  ptr +="<h1>ESP32 Weather Report</h1>\n";
  ptr +="<p>Temperature: ";
  ptr +=DHT.temperature;
  ptr +=" &#730;C";
  ptr +="<p>Humidity: ";
  ptr +=DHT.humidity;
  ptr +="%</p>";
  ptr +="<br>&#128522;</br>";
  ptr += warn;
  
  ptr +="</div>\n";
  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}


// Handle root url (/)
void handle_root() {
  float a=1.2;
  float b=21.19;
  //server.send(200, "text/html", HTML(a,b));
  server.send(200, "text/html", SendHTML(a,b)); 
}

/*
 *  modified on 25 MAy 2019
  by Mohammadreza Akbari @ Electropeak
  https://electropeak.com/learn

  https://lastminuteengineers.com/esp32-dht11-dht22-web-server-tutorial/

led https://lastminuteengineers.com/creating-esp8266-web-server-arduino-ide/w
 */
