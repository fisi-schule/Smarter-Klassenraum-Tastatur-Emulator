#include <WiFi101.h> // Bibliotek zum steuern von Wlan Karten
#include "Keyboard.h" // Bibliotek zum emulieren einer Tastartur über USB

// Konfiguration
char ssid[] = "BBS3_GSS";
char pass[] = "";
int keyIndex = 0;
bool val = true;

int status = WL_IDLE_STATUS;
WiFiServer server(80);

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
  Serial.println("Debug Server auf Port 80 gestartet");
  server.begin();
  Serial.println("");
  Serial.println("Wlan Status:");
  printWifiStatus();
}

// Haupt-Prozess
void loop() {
  WiFiClient client = server.available();
  if (client) {                             
    String currentLine = "";              
    while (client.connected()) 
    {       
      if (client.available()) 
      {
        char c = client.read();
        if (c == '\n') 
        {                 

            if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.println("<h1>Debug Optionen</h1><br>");
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

void bbbMute()
{
  Keyboard.press(KEY_LEFT_ALT);
  delay(200);
  Keyboard.press('m');
  delay(200);
  Keyboard.releaseAll();
}

void bbbNextSlidePresenter()
{
  Keyboard.write(KEY_RIGHT_ARROW);
}

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