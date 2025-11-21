#include <Arduino.h>
#include <WiFi.h>
#include "secrets.h"

// you can adjust this value to your needs
// 0.1 = very stable but slow
// 0.2 = faster but less filtered
float alpha = 0.12;  

float filteredRSSI = 0;

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  Serial.print("Conectando");
  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
    Serial.print(".");
  }
  Serial.println("\nConectado!");
  filteredRSSI = WiFi.RSSI();
}

void loop() {
  int rawRSSI = WiFi.RSSI();
  filteredRSSI = alpha * rawRSSI + (1 - alpha) * filteredRSSI;

  Serial.print("RSSI crudo: ");
  Serial.print(rawRSSI);
  Serial.print("  |  RSSI filtrado: ");
  Serial.println(filteredRSSI);

  delay(150);
}
