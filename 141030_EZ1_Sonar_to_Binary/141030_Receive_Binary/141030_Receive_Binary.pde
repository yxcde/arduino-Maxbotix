/*
 * ReceiveBinaryData_P
 *
 * portIndex must be set to the port connected to the Arduino
 */
import processing.serial.*;

Serial myPort;        // Create object from Serial class
short portIndex = 2;  // select the com port, 0 is the first port

char HEADER = 'H';
int value1, value2;         // Data received from the serial port

void setup()
{
  size(600, 600);
  // Open whatever serial port is connected to Arduino.
  String portName = Serial.list()[portIndex];
  println(Serial.list());
  println(" Connecting to -> " + Serial.list()[portIndex]);
  myPort = new Serial(this, Serial.list()[portIndex], 9600);
}

void draw()
{
  // read the header and two binary *(16 bit) integers:
  if ( myPort.available() >= 5)  // If at least 5 bytes are available,
  {
    if( myPort.read() == HEADER) // is this the header
    {
      value1 = myPort.read();                 // read the lowByte
      value1 =  myPort.read() * 256 + value1; // add the highByte

      value2 = myPort.read();                 // read the lowByte
      value2 =  myPort.read() * 256 + value2; // add the highByte
      
      println("Message received: " + (value1*2.54) + "," + (value2*2.54));
     //println("Message received: " + value1);
    }
  }
  background(0);             // Set background to white
  fill(255);                     // set fill to black
  distance(value1, value2);
 
}

void distance(int val1, int val2){
  float distance1 = (val1)*2.54;
  float distance2 = (val2)*2.54;
  rect(0, height, width/2, -distance1);
  rect(width/2, height, width, -distance2); 
}