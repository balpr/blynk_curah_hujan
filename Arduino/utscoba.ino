#define BLYNK_PRINT SwSerial
#include <SoftwareSerial.h>
#include <DHT.h>
SoftwareSerial SwSerial(10, 11); // RX, TX
DHT dht (13, DHT11);

#include <BlynkSimpleStream.h>
#define BLYNK_TEMPLATE_ID "TMPLekuMNQTX"
#define BLYNK_DEVICE_NAME "Curah Hujan"

char auth[] = "1wKCWWHFkruxu4-5fgwrNUQRQifDoY3g";

BlynkTimer timer;

void sendSensor() {
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  int s = 0;
  
  float Vout = analogRead(A0);
  float p = (Vout/float (1023) + 0.095)/0.009;
//  float dist = 1.55;
//  p = p-dist;
  

  if(t >= 26 && t <=27)
  {
    if(h >= 76 && h <=81)
      if(p < 101.03)
        s= 1;
  }
  else if(t >= 27 && t <=28)
  {    
    if(h >= 81 && h <=82)
      if(p < 101.04)
        s= 2;
  }
  else if(t >= 28 && t <=30)
  {
    if(h >= 82 && h <=85)
      if(p > 101.03)
        s= 3;
  }
  else
  {
    s=0;
  }
    

  Blynk.virtualWrite(V0, t);
  Blynk.virtualWrite(V1, s);
  Blynk.virtualWrite(V2, h);
  Blynk.virtualWrite(V3, p);
}

void setup() {
  // put your setup code here, to run once:
  SwSerial.begin(9600);
  Serial.begin(9600);
  dht.begin();
  Blynk.begin(Serial, auth);
  timer.setInterval(1000L, sendSensor);
}

void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();
  timer.run();
}
