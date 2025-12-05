#include <Arduino.h>
#include <WiFi.h>

// button 'boot'
const int BOOT_PIN = 0;

struct NetStats {
  String ssid;
  int sumRSSI = 0;
  int count = 0;
};

NetStats networks[50];
int netCount = 0;

int findNetwork(const String& ssid) {
  for (int i = 0; i < netCount; i++)
    if (networks[i].ssid == ssid) return i;
  return -1;
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect(true);

  pinMode(BOOT_PIN, INPUT);
  Serial.println("\n--- PRESS BOOT BUTTON ---\n");
}

void loop() {
  if (digitalRead(BOOT_PIN) == 0) {
    Serial.println("\n--- BOOT ---");

    // reset networks data
    netCount = 0;
    for (int i = 0; i < 50; i++) {
      networks[i].ssid = "";
      networks[i].sumRSSI = 0;
      networks[i].count = 0;
    }

    // Do 5 scans
    for (int k = 0; k < 5; k++) {
      Serial.print("Medición ");
      Serial.println(k + 1);

      int n = WiFi.scanNetworks();

      for (int i = 0; i < n; i++) {
        String ssid = WiFi.SSID(i);
        int rssi   = WiFi.RSSI(i);

        int idx = findNetwork(ssid);

        if (idx == -1 && netCount < 50) {
          idx = netCount++;
          networks[idx].ssid = ssid;
        }

        networks[idx].sumRSSI += rssi;
        networks[idx].count++;
      }

      WiFi.scanDelete();
      delay(300);
    }

    // show average
    Serial.println("\n--- AVERAGE ---");
    for (int i = 0; i < netCount; i++) {
      float average = (float)networks[i].sumRSSI / networks[i].count;

      Serial.print(i + 1);
      Serial.print(") ");
      Serial.print(networks[i].ssid);
      Serial.print(" -> ");
      Serial.print(average, 1);
      Serial.println(" dBm");
    }

    Serial.println("\n---  BOOT ---\n");
    delay(600);
  }
}
