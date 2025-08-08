#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

SoftwareSerial mySerial(6, 7); // TX, RX for DFPlayer
DFRobotDFPlayerMini myDFPlayer;

const int sensorIn = 2;
const int sensorOut = 3;

unsigned long lastTriggerTime = 0;
int triggerDelay = 1000;  // 1 second to detect entry/exit pattern

int lastSensor = 0; // 1 = IN first, 2 = OUT first

void setup() {
  pinMode(sensorIn, INPUT);
  pinMode(sensorOut, INPUT);

  Serial.begin(9600);
  mySerial.begin(9600);

  if (!myDFPlayer.begin(mySerial)) {
    Serial.println("DFPlayer not found!");
    while (true);
  }

  myDFPlayer.volume(30);  // Volume range: 0-30
}

void loop() {
  bool inTriggered = digitalRead(sensorIn) == LOW;
  bool outTriggered = digitalRead(sensorOut) == LOW;

  if (inTriggered && lastSensor == 0) {
    lastSensor = 1;
    lastTriggerTime = millis();
  }

  if (outTriggered && lastSensor == 0) {
    lastSensor = 2;
    lastTriggerTime = millis();
  }

  if ((millis() - lastTriggerTime > triggerDelay) && lastSensor != 0) {
    if (lastSensor == 1 && outTriggered) {
      myDFPlayer.play(1);  // Welcome
      delay(2000); // Wait for audio
    } else if (lastSensor == 2 && inTriggered) {
      myDFPlayer.play(2);  // Bye
      delay(2000);
    }
    lastSensor = 0;
  }
}
