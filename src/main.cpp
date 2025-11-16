#include <WiFi.h>

const char* ssid = WIFI_SSID;
const char* password = WIFI_PASS;

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.print("Conectando");
  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
    Serial.print(".");
  }

  Serial.println("\nConectado!");
}

void loop() {
  int rssi = WiFi.RSSI();
  Serial.print("RSSI: ");
  Serial.println(rssi);

  delay(150);
}
