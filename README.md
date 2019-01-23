# LauschArduino

Die serielle Interaktion zwischen Arduino und PC ist bei komplexen Maschinen oft nur schwer durchschaubar, was die Fehlersuche schwierig gestaltet. Dieser kleine Sketch schafft Abhilfe.

## Features
 - Speichern einer PC-/Arduino-Konversation im EEPROM (max. 8 kB!), Ausgabe im seriellen Monitor auf Befehl
 - Erkennen von bestimmten Keywörtern
 - Einbinden eigener Sketches

 Die einzelnen Funktionen können in der Config.h-Datei aktiviert und deaktiviert werden

## Einbinden in bestehende Schaltungen

Wichtig: Das Board muss ZWEI serielle Schnittstellen haben (z.B. Arduino Mega), Arduino Uno und Nano sind somit ungeeignet!

| Anschluss LauschArduino   | Anschließen an                  |
| -------------             | -------------                   |
| Serial/USB                | PC                              |
| Serial1 (TX/RX)           | anderer Arduino: Serial (RX/TX) |
| VIN                       | anderer Arduino: VIN            |
| GND                       | anderer Arduino: GND            |

