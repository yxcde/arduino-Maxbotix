// using the maxsonar quick start http://www.adafruit.com
// http://www.adafruit.com/index.php?main_page=product_info&cPath=35&products_id=172

int sonarPin = 0; //pin connected to analog out on maxsonar sensor
int piezoPin = 9; // specifies the pin connected to piezo from Arduino
int inchesAway; // inches away from the maxsonar sensor

void setup() {
	pinMode(piezoPin, OUTPUT);
//Serial.begin(9600); // starts serial communication, used for debugging or seeing the values
}

void loop() {
inchesAway = analogRead(sonarPin) /2; // reads the maxsonar sensor and divides the value by 2
// approximate distance in inches
//Serial.print(inchesAway); // prints the sensor information from the maxsonar to the serial monitor 
//Serial.println(" inches from sensor");

if (inchesAway < 24) { // if something is 24 inches away then make a 1khz sound
	digitalWrite(piezoPin, HIGH);
	delayMicroseconds(500);
	digitalWrite(piezoPin, LOW);
	delayMicroseconds(500);
}
}