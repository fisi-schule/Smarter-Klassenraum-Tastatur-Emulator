#include <WiFi101.h> // Bibliotek zum steuern von Wlan Karten
#include "Keyboard.h" // Bibliotek zum emulieren einer Tastartur über USB

// Konfiguration
char ssid[] = "Pixel_2707";
char pass[] = "1234567887654321";
int keyIndex = 0;
bool val = true;

int status = WL_IDLE_STATUS;

// Start-Prozess
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

// Haupt-Prozess
void loop() {
  char input = 0;
  if(Serial.available())
  {
    input = Serial.read();
    Serial.flush();
  }
  if (input == '1'){
    pressF();
  }
  input = 0;
}

// Testfunktion
void pressF()
{
  Keyboard.press('F');
}

// Funktion für die Ausgabe der Wlan Verbindungsinformationen
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