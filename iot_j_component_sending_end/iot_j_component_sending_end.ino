#define USE_ARDUINO_INTERRUPTS true 
#define BLYNK_PRINT Serial
#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>   
#include <PulseSensorPlayground.h>                                      
PulseSensorPlayground pulseSensor; 
#include <SoftwareSerial.h>
SoftwareSerial EspSerial(0,1); // RX, TX 
 
 
 
char auth[] = "uvqSe9JhxWIH6RMtSGrmN8acWzDslmG0";
char ssid[] = "MANMOHAN";
char pass[] = "ELECTRONICS";
 
const int PulseWire = A1;       
const int LED13 = 13;          
int Threshold = 550;
  
// Your ESP8266 baud rate:
#define ESP8266_BAUD 115200  
ESP8266 wifi(&EspSerial);
 
BlynkTimer timer;
 
 
 
 
 
void sendSensor()
{
  int temp=(analogRead(A0)*0.48828125);
 
 int myBPM = pulseSensor.getBeatsPerMinute(); 
 
 if (pulseSensor.sawStartOfBeat()) {             
 Serial.println("?  A HeartBeat Happened ! "); 
 Blynk.virtualWrite(V5,myBPM);                        
}
  
  Blynk.virtualWrite(V6, temp);
}
 
 
 
void setup()
{   
 
  Serial.begin(9600);          
    
pulseSensor.begin();
  EspSerial.begin(ESP8266_BAUD);
  delay(10);
 
  Blynk.begin(auth, wifi, ssid, pass);
  pulseSensor.analogInput(PulseWire);   
  pulseSensor.blinkOnPulse(LED13);       
  pulseSensor.setThreshold(Threshold); 
  pulseSensor.begin();
  timer.setInterval(1000L, sendSensor);
   
}
 
void loop()
{
  Blynk.run();
  timer.run();
 
}
