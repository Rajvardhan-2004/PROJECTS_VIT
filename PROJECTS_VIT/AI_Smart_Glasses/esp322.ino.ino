#include <WiFi.h>
#include <Wire.h>
#include <WebServer.h>

const char* ssid = "iPhone";
const char* password = "13579Raj";

#define SDA_PIN 4
#define SCL_PIN 5
#define ARDUINO_ADDRESS 0x08

#define MIC_PIN 39  // Analog pin for microphone input
#define LED_PIN 2   // Built-in LED
const int SOUND_THRESHOLD = 2500;

WebServer server(80);
String latestText = "";

void sendTextToArduino(const String& text) {
  Wire.beginTransmission(ARDUINO_ADDRESS);
  Wire.write((const uint8_t*)text.c_str(), text.length());
  Wire.endTransmission();
}

void handleTextReceive() {
  if (server.hasArg("text")) {
    latestText = server.arg("text");
    Serial.print("Received from laptop: ");
    Serial.println(latestText);
    sendTextToArduino(latestText);
    server.send(200, "text/plain", "Text received and sent to Arduino");
  } else {
    server.send(400, "text/plain", "Missing 'text' parameter");
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\n✅ Connected to WiFi!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  Wire.begin(SDA_PIN, SCL_PIN);

  server.on("/send_text_to_esp32", handleTextReceive);
  server.begin();
  Serial.println("📡 Server started");
}

void loop() {
  server.handleClient();

  // Check sound level
  int micValue = analogRead(MIC_PIN);
  if (micValue > SOUND_THRESHOLD) {
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);
  }
}
