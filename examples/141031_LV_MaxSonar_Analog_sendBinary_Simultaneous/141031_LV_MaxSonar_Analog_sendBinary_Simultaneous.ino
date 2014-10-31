/*
* This code reads the Analog Voltage output from the
* LV-MaxSonar sensors
* If you wish for code with averaging, please see
* playground.arduino.cc/Main/MaxSonar
* Please note that we do not recommend using averaging with our sensors.
* Mode and Median filters are recommended.
*/

//NOTE: calibration for cm still lacks accuracy. 18.09.2014


#include <ctype.h>

#define bit9600Delay 84  
#define halfBit9600Delay 42
#define bit4800Delay 188 
#define halfBit4800Delay 94 

byte rx = 6;
byte tx = 7;

const int anPin1 = 0;
const int anPin2 = 1;
const int sensorTrigger = 2;
//long distance1;
long anVolt, cm, inches, distance1, distance2;
float sensorOn = 0.2;
float sensorDelay = 50;


void setup() {
  Serial.begin(9600);  // sets the serial port to 9600
  pinMode(rx,INPUT);
  pinMode(tx,OUTPUT);
  digitalWrite(tx,HIGH);

  pinMode(sensorTrigger, OUTPUT);
}

void read_sensors(){
  /*
  * Scale factor is (Vcc/512) per inch. A 5V supply yields ~9.8mV/in
  * Arduino analog pin goes from 0 to 1024, so the value has to be divided by 2 to get the actual inches
  */

  //digitalWrite(sensorTrigger, HIGH);
  //Serial.println("Sensors on");
  SWprint();
  distance1 = analogRead(anPin1)/2;
  distance2 = analogRead(anPin2)/2;
  delay(sensorOn);
  //digitalWrite(sensorTrigger, LOW);
  //Serial.println("Sensors off");
}

void SWprint()
{
  byte mask;
  //startbit
  digitalWrite(tx,LOW);
  delayMicroseconds(bit9600Delay);
  for (mask = 0x01; mask>0; mask <<= 1) {
    if (mask){ // choose bit
     digitalWrite(tx,HIGH); // send 1
   }
   else{
     digitalWrite(tx,LOW); // send 0
   }
   delayMicroseconds(bit9600Delay);
 }
  //stop bit
  digitalWrite(tx, HIGH);
  delayMicroseconds(bit9600Delay);
}

void print_all(){
	Serial.print("S1");
  Serial.print(" ");
  Serial.print(distance1);
  Serial.print(" ");
  Serial.print("centimeters");
  Serial.print(" ");
  Serial.print("|");
  Serial.print(" ");
  Serial.print("S2");
  Serial.print(" ");
  Serial.print(distance2);
  Serial.print(" ");
  Serial.print("centimeters");
  Serial.println();
}

void sendBinaryInt(int data){
  Serial.write(lowByte(data));
  Serial.write(highByte(data));
}

void sendBinaryLong(long value){
  int temp = value & 0xFFFF;
  sendBinaryInt(temp);
  temp = value >> 16;
  sendBinaryInt(temp);
}

void loop() {

  read_sensors();
  Serial.print('H'); //Header-symbol
  sendBinaryInt(distance1);
  sendBinaryInt(distance2);
  //print_all();
  delay(sensorDelay); 
}
