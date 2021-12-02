#include <ArduinoHttpClient.h>
#include <ArduinoJson.h>
#include <WiFiNINA.h>

char ssid[] = "SoteloNetwork";
char password[] = "1turr1aga";

int status = WL_IDLE_STATUS;

char server[] = "http://3f95-189-217-99-41.ngrok.io";    //Always modify when re-run ngrok

WiFiClient client;

void setup(){
  Serial.begin(9600);

  while (status != WL_CONNECTED) {
    Serial.println("Attempting to connect to Network: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid,password);
    delay (1000);
  }

  Serial.print("Connected to SSID: ");
  Serial.println(WiFi.SSID());
  IPAddress ip = WiFi.localIP();
  IPAddress gateway = WiFi.gatewayIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

}

void loop(){

  DynamicJsonDocument doc1(1024);
  DynamicJsonDocument doc2(1024);
  DynamicJsonDocument doc3(1024);
  
  float sensor1 = analogRead(A0);
  float voltaje1 = sensor1*(5.0 /1023.0);
  float rs1 = 1000*( (5-voltaje1) / voltaje1);
  float y1 = -0.00005*rs1 + 0.5963;
  
  float sensor2 = analogRead(A1);
  float voltaje2 = sensor1*(5.0 /1023.0);
  float rs2 = 1000*( (5-voltaje2) / voltaje2);
  float y2 = -0.0003*rs2 + 0.9696;
  
  float sensor3 = analogRead(A2);
  float voltaje3 = sensor1*(5.0 /1023.0);
  float rs3 = 1000*( (5-voltaje3) / voltaje3);
  float y3 = -0.0012*rs3 + 1.9068

  doc1["valor"] = y1;
  doc1["idDispositivo"] = "1";
  doc1["idParametro"] = 1;

  doc2["valor"] = y2;
  doc2["idDispositivo"] = "2";
  doc2["idParametro"] = 2;

  doc3["valor"] = y3;
  doc3["idDispositivo"] = "3";
  doc3["idParametro"] = 3;

  String postData1;
  String postData2;
  String postData3;

  serializeJson(doc1, postData1);
  serializeJson(doc2, postData2);
  serializeJson(doc3, postData3);

   if (client.connect(server, 80)) {
    client.println("POST /mediciones/agregar HTTP/1.1");
    client.println("Host: 3f95-189-217-99-41.ngrok.io");
    client.println("Content-Type: application/json");
    client.print("Content-Length: ");
    client.println(postData1.length());
    client.println();
    client.print(postData1);
   }

   if (client.connect(server, 80)) {
    client.println("POST /mediciones/agregar HTTP/1.1");
    client.println("Host: 3f95-189-217-99-41.ngrok.io");
    client.println("Content-Type: application/json");
    client.print("Content-Length: ");
    client.println(postData2.length());
    client.println();
    client.print(postData2);
   }

   if (client.connect(server, 80)) {
    client.println("POST /mediciones/agregar HTTP/1.1");
    client.println("Host: 3f95-189-217-99-41.ngrok.io");
    client.println("Content-Type: application/json");
    client.print("Content-Length: ");
    client.println(postData3.length());
    client.println();
    client.print(postData3);
  }

  if (client.connected()) {
    client.stop();
  }
  
  Serial.println(postData1);
  Serial.println(postData2);
  Serial.println(postData3);

  delay(200);
  
}
