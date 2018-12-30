/*
   LED Wave funcionality
   Setup
     6 LEDs as output
     2 buttons as input
   Functionality
     Button 1 (testButton) turns LEDs on
     Button 2 (waveButton) causes a wave across the LEDs
     Potentiometer (speedControlPin) controls the speed of the wave
     Speaker (speakerPin) makes a sound for each light change
*/
#include "pitches.h"
// ******************************************
// Global variables Declaration - Mapping physical sensors connections to Arduino PINs
const int testButton= 2;
const int waveButton= 4;
const int speakerPin = 7;
const int speedControlPin = A0;

// Mapping all LEDs physical connections to Arduino PINs
const int ledsPin[]={3,5,6,9,10,11};
boolean ledsOn=false;         // the present state of the LEDs (ON/OFF)
boolean lastButton=LOW;       // the last button state
boolean currentButton=LOW;    // the current button state

//Mario main theme melody
int theme[] = {
  NOTE_E7, NOTE_E7, 0, NOTE_E7,
  0, NOTE_C7, NOTE_E7, 0,
  NOTE_G7, 0, 0,  0,
  NOTE_G6, 0, 0, 0,

  NOTE_C7, 0, 0, NOTE_G6,
  0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6,
  0, NOTE_AS6, NOTE_A6, 0,

  NOTE_G6, NOTE_E7, NOTE_G7,
  NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7,
  NOTE_D7, NOTE_B6, 0, 0,

  NOTE_C7, 0, 0, NOTE_G6,
  0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6,
  0, NOTE_AS6, NOTE_A6, 0,

  NOTE_G6, NOTE_E7, NOTE_G7,
  NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7,
  NOTE_D7, NOTE_B6, 0, 0
};

//Mario main them tempo
int tempo[] = {
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
};
/*
//Underworld melody
int theme[] = {
  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,
  NOTE_AS3, NOTE_AS4, 0,
  0,
  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,
  NOTE_AS3, NOTE_AS4, 0,
  0,
  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
  NOTE_DS3, NOTE_DS4, 0,
  0,
  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
  NOTE_DS3, NOTE_DS4, 0,
  0, NOTE_DS4, NOTE_CS4, NOTE_D4,
  NOTE_CS4, NOTE_DS4,
  NOTE_DS4, NOTE_GS3,
  NOTE_G3, NOTE_CS4,
  NOTE_C4, NOTE_FS4, NOTE_F4, NOTE_E3, NOTE_AS4, NOTE_A4,
  NOTE_GS4, NOTE_DS4, NOTE_B3,
  NOTE_AS3, NOTE_A3, NOTE_GS3,
  0, 0, 0
};
//Underwolrd tempo
int tempo[] = {
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  6, 18, 18, 18,
  6, 6,
  6, 6,
  6, 6,
  18, 18, 18, 18, 18, 18,
  10, 10, 10,
  10, 10, 10,
  3, 3, 3
};
*/
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
  {
    ledsOn =!ledsOn; //toggle the LEDs state
    if(ledsOn)
    {
      melody();
    }
  }
  lastButton = currentButton;
  for (int i=0; i<6; i++)
  {
    digitalWrite(ledsPin[i], ledsOn);
  }
}
// ******************************************
// checking if the wave button was pressed and run animation wave on LEDs
void checkWaveButton()
{
  int speedLevel=analogRead(speedControlPin);
  int notes[] = {
    NOTE_A1, NOTE_A2, NOTE_A3, NOTE_A4, NOTE_A5, NOTE_A6
  };
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
     tone(speakerPin,notes[i],speedLevel);
     delay(speedLevel);
     digitalWrite(ledsPin[i], LOW);
    }
    for(int i=5; i>=0; i--)
    {
     digitalWrite(ledsPin[i], HIGH);
     tone(speakerPin,notes[i],speedLevel);
     delay(speedLevel);
     digitalWrite(ledsPin[i], LOW);
    }
  }
}

void melody() {
    int size = sizeof(theme) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {

      // To calculate the note duration, take one second divided by the note type.
      // e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / tempo[thisNote];

      tone(speakerPin, theme[thisNote], noteDuration);

      // To distinguish the notes, set a minimum time between them. The note's duration + 30% seems to work well:
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      tone(speakerPin, 0, noteDuration);
    }
}