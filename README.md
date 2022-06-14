# Smarter-Klassenraum-Tastatur-Emulator

Im Fach Cyber-physisches Systeme sollen die Schüler ein cyber-physisches System entwickeln, im Rahmen eines modernen digitalen Klassenraums. Dazu werden wir einen Aktor konstruieren, der die Daten von anderen Sensoren verarbeitet und anhand dieser vordefinierte Befehle als Tastatureingaben an ein Windows Gerät sendet. Dazu kann das Muten in BBB oder auch das sperren des Computers gezählt werden.

![Aufbau](https://i.imgur.com/kfZlaKt.jpeg)

## Voraussetzungen

- 1 x MKR1000
- 1 x Wlan Netzwerk
- 1 x PC mit USB Port
- 1 x Micro USB Kabel

## Einrichtung

1. Den MKR1000 mit einem PC verbinden
2. Herunterlanden der [Arduino IDE](https://www.arduino.cc/en/software)
3. Installieren der Arduino IDE Bibliotheken [WiFi101](https://www.arduino.cc/reference/en/libraries/wifi101/) und [Keyboard](https://www.arduino.cc/reference/en/libraries/keyboard/)
4. Arduino IDE, Board Typ auf MKR1000 stellen
5. Arduino IDE, Bound (Datenrate) auf 9600 setzen
6. [main.ino](https://github.com/fisi-schule/Smarter-Klassenraum-Tastatur-Emulator/blob/main/main.ino) herunterlanden und in dem Arduino IDE öffnen
7. Die WLAN SSID (Name des Wlans) u. das WLAN Passwort anpassen (Zeile 5-6)
8. Code auf den Arduino hochladen

## Bedienung

Nach dem der MKR1000 sich mit dem angegbenen Wlan verbunden hat, kann man über ein Debug Menü, die Funktionen des Tastatur-Emulators testen. Das Debug Menü kann über die IP-Adresse des MKR1000 erreicht werden.

Tipp: Die IP-Adresse des MKR1000 wird auf der Seriellen Schnittstelle ausgegeben.


## Lizenz

CC BY-SA 4.0

## Informationen zum Autor

Dieses Projekt wurde ursprünglich von [rootsaid](https://github.com/rootsaid) in 2017 erstellt und von Cayne Vejvoda und OneCyanide in 2022 geforked und an unsere Anforderungen angepasst.
