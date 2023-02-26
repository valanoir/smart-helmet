#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <dht.h>
#define dht_apin A5//temp
const int BUZZER_PIN = 3; //buzzer to arduino pin 9
const int BUTTON_PIN = 7;
String data;

dht DHT;
TinyGPSPlus gps;

static const int RXPin = 4, TXPin = 5;
static const uint32_t GPSBaud = 9600;
int pres_pin = A2;//pressure
int gas_pin = A0;//Gas
SoftwareSerial BTserial(10, 11); //RX, TX Bluetooth
SoftwareSerial ss(RXPin, TXPin);//GPS

void setup() 
{
  Serial.begin(9600);
  BTserial.begin(9600);
  ss.begin(GPSBaud);
  pinMode(BUTTON_PIN, INPUT_PULLUP); // set arduino pin to input pull-up mode
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() 
{
  int buttonState = digitalRead(BUTTON_PIN);
  while (ss.available() > 0)
    if (gps.encode(ss.read()))
      displayInfo();
    
  if (buttonState == LOW){
  tone(BUZZER_PIN, 50); // Send 1KHz sound signal...
  delay(4000);        // ...for 1 sec
  // noTone(BUZZER_PIN);     // Stop sound...
  // delay(1000);        // ...for 1sec
}
else{
    noTone(BUZZER_PIN);
  }
if (buttonState == LOW){
    data="EMERGENCY SOS";
  }
  else {
    data="SAFE";
  }

  DHT.read11(dht_apin);
  int pressure_value = analogRead(pres_pin);
  int air_value = analogRead(gas_pin);
  if(pressure_value > 350 ){
    tone(BUZZER_PIN, 50);
     delay(2000);        // ...for 1 sec
  noTone(BUZZER_PIN);     // Stop sound...
  delay(1000);  
    
  }else{
    noTone(BUZZER_PIN);
  }

  BTserial.print(DHT.temperature);
  BTserial.print("C ,");

  BTserial.print(pressure_value);
  BTserial.print("P ,");

  BTserial.print(DHT.humidity);
  BTserial.print(",");

  BTserial.print(air_value);
  BTserial.print("Pm ,");

  BTserial.print("12.9716");
  BTserial.print(F(","));

  BTserial.print("77.5946");
  BTserial.print(F(","));

  BTserial.print(data);
  BTserial.print(";");

  Serial.print(DHT.temperature);
  Serial.println("C");

  Serial.print(pressure_value);
  Serial.println("P");

  Serial.print(DHT.humidity);
  Serial.println("");

  Serial.print(air_value);
  Serial.println("Pm");

  Serial.print(data);
  Serial.println("");
  
  
  
  delay(20);
}
void displayInfo()
{
  Serial.print("LAt");
  Serial.println(gps.location.lat(), 6);
 
  Serial.print("Longitude");
  Serial.println(gps.location.lng(), 6);
  delay(1000);
}
