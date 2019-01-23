# LauschArduino

"Lausch-Arduino", der die Kommunikation eines anderen Arduinos über die serielle Verbindung (z.B. USB) speichert und auf Befehl ausgeben kann

# Features
 - Speichern einer PC-/Arduino-Konversation im EEPROM (max. 8 kB!), Ausgabe im seriellen Monitor auf Befehl
 - Erkennen von bestimmten Keywörtern
 - Einbinden eigener Sketches

 Die einzelnen Funktionen können in der Config.h-Datei aktiviert und deaktiviert werden

# Einbinden in bestehende Schaltungen

Wichtig: Das Board muss ZWEI serielle Schnittstellen haben

USB/Serial -> PC
Serial1 (TX/RX) -> anderer Arduino (RX/TX)
VIN -> VIN anderer Arduino
GND -> GND anderer Arduino
