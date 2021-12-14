#include <SoftwareSerial.h>
#include "EBYTE.h"

#define PIN_AX 2
#define PIN_TX 4
#define PIN_RX 3
#define PIN_M1 5
#define PIN_M0 6
#define BTN    7

struct DATA {
  int State;
};

DATA Message;

SoftwareSerial ESerial(PIN_RX, PIN_TX);
EBYTE Transceiver(&ESerial, PIN_M0, PIN_M1, PIN_AX);

void setup() {
  ESerial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(BTN, INPUT_PULLUP);
  Transceiver.init();
  Transceiver.PrintParameters();
}

void loop() {
  if (digitalRead(BTN) == HIGH){
    Message.State = 1;
    Transceiver.SendStruct(&Message, sizeof(Message));
    for (int i = 0; i <= 125; i++) {
      digitalWrite(LED_BUILTIN, HIGH);
      delay(50);
      digitalWrite(LED_BUILTIN, LOW);
      delay(50);
    }
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }
}
