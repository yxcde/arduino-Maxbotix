/*
Test code for the Arduino Uno
Written by Tom Bonar for testing
Sensors being used for this code are the MB10X0 from MaxBotix
All PW inputs are coded in this for simplicity.
Remove the comments to use the additional sensor inputs
*/
const int pwPin1 = 9;
long pulse1, sensor, mm, cm, inches;

void setup () {
  Serial.begin(9600);
  pinMode(pwPin1, INPUT);
}

void read_sensor (){
  sensor = pulseIn(pwPin1, HIGH);
  mm = sensor;      //Takes the pulse width and tells Arduino it is equal to millimeters
  inches = mm/25.4;   //Takes mm and converts it to inches
  
  //other way to calculate inches
  //pulse1 = pulseIn(pwPin1, HIGH);
  //sensor = pulse1/147;
}

//This section of code is if you want to print the range readings to your computer too remove this from the code put /* before the code section and */ after the code
void printall(){         
  Serial.print("S1");
  Serial.print(" ");
  Serial.print(mm);
  Serial.println(" ");
}

void loop () {
  read_sensor();
  printall();
  delay(50); // This delay time changes by 50 for every sensor in the chain.  For 5 sensors this will be 250
}
