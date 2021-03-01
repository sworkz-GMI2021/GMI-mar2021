//https://lastminuteengineers.com/esp8266-dht11-dht22-web-server-tutorial/
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <dht11.h>

dht11 DHT;
#define DHT11_PIN D4

/*Put your SSID & Password*/
const char* ssid = "YES";  // Enter SSID here
const char* password = "a2856245";  //Enter Password here

ESP8266WebServer server(80);

float Temperature;
float Humidity;

void setup() {
  Serial.begin(115200);
  delay(100);
  Serial.println("Interface DHT11 NodeMCU Using Web Server");
  Serial.println("Connecting to ");
  Serial.println(ssid);

  //connect to your local wi-fi network
  WiFi.begin(ssid, password);

  //check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");  Serial.println(WiFi.localIP());

  server.on("/", handle_OnConnect);
  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("HTTP server started");

}
void loop() {
  
  server.handleClient();
  
}

void handle_OnConnect() {
int chk = DHT.read(DHT11_PIN);    // READ DATA

 Temperature = DHT.temperature; // Gets the values of the temperature
  Humidity = DHT.humidity; // Gets the values of the humidity 
  Serial.print(Temperature);
  Serial.print("&deg;C, ");
  Serial.print(Humidity);
  Serial.println("%");
  server.send(200, "text/html", SendHTML(Temperature,Humidity)); 
}

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}

String SendHTML(float Temperaturestat,float Humiditystat){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>NodeMCU 8266 Weather Report</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;}\n";
  ptr +="p {font-size: 24px;color: #444444;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<div id=\"webpage\">\n";
  ptr +="<h1>NodeMCU Weather Report at PMJ</h1>\n";
  
  ptr +="<p>Temperature: ";
  ptr +=(int)Temperaturestat;
  ptr +="&deg;C</p>";
  ptr +="<p>Humidity: ";
  ptr +=(int)Humiditystat;
  ptr +="%</p>";
  
  ptr +="</div>\n";
  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;

}
