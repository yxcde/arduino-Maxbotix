// written at: luckylarry.co.uk editied for MaxBotix LV-MaxSonar-EZ1
// very easy Theremin

// setup pins and variables
int pwPin = 7;                                  // MaxSonar PW pin
int speakerPin = 6;                             // Speaker output pin
unsigned long pulseTime = 0;                    // stores the pulse in Micro Seconds
unsigned long distance = 0;                     // variable for storing the distance (cm) we'll use distance as a switch for the speaker
unsigned long soundDelay = 0;                   // variable for storing the deay needed for the pitch


//setup
void setup() {

  pinMode(speakerPin, OUTPUT);                  // sets pin 6 as output
  pinMode(pwPin, INPUT);                      // set PW pin 7 as input
  Serial.begin(9600);

 } 

// execute
void loop() {
  pulseTime = pulseIn(pwPin, HIGH);           // Look for a return pulse, it should be high as the pulse goes low-high-low
  distance = (pulseTime/147)*2.54;              // convert the pulse into distance (cm)
  soundDelay = pulseTime/3;                     // alter this variable to alter the pitch of the sound emitted

  // make the sound.
  // check the distance, if over 30cm make no sound
  if (distance < 40) {
  digitalWrite(speakerPin, HIGH);
  delayMicroseconds(soundDelay);
  digitalWrite(speakerPin, LOW);
  delayMicroseconds(soundDelay);
 }

  Serial.print(distance);
  Serial.print(" ");
  Serial.println("cm");
}