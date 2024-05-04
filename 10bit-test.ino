#include "Bitcoin.h"
#ifdef ESP32
#include <WiFi.h>
#include <AsyncTCP.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#endif
#include <ESPAsyncWebServer.h>

AsyncWebServer server(80);
int led = 2;
int i2 =0;
String priv0 = "PrivateKey : ";
byte secret[32];
String target = "1LeBZP5QCwwgXRtmVUvTVrraqPUokyLHqe";
void setup() {
  Serial.begin(115200);
  Serial.println("Initializing...");
  WiFi.mode(WIFI_AP);
  WiFi.softAP("Worker_01", "00000000"); // or NULL password
  Serial.println(WiFi.softAPIP());
  pinMode(led,OUTPUT);
  server.on("/key", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200,"text/plain",priv0);
  });
  server.begin();
  Serial.println("Setup done!");

}

void loop() {
if(i2 > 100){
  digitalWrite(led, HIGH);
  i2++;
  if(i2 == 128){
    i2 = 0;
    }
  }else{
    i2++;
    digitalWrite(led, LOW);
    }
gen_10_priv(secret);
PrivateKey0090 pk121(secret);
if (pk121.legacyAddress() == target){
    for(int i=0;i < 32;i++){
    priv0 = priv0 + String(secret[i],HEX)+",";
  }
  Serial.print("hahahahahahah :");
  Serial.println(pk121.legacyAddress());

  
  for(;;){
    digitalWrite(led, HIGH);
    delay(200);
    digitalWrite(led, LOW);
    delay(200);
    }
}
}



void gen_10_priv(byte* secret){
  secret[31] = random(256);//1
  secret[30] = random(2,4);//2

}
