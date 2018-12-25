/*
   LED Wave funcionality
   Setup
     6 LEDs as output
     2 buttons as input
   Functionality
     Button 1 (testButton) turns LEDs on
     Button 2 (waveButton) causes a wave across the LEDs
     Potentiometer (speedControlPin) controls the speed of the wave
*/
// ******************************************
// Global variables Declaration - Mapping physical sensors connections to Arduino PINs
const int testButton=2;
const int waveButton=4;
const int speedControlPin = A0;

// Mapping all LEDs physical connections to Arduino PINs
const int ledsPin[]={3,5,6,9,10,11};
boolean ledsOn=false;         // the present state of the LEDs (ON/OFF)
boolean lastButton=LOW;       // the last button state
boolean currentButton=LOW;    // the current button state
// ******************************************
void setup()
{
    pinMode (testButton, INPUT); // set test button as input
    pinMode (waveButton, INPUT); // set wave animation button as input
    for (int i=0; i<6; i++)        // set all LEDs to output
      pinMode(ledsPin[i], OUTPUT);
}
// ******************************************
void loop()
{
  checkTestButton();
  checkWaveButton();
}
// ******************************************
// if the button was pressed than wait for the button state to stablize and
boolean debounce(int buttonPIN,boolean last)
{
  boolean current= digitalRead(buttonPIN);
  if (current != last) {
    delay(5); // wait 5ms for button state stablizing
    current = digitalRead(buttonPIN); // read it again
  }
  return current;
}
// ******************************************
// checking if the test button was pressed and turn ON or OFF all LEDs
void checkTestButton()
{
  currentButton = debounce(testButton,lastButton);
  if (currentButton == HIGH && lastButton == LOW) // button was pressed
     ledsOn =!ledsOn; //toggle the LEDs state
   lastButton = currentButton;
   for (int i=0; i<6; i++)
       digitalWrite(ledsPin[i], ledsOn);
}
// ******************************************
// checking if the wave button was pressed and run animation wave on LEDs
void checkWaveButton()
{
  int speedLevel=analogRead(speedControlPin);
  // mapping the relevant ranges from the sensors reading
  speedLevel=map(speedLevel, 0, 1023, 700, 100);
  if(digitalRead(waveButton) == HIGH)// button is pressed
  {
    Serial.println("Running Animation Wave with the following Parameters:");
    Serial.print("Speed:");
    Serial.println(speedLevel);
    
    for(int i=0; i<6; i++)
    {
     digitalWrite(ledsPin[i], HIGH);
     delay(speedLevel);
     digitalWrite(ledsPin[i], LOW);
    }
    for(int i=5; i>=0; i--)
    {
     digitalWrite(ledsPin[i], HIGH);
     delay(speedLevel);
     digitalWrite(ledsPin[i], LOW);
    }
  }
}
