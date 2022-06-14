#include <WiFi101.h> // Bibliotek zum steuern von Wlan Karten
#include "Keyboard.h" // Bibliotek zum emulieren einer Tastartur über USB

// Konfiguration
char ssid[] = "BBS3_GSS"; // SSID eines Wlans, über welche die Kommunikation zu dem Sensor stattfindet
char pass[] = ""; // Password eines Wlans, über welche die Kommunikation zu dem Sensor stattfindet

int status = WL_IDLE_STATUS; // Setzen des Wlan Status auf WL_IDLE_STATUS
WiFiServer server(80); // Setzen des WLan Server Port auf 80

// Start-Prozess
void setup() { // Wird als erste Funktion automatisch nach dem deklarieren von Variablen unter dem Abschnitt Konfiguration ausgeführt
  Serial.begin(9600); // Serielle Kommunikation starten
  Keyboard.begin(); // Emulation einer Tastartur über USB starten
  delay(5000);
  Serial.println("Tastatur-Emulator");
  Serial.println("");
  Serial.println("Hardware Test:");
  // Ausgabe eines Fehlers, wen keine Wlan Unterstützung gefunden wird
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
  // For Schleife für die zensierte Ausgabe des Wlan Passwords im Log
  for ( int i = 0; i < strlen(pass); i++ ) {
    Serial.print("*");
  }
  Serial.println("");
  Serial.println("");
  Serial.println("Wlan Verbindungsaufbau:");
  // Solange keine Verbindung zu dem Wlan besteht, wird versucht sich erneut zu verbinden
  while ( status != WL_CONNECTED) {
    Serial.println("Verbindung wird hergestellt...");
    status = WiFi.begin(ssid, pass); // Herstellen der Wlan verbindung zu der SSID mit dem konfigurierten Passwort
    delay(10000);
  }
  Serial.println("Verbindung erfolgreich");
  Serial.println("");
  Serial.println("Debug Server auf Port 80 gestartet");
  server.begin(); // Starten des Web Servers
  Serial.println("");
  Serial.println("Wlan Status:");
  printWifiStatus();
}

// Haupt-Prozess
void loop() { // Wird nach der setup Funktion ausgeführt und fortlaufend wiederholt
  WiFiClient client = server.available();
  if (client) {
    String currentLine = "";
    while (client.connected())
    {
      if (client.available())
      {
        char c = client.read();
        if (c == '\n') {
            if (currentLine.length() == 0) {
                // Senden einer HTTP Antwort an den Client. Die Antowrt enthält eine Debug Webseite, welche zum Testen der Tastatur-Emulator Funktion für BBB.
            	client.println("HTTP/1.1 200 OK");
            	client.println("Content-type:text/html");
            	client.println();
            	client.println("<h1>Debug Options</h1><br>");
            	client.print("<h2><a href=\"/F\">F</a></h2><br>");
            	client.print("<h2><a href=\"/M\">Mute</a></h2><br>");
            	client.print("<h2><a href=\"/N\">Next Slide</a></h2><br>");
            	client.print("<h2><a href=\"/P\">Previous Slide</a></h2><br>");
            	client.println();
            	break;
          }
          else {
            currentLine = "";
          }
        }
        else if (c != '\r') {
          currentLine += c;
        }
        if (currentLine.endsWith("GET /F")) {
          delay(5000);
          pressF();
        }
        if (currentLine.endsWith("GET /M")) {
          delay(5000);
          bbbMute();
        }
        if (currentLine.endsWith("GET /N")) {
          delay(5000);
          bbbNextSlidePresenter();
        }
        if (currentLine.endsWith("GET /P")) {
          delay(5000);
          bbbPreviousSlidePresenter();
        }
      }
    }

    client.stop();
  }
}

// Testfunktion
void pressF()
{
  Keyboard.write('F');
}

// Funktion zum ausführen der "Stummschalten" Aktion in BBB
void bbbMute()
{
  Keyboard.press(KEY_LEFT_ALT);
  delay(200);
  Keyboard.press('m');
  delay(200);
  Keyboard.releaseAll();
}

// Funktion zum ausführen der "Nächste Folie" Aktion in BBB
void bbbNextSlidePresenter()
{
  Keyboard.write(KEY_RIGHT_ARROW);
}

// Funktion zum ausführen der "voriege Folie" Aktion in BBB
void bbbPreviousSlidePresenter()
{
  Keyboard.write(KEY_LEFT_ARROW);
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
