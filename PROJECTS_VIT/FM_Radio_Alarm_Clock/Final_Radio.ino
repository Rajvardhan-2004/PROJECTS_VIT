#include <Wire.h>
#include <EEPROM.h>
#include <RTClib.h>
#include <Adafruit_SSD1306.h>
#include <TEA5767Radio.h>

// OLED display setup
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// RTC module
RTC_DS3231 rtc;

// TEA5767 FM Radio
TEA5767Radio radio;

// Pin definitions for RGB LED
const int redPin = 2;
const int greenPin = 3;
const int bluePin = 4;

// Button pin to stop alarm
const int buttonPin = 7;

// EEPROM addresses for alarm settings
#define EEPROM_ALARM_HOUR 0
#define EEPROM_ALARM_MIN 1
#define EEPROM_FM_FREQ 2  // Frequency stored in two bytes

bool alarmTriggered = false;
int lastCheckedMinute = -1; // Prevent retriggering in the same minute

// Alarm settings (default values, overridden by EEPROM)
int alarmHour = 7;
int alarmMinute = 30;
int fmFrequency = 10170; // 101.7 MHz (stored as 10170 kHz)

void setup() {
  Serial.begin(9600);
  Wire.begin();

  // Initialize OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED init failed");
    for (;;);
  }
  display.clearDisplay();
  display.display();

  // Initialize RTC
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    for (;;);
  }
  
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // Set RTC to compile time
  


  // Set up LED pins
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  turnOffLEDs();

  // Set up button input
  pinMode(buttonPin, INPUT_PULLUP);

  // Read stored alarm settings from EEPROM
  alarmHour = EEPROM.read(EEPROM_ALARM_HOUR);
  alarmMinute = EEPROM.read(EEPROM_ALARM_MIN);
  int freqHigh = EEPROM.read(EEPROM_FM_FREQ);
  int freqLow = EEPROM.read(EEPROM_FM_FREQ + 1);
  fmFrequency = (freqHigh << 8) | freqLow;

  // If EEPROM values are invalid, set defaults
  if (alarmHour > 23) alarmHour = 12;
  if (alarmMinute > 59) alarmMinute = 03;
  if (fmFrequency < 8700 || fmFrequency > 10800) fmFrequency = 9390;

  Serial.print("Alarm set for: ");
  Serial.print(alarmHour);
  Serial.print(":");
  Serial.println(alarmMinute);
  Serial.print("FM Frequency: ");
  Serial.println(fmFrequency / 100.0);
}

void loop() {
  DateTime now = rtc.now();
  displayTime(now);
  
  // Check if the alarm should trigger (only once per minute)
  if (!alarmTriggered && now.hour() == alarmHour && now.minute() == alarmMinute && now.minute() != lastCheckedMinute) {
    alarmTriggered = true;
    lastCheckedMinute = now.minute();
    triggerAlarm();
  }

  // Check if button is pressed to disable alarm
  if (alarmTriggered && digitalRead(buttonPin) == LOW) {
    disableAlarm();
  }
  

  delay(1000); // Update every second
}

void displayTime(DateTime now) {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);

  char timeString[9];
  sprintf(timeString, "%02d:%02d:%02d", now.hour(), now.minute(), now.second());
  display.println(timeString);

  display.setTextSize(1);
  display.setCursor(0, 40);
  if (alarmTriggered) {
    display.println("ALARM ON - Press button to disable");
  } else {
    display.print("Alarm: ");
    display.print(alarmHour);
    display.print(":");
    display.println(alarmMinute);
  }

  display.setCursor(0, 55);
  display.print("FM: ");
  display.print(fmFrequency / 100.0);
  display.println(" MHz");

  display.display();
}

void triggerAlarm() {
  startFMRadio(fmFrequency);
  Serial.println("Alarm triggered! Smooth sunrise effect starting...");

  // Smooth sunrise effect using digitalWrite (gradual turn-on effect)
  digitalWrite(redPin, LOW);
  digitalWrite(bluePin, LOW);
  delay(2000);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, LOW);
  digitalWrite(redPin, HIGH);
  delay(2000);
  digitalWrite(bluePin, LOW);
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, LOW);
  delay(2000);

  Serial.println("Sunrise effect completed.");
}

void disableAlarm() {
  stopFMRadio();
  turnOffLEDs();
  alarmTriggered = false;
  Serial.println("Alarm disabled by button press.");
}

void turnOffLEDs() {
  digitalWrite(redPin, HIGH);
  digitalWrite(greenPin, HIGH);
  digitalWrite(bluePin, HIGH);
}

void startFMRadio(int frequency) {
  float freqMHz = frequency / 100.0; // Convert from kHz to MHz
  radio.setFrequency(freqMHz);
  Serial.print("Starting FM radio at ");
  Serial.print(freqMHz);
  Serial.println(" MHz");
}

void stopFMRadio() {
  radio.setFrequency(0); // Properly stop the radio
  Serial.println("Stopping FM radio.");
}
