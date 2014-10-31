/*
* This code reads the Analog Voltage output from the
* LV-MaxSonar sensors
* If you wish for code with averaging, please see
* playground.arduino.cc/Main/MaxSonar
* Please note that we do not recommend using averaging with our sensors.
* Mode and Median filters are recommended.
*/

//NOTE: calibration for cm still lacks accuracy. 18.09.2014

const int anPin1 = 0;
const int anPin2 = 1;
const int sensorTrigger = 2;
//long distance1;
long anVolt, cm, inches, distance1, distance2;
float sensorOn = 0.2;
float sensorDelay = 50;


void setup() {
  Serial.begin(9600);  // sets the serial port to 9600
  pinMode(sensorTrigger, OUTPUT);
  digitalWrite(sensorTrigger, LOW);

}

void read_sensors(){
  /*
  * Scale factor is (Vcc/512) per inch. A 5V supply yields ~9.8mV/in
  * Arduino analog pin goes from 0 to 1024, so the value has to be divided by 2 to get the actual inches
  */
  digitalWrite(sensorTrigger, HIGH);
  //Serial.println("Sensors on");
  distance1 = analogRead(anPin1)/2;
  distance2 = analogRead(anPin2)/2;
  delay(sensorOn);
  digitalWrite(sensorTrigger, LOW);
  //Serial.println("Sensors off");
 
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
  digitalWrite(sensorTrigger, LOW);
  
  read_sensors();
  Serial.print('H'); //Header-symbol
  sendBinaryInt(distance1);
  sendBinaryInt(distance2);
  //print_all();
  delay(sensorDelay); 
}
