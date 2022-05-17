#include <SPI.h>
#include <WiFi101.h>
#include "Keyboard.h"

char ssid[] = "Pixel_2707";
char pass[] = "1234567887654321";
int keyIndex = 0;
bool val = true;

int status = WL_IDLE_STATUS;

void setup() {
  Serial.begin(9600);
  Keyboard.begin();
  delay(5000);
  Serial.println("Tastatur-Emulator");
  Serial.println("");
  Serial.println("Hardware Test:");
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("Keine Wlan Unterstützung gefunden");
    Serial.println("");
    Serial.println("Programm wird beendet");
    return;
  }
  Serial.println("Wlan Unterstützung gefunden");
  Serial.println("");
  Serial.println("Konfiguration:");
  Serial.print("Wlan SSID: ");
  Serial.println(ssid);
  Serial.print("Wlan Passwort: ");
  for ( int i = 0; i < strlen(pass); i++ ) {
    Serial.print("*");
  }
  Serial.println("");
  Serial.println("");
  Serial.println("Wlan Verbindungsaufbau:");
  while ( status != WL_CONNECTED) {
    Serial.println("Verbindung wird hergestellt...");
    status = WiFi.begin(ssid, pass);
    delay(10000);
  }
  Serial.println("Verbindung erfolgreich");
  Serial.println("");
  Serial.println("Wlan Status:");
  printWifiStatus();
}
void loop() {
  char input = 0;
  if(Serial.available())
  {
    input = Serial.read();
    Serial.flush();
  }
  if (input == 1){
    pressF();
  }
  input = 0;
}

void pressF()
{
  Keyboard.press('F');
}

void printWifiStatus()
{
  IPAddress ip = WiFi.localIP();
  Serial.print("IP-Adresse: ");
  Serial.println(ip);
  long rssi = WiFi.RSSI();
  Serial.print("Signalstärke:");
  Serial.print(rssi);
  Serial.println(" dBm");
}