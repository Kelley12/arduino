/*
  Ultrasonic Sensor
*/
// Ultrasonic variables declaration
const int triggerPin = 12;      // pin connected to Trig Pin in the ultrasonic distance sensor
const int echoPin = 11;         // pin connected to Echo Pin in the ultrasonic distance sensor
const int thresholdLedPin = 13; // pin connected to threshold LED indicator
const int thresholdLevel = 20;  // minimum distance in cm to turn ON the LED

void setup()
{ // setting each digital pin mode
  pinMode(triggerPin,OUTPUT);      // Trigger is an output pin
  pinMode(echoPin,INPUT);          // Echo is an input pin
  pinMode(thresholdLedPin,OUTPUT); // LED is an output pin
  digitalWrite(thresholdLedPin, LOW);
  // initialize serial port
  Serial.begin(9600);
}

void loop()
{
  getSensorDistance();
  delay(1000);
}

// Ultrasonic Sensor Functions
int getSensorDistance()
{
  long duration;
  int cm, inches;
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);   // Trigger pin to HIGH
  delayMicroseconds(10);            // 10us high
  digitalWrite(triggerPin, LOW);    // Trigger pin to LOW
  duration = pulseIn(echoPin,HIGH); // Waits for the echo pin to get high and returns the duration in microseconds
/*
The echo ping travels out and back, so to find the distance of the
object we take half of the distance travelled.  The speed of sound is 340.29 m/s or 29 microseconds per centimeter.
340.29 m/s --> 34029 cm/s --> 29.386 micro seconds/cm
*/
  cm = (duration/2) / 29.386;
  inches = (duration/2) / 74;
  Serial.print("Distance = "); // Output to serial
  Serial.print(cm);
  Serial.println(" cm");
  //  Serial.print(inches);
  //  Serial.print("in, ");

  // checking if threshold level was crossed
  if (cm <= thresholdLevel)
    digitalWrite(thresholdLedPin, HIGH);
  else
    digitalWrite(thresholdLedPin, LOW);
  return cm;
}