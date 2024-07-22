/*
 * Control shiny hunter by reading the messages on the serial port of arduino
 * 
 *
 */

/* Libraries                */

#include <Servo.h>

/* Signatures               */

// Moves character up and down to find
// a battle
void battleResearch();

// Moves the bracket to press the 
// escape button
void battleEscape();

// Reads serial communication from
// computer to see if a battle was
// found
boolean battleEncountered();

// Reads serial communication from
// computer to see if a shiny
// was found
boolean shinyEncounter();

/* Definition of objects    */

Servo motionAvatar;
Servo escapeButton;

void setup() {
  Serial.begin(9600);

  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  
  motionAvatar.attach(9);
  escapeButton.attach(10);

  escapeButton.write(0);
  motionAvatar.write(0);
  
}

void loop() {
  while(!battleEncountered()) {
    battleResearch();    
  }
  if (shinyEncountered()) {
    while (true) {
      digitalWrite(13, HIGH);
    }
  } else {
    battleEscape();
  }
}

/* Functions                */

void battleResearch() {
  for (int pos = 0; pos <= 180; pos++) {
    motionAvatar.write(pos);
    delay(15); // Delay to allow the servo to reach the position
  }
}

void battleEscape() {
  delay(1000);
  for (int pos = 0; pos <= 180; pos++) {
    escapeButton.write(pos);
    delay(15);
  }
  for (int pos = 180; pos >= 0; pos--) {
    escapeButton.write(pos);
    delay(15);
  }
}

bool battleEncountered() {
  if (Serial.available() > 0) {
    char receivedChar = Serial.read();
    if (receivedChar == 'b') {
      delay(18000);
      return true;
    }
  }
  return false;
}

bool shinyEncountered() {
  if (Serial.available() > 0) {
    char receivedChar = Serial.read();
    if (receivedChar == 's') {
      return true;
    }
  }
  return false;
}
