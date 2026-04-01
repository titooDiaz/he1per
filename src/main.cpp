#include <Arduino.h>
#include <WiFi.h>

const char* ssid = "*";
const char* password = "*";

WiFiServer server(80);

// Pines
#define AIN1 26
#define AIN2 27
#define BIN1 33
#define BIN2 25
#define STBY 16

#define freq 1000
#define resolution 8
#define canalA 0
#define canalB 1

void stopMotors() {
  Serial.println("CMD: STOP");
  ledcWrite(canalA, 0);
  ledcWrite(canalB, 0);
}

void forward() {
  Serial.println("CMD: FORWARD");
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN2, LOW);
  ledcWrite(canalA, 200);
  ledcWrite(canalB, 200);
}

void backward() {
  Serial.println("CMD: BACKWARD");
  digitalWrite(AIN2, HIGH);
  digitalWrite(BIN2, HIGH);
  ledcWrite(canalA, 200);
  ledcWrite(canalB, 200);
}

void left() {
  Serial.println("CMD: LEFT");
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN2, HIGH);
  ledcWrite(canalA, 200);
  ledcWrite(canalB, 200);
}

void right() {
  Serial.println("CMD: RIGHT");
  digitalWrite(AIN2, HIGH);
  digitalWrite(BIN2, LOW);
  ledcWrite(canalA, 200);
  ledcWrite(canalB, 200);
}

void setup() {
  Serial.begin(115200);

  pinMode(AIN2, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(STBY, OUTPUT);
  digitalWrite(STBY, HIGH);

  ledcSetup(canalA, freq, resolution);
  ledcAttachPin(AIN1, canalA);

  ledcSetup(canalB, freq, resolution);
  ledcAttachPin(BIN1, canalB);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(300);
    Serial.print(".");
  }

  Serial.println("\nIP:");
  Serial.println(WiFi.localIP());

  server.begin();
}

void loop() {
  WiFiClient client = server.available();

  if (!client) return;

  Serial.println("\n--- NUEVO CLIENTE ---");

  String request = client.readStringUntil('\r');
  Serial.println("REQUEST:");
  Serial.println(request);

  if (request.indexOf("forward") != -1) forward();
  else if (request.indexOf("backward") != -1) backward();
  else if (request.indexOf("left") != -1) left();
  else if (request.indexOf("right") != -1) right();
  else if (request.indexOf("stop") != -1) stopMotors();

  client.println("HTTP/1.1 200 OK");
  client.println("Content-type:text/plain");
  client.println("Access-Control-Allow-Origin: *");
  client.println("Connection: close");
  client.println();
  client.println("OK");

  client.stop();
}