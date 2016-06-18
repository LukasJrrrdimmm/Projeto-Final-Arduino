#include "PAN3101.h"
// #include "ADNS2051.h"
// #include "ADNS2610.h"
// #include "ADNS2083.h"
#define SCLK 4 // Serial clock pin on the Arduino
#define SDIO 5 // Serial data (I/O) pin on the Arduino
PAN3101 Optical1 = PAN3101(SCLK, SDIO);
// ADNS2051 Optical1 = ADNS2051(SCLK, SDIO);
// ADNS2610 Optical1 = ADNS2610(SCLK, SDIO);
// ADNS2083 Optical1 = ADNS2083(SCLK, SDIO);
signed long x2 = 0;
signed long y2 = 0;
int potPin = A0; 
int pinA = 7;
int ledp3 = 10;
int ledPin = 13;
int ledp2 = 8;
volatile unsigned int val = 0;
int v2 = 500; 
byte b = 0;
byte c = 0;
byte d = 0;
int interrupt = 2;
byte valor = 0;
volatile int interruption = 0;
void setup() {
 pinMode(ledPin, OUTPUT);
 pinMode(pinA, OUTPUT);
 pinMode(ledp3, OUTPUT);
 pinMode(ledp2, OUTPUT);
 pinMode(interrupt, OUTPUT);
 Serial.begin(9600);
}
void Optical(){
    //delay(100);
    x2 += Optical1.dx();
    y2 += Optical1.dy();
    Serial.print("x=");
    Serial.print(x2, DEC);
    Serial.print(" y=");
    Serial.println(y2, DEC);
}
 void functionInterruption(){
   Optical();
   delay(1000);
   Serial.print("Number of Interruption is ");Serial.println(interruption);
   Serial.print("x=");
   Serial.print(x2, DEC);
   Serial.print(" y=");
   Serial.println(y2, DEC);
   digitalWrite(ledp3,HIGH);
   delay(1000);
   digitalWrite(ledp3,LOW);
   delay(1000); 
   interruption++;
    val = analogRead(potPin);
    map(val,0,65535,0,255);
    valor = val;
    if(valor < 100){
      detachInterrupt(0);
      loop();
    }
 } 
void funciona(){
  digitalWrite(pinA,HIGH);
  delay(100);
  val = analogRead(potPin);
  map(val,0,65535,0,255);
  valor = val;
 v2 = analogRead(potPin);
 b = val;
 digitalWrite(ledPin, HIGH);
 //c = v2;
 //d = b + c;
 Serial.print("A = ");
 Serial.print(valor);
 Serial.print(";B = ");
 Serial.print(b);
 Serial.println(";");
 if(valor > 100){
   digitalWrite(pinA, LOW);
   digitalWrite(ledPin,LOW);
   attachInterrupt(0, functionInterruption, LOW);
   digitalWrite(ledp2, HIGH); 
 }else{
   digitalWrite(pinA, HIGH);
   digitalWrite(ledp2, LOW);
 }
}
void loop() {
  funciona();
  Optical();
 }
