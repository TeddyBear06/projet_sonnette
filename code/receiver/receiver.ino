#include <SoftwareSerial.h>
#include "EBYTE.h"

#define PIN_AX 2
#define PIN_TX 4
#define PIN_RX 3
#define PIN_M1 5
#define PIN_M0 6
#define SPK    7

struct DATA {
  int State;
};

DATA Message;
unsigned long Last;

SoftwareSerial ESerial(PIN_RX, PIN_TX);
EBYTE Transceiver(&ESerial, PIN_M0, PIN_M1, PIN_AX);

void setup() {
  ESerial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  pinMode(SPK, OUTPUT);
  digitalWrite(SPK, LOW);
  Transceiver.init();
}

void loop() {
  if (Transceiver.available()) {
    Transceiver.GetStruct(&Message, sizeof(Message));
    if (Message.State == 1) {
      for (int i = 0; i < 3; i++) {
        digitalWrite(LED_BUILTIN, HIGH);
        ringTheBell();
        digitalWrite(LED_BUILTIN, LOW);
        delay(1000);
      }
    } else {
      digitalWrite(LED_BUILTIN, LOW);
    }
    Last = millis();
  } else {
    digitalWrite(LED_BUILTIN, LOW);
    if ((millis() - Last) > 1000) {
      Last = millis();
    }
  }
}

void ringTheBell() {
  tone(SPK, 2500, 1000);
  delay(1000);
  tone(SPK, 1000, 2000);
  delay(2000);
  digitalWrite(SPK, LOW);
}
