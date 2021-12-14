#include <SoftwareSerial.h>
#include <Adafruit_SSD1306.h>
#include "EBYTE.h"

#define PIN_AX 2
#define PIN_TX 4
#define PIN_RX 3
#define PIN_M1 5
#define PIN_M0 6
#define BTN    7

#define PIX_WIDTH             128
#define PIX_HEIGHT            64
#define RST                   -1
#define ADDR_I2C              0x3C

Adafruit_SSD1306 oled(PIX_WIDTH, PIX_HEIGHT, &Wire, RST);

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
  oled.begin(SSD1306_SWITCHCAPVCC, ADDR_I2C);
  oled.clearDisplay();
  oled.ssd1306_command(SSD1306_DISPLAYON);
  oled.setTextSize(3);
  oled.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
  oled.setCursor(0, 0);
  oled.println("OK");
  oled.display();
  delay(1000);
  oled.ssd1306_command(SSD1306_DISPLAYOFF);
}

void loop() {
  if (digitalRead(BTN) == HIGH){
    Message.State = 1;
    Transceiver.SendStruct(&Message, sizeof(Message));
    oled.ssd1306_command(SSD1306_DISPLAYON);
    oled.setTextSize(2);
    oled.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
    oled.setCursor(0, 0);
    oled.println("Appel en");
    oled.println("cours...");
    oled.display();
    for (int i = 0; i <= 125; i++) {
      digitalWrite(LED_BUILTIN, HIGH);
      delay(50);
      digitalWrite(LED_BUILTIN, LOW);
      delay(50);
    }
    oled.ssd1306_command(SSD1306_DISPLAYOFF);
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }
}
