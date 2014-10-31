//  Sonar to binary Serial-communication

// inspired by "very easy Theremin" written at: luckylarry.co.uk editied for MaxBotix LV-MaxSonar-EZ1
//



// setup pins and variables
int pwPin1 = 6;                                 // MaxSonar PW pin
int pwPin2 = 7;     
int speakerPin1 = 4;                            // Speaker output pin (not if using toneAC-Library)
int speakerPin2 = 8;
unsigned long pulseTime1 = 0;                    // stores the pulse in Micro Seconds
unsigned long pulseTime2 = 0;
unsigned long distance1 = 0;                     // variable for storing the distance (cm) we'll use distance as a switch for the speaker
unsigned long distance2 = 0;
unsigned long soundDelay = 0;                   // variable for storing the delay needed for the pitch


//setup
void setup() {

  pinMode(speakerPin1, OUTPUT);                // sets pin 4 as output
  pinMode(speakerPin2, OUTPUT);                // sets pin 8 as output
  pinMode(pwPin1, INPUT);                      // set PW pin 6 as input
  pinMode(pwPin2, INPUT);                      // set PW pin 7 as input
  Serial.begin(9600);

} 

// execute
void loop() {
  Serial.print('H'); //Header-Symbol

  pulseTime1 = pulseIn(pwPin1, HIGH);           // Look for a return pulse, it should be high as the pulse goes low-high-low
  distance1 = (pulseTime1/147)*2.54;            // convert the pulse into distance (cm)
  pulseTime2 = pulseIn(pwPin2, HIGH);           // Look for a return pulse, it should be high as the pulse goes low-high-low
  distance2 = (pulseTime2/147)*2.54;              // convert the pulse into distance (cm)
    
  soundDelay = pulseTime1/3;                   // alter this variable to alter the pitch of the sound emitted  

  // make the sound.
  // check the distance, if over 30cm make no sound
  if (distance1 < 60) {
    tone(speakerPin1, pulseTime1); 
  }

 /* if (distance2 < 60) {
    tone(speakerPin2, pulseTime2);
  }
  */
   sendBinaryInt(pulseTime1);
   sendBinaryInt(pulseTime2);
/*
  Serial.print(pulseTime);
  Serial.print(" ");
  Serial.print("Hz");
  Serial.print(" ");
  Serial.print("|");
  Serial.print(" ");
  Serial.print(distance);
  Serial.print(" ");
  Serial.println("cm");
  */
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