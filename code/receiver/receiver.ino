#include <SoftwareSerial.h>
#include "EBYTE.h"
#include "pitches.h"

#define PIN_AX 2
#define PIN_TX 4
#define PIN_RX 3
#define PIN_M1 5
#define PIN_M0 6
#define BUZ    7

struct DATA {
  int State;
};

DATA Message;
unsigned long Last;

SoftwareSerial ESerial(PIN_RX, PIN_TX);
EBYTE Transceiver(&ESerial, PIN_M0, PIN_M1, PIN_AX);

int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

void setup() {
  ESerial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(BUZ, OUTPUT);
  Transceiver.init();
  digitalWrite(LED_BUILTIN, LOW);
  Transceiver.PrintParameters();
}

void loop() {
  if (Transceiver.available()) {
    Transceiver.GetStruct(&Message, sizeof(Message));
    if (Message.State == 1) {
      for (int i = 0; i <= 3; i++) {
        digitalWrite(LED_BUILTIN, HIGH);
        playMelody();
        delay(1000);
        digitalWrite(LED_BUILTIN, LOW);
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

void playMelody() {
  for (int thisNote = 0; thisNote < 8; thisNote++) {
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(BUZ, melody[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(BUZ);
  }
}
