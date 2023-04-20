
#define BLYNK_TEMPLATE_ID "TMPLhXCPLb7P"
#define BLYNK_DEVICE_NAME "plant watering system"
#define BLYNK_AUTH_TOKEN "C3eji_8lTqVjf6N0sy78w4eKGHNG_cHW"
#define BLYNK_FIRMWARE_VERSION        "0.1.0"

#define BLYNK_PRINT Serial
#define BLYNK_DEBUG
#include <Blynk.h>

#define APP_DEBUG

#define USE_NODE_MCU_BOARD
BlynkTimer timer;

#include "BlynkEdgent.h"
#define soil A0
#define waterPump 7
WidgetLED pump(V1);

float soilLevel, soilR; 

/********Blynk lcd*******/
WidgetLCD vLcd(V2);

void sendSensor()
{
  readSoil();
  if(soilLevel>=80)
  {    
    digitalWrite(waterPump, LOW);
    vLcd.print(0,0,"Water Pump OFF");
    pump.off();
  }
  
 if(soilLevel<20)
  {    
    digitalWrite(waterPump, HIGH);
    vLcd.print(0,0, "Water Pump ON ");
    pump.on();
  }
}
void readSoil()
{
  soilR=analogRead(soil);  
  Serial.println(soilR);
  soilLevel=map(soilR, 510, 1023, 200,0); // ajust soil level here
  Serial.println(soilLevel);
  Blynk.virtualWrite(V0, soilLevel);
  delay(1000);
}
void setup()
{
  Serial.begin(9600);
  pinMode(waterPump, OUTPUT);
  digitalWrite(waterPump, LOW);
  BlynkEdgent.begin();
  delay(2000); 
   timer.setInterval(1000L, sendSensor); 
}

void loop() 
{
  BlynkEdgent.run();
  timer.run(); 
sendSensor();
}
