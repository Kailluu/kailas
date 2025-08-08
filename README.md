#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

// DFPlayer Mini pins
static const uint8_t PIN_MP3_TX = 2; // Connects to DFPlayer's RX
static const uint8_t PIN_MP3_RX = 3; // Connects to DFPlayer's TX
SoftwareSerial softwareSerial(PIN_MP3_RX, PIN_MP3_TX);

// IR sensor pins
const int irEntryPin = 4;  // Entry sensor
const int irExitPin  = 5;  // Exit sensor

// Player object
DFRobotDFPlayerMini player;

void setup() {
  Serial.begin(9600);
  softwareSerial.begin(9600);

  pinMode(irEntryPin, INPUT);
  pinMode(irExitPin, INPUT);

  if (player.begin(softwareSerial)) {
    Serial.println("DFPlayer Mini connected.");
    player.volume(25); // Volume 0–30
  } else {
    Serial.println("DFPlayer Mini connection failed!");
    while (true);
  }
}

void loop() {
  // Read IR sensors
  bool entryDetected = digitalRead(irEntryPin) == LOW; // LOW when object detected
  bool exitDetected  = digitalRead(irExitPin)  == LOW;

  if (entryDetected) {
    Serial.println("Person Entering");
    player.play(1); // Play greeting audio
    delay(2000);    // Simple debounce
  }

  if (exitDetected) {
    Serial.println("Person Exiting");
    player.play(2); // Play exit audio
    delay(2000);
  }
}
