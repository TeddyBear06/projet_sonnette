#include <SoftwareSerial.h>
#include "EBYTE.h"

#define PIN_AX  2
#define PIN_TX  4
#define PIN_RX  3
#define PIN_M1  5
#define PIN_M0  6
#define BTN     A5
#define LED_BTN A4
#define SPK     7
#define VOLT_INPUT A0
#define LED_VERTE A1
#define LED_ORANG A2
#define LED_ROUGE A3

struct DATA {
  int State;
};

DATA Message;

SoftwareSerial ESerial(PIN_RX, PIN_TX);
EBYTE Transceiver(&ESerial, PIN_M0, PIN_M1, PIN_AX);

void setup() {
  Serial.begin(9600);
  ESerial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(BTN, INPUT_PULLUP);
  pinMode(LED_BTN, OUTPUT);
  digitalWrite(LED_BTN, LOW);
  pinMode(SPK, OUTPUT);
  digitalWrite(SPK, LOW);
  pinMode(LED_VERTE, OUTPUT);
  pinMode(LED_ORANG, OUTPUT);
  pinMode(LED_ROUGE, OUTPUT);
  Transceiver.init();
}

void loop() {
  checkVoltage();
  if (digitalRead(BTN) == HIGH){
    Message.State = 1;
    Transceiver.SendStruct(&Message, sizeof(Message));
    for (int j=0;j<3;j++) {
      digitalWrite(LED_BTN, HIGH);
      ringTheBell();
      digitalWrite(LED_BTN, LOW);
      delay(1000);
    }
  } else {
    digitalWrite(LED_BTN, LOW);
  }
}

void checkVoltage() {
  int raw_volt_input_val;
  int input_voltage;
  float temp;
  raw_volt_input_val = analogRead(VOLT_INPUT);
  temp = raw_volt_input_val/4.092;
  raw_volt_input_val = (int) temp;
  input_voltage = ((raw_volt_input_val%100)/10);
  Serial.println(input_voltage);
  if (input_voltage <= 4) {
    digitalWrite(LED_VERTE, LOW);
    digitalWrite(LED_ORANG, LOW);
    digitalWrite(LED_ROUGE, HIGH);
  } else if (input_voltage > 3 && input_voltage <= 4) {
    digitalWrite(LED_VERTE, LOW);
    digitalWrite(LED_ORANG, HIGH);
    digitalWrite(LED_ROUGE, LOW);
  } else {
    digitalWrite(LED_VERTE, HIGH);
    digitalWrite(LED_ORANG, LOW);
    digitalWrite(LED_ROUGE, LOW);
  }
}

void ringTheBell() {
  tone(SPK, 2500, 1000);
  delay(1000);
  tone(SPK, 1000, 2000);
  delay(2000);
  digitalWrite(SPK, LOW);
}
