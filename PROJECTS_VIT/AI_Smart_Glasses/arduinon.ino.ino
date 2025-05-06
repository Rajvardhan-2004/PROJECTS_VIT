#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

String receivedText = "";

void setup() {
  Wire.begin(8);  // I2C address for Arduino Nano (slave)
  Wire.onReceive(receiveEvent);  // Register receive event

  Serial.begin(9600);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 OLED init failed"));
    while (true);  // Stop if display not found
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Waiting for ESP32...");
  display.display();
}

void loop() {
  if (receivedText.length() > 0) {
    Serial.println("From ESP32: " + receivedText);

    display.clearDisplay();
    display.setCursor(0, 0);
    display.println(receivedText);
    display.display();

    receivedText = "";  // Clear for next message
  }

  delay(100);
}

void receiveEvent(int howMany) {
  receivedText = "";
  while (Wire.available()) {
    char c = Wire.read();
    receivedText += c;
  }
}
