#include <AllThingsTalk_LoRaWAN.h>
#include "keys.h"
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#if defined(ARDUINO_SODAQ_ONE)
  #define debugSerial SerialUSB
#elif defined(ARDUINO_AVR_SODAQ_MBILI)
  #define debugSerial Serial
#else
  #error "Unsupported board."
#endif
#define loraSerial Serial1

ABPCredentials credentials(DEVADDR, APPSKEY, NWKSKEY);
LoRaModem modem(loraSerial, debugSerial, credentials);
BinaryPayload payload;


#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme; // I2C
const int flotPin = 20;
const int waterpump = 21;
const int tilt = 4;
int compt = 0;

void sendLora(String payloadString){
    payload.reset();
    payload.add(payloadString);

    modem.send(payload);
}

void sendFake(String p){
  Serial.println("----");
  Serial.println(p);
  Serial.println("---");
}

void setup() {
  Serial.begin(9600);
  Serial.println(F("BME280 test"));
  pinMode(tilt, INPUT);
  pinMode(flotPin, INPUT_PULLUP);
  pinMode(waterpump, OUTPUT);


  if (!bme.begin()) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }
   while ((!debugSerial)) {}

  if (!modem.init()) {
    exit(0);
  }
}

void loop() {
    //compt update
    compt += 1;
    
    //temperature
    char tempString[10];
    dtostrf(bme.readTemperature(), 4, 2, tempString); 
    
    String payloadString = "";
    payloadString += tempString;
    payloadString += "|";
    payloadString += digitalRead(4);
    payloadString += "|";
    payloadString += digitalRead(flotPin);

    if (digitalRead(flotPin) == LOW && digitalRead(tilt) == LOW){
      digitalWrite(waterpump, HIGH);
      delay(10000);
      digitalWrite(waterpump, LOW);
      delay(1000);
    }

    sendFake(payloadString);
    Serial.println(compt);
    if (compt == 5){
      sendLora(payloadString);
      compt = 0;
    }
    delay(5000);
}
