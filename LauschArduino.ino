/***********************************************
  "Lausch-Arduino", der die Kommunikation eines
  anderen Arduinos über die serielle Verbindung
  (z.B. USB) speichert und auf Befehl ausgeben
  kann

  GEHT NUR BEI ARDUINO MEGA!

  Jan Hauke, Dezember 2018

************************************************
  Einbinden in bestehende Schaltung:

  USB/Serial -> PC
  Serial1 (TX/RX) -> anderer Arduino (RX/TX)
  VIN -> VIN anderer Arduino
  GND -> GND anderer Arduino

************************************************
  !!!   EINSTELLUNGEN IN CONFIG.H-DATEI    !!!

************************************************
  Speichert Konversation in EEPROM
  (max. 8 kB!)

  Ausgabe an den PC auf Befehl
  (einstellbar in Config.h)

***********************************************/

#include "Config.h"


void setup () {
  Serial.begin(USB_BAUDRATE);
  Serial1.begin(SERIAL1_BAUDRATE);

  pinMode(HOMING_AZM, INPUT_PULLUP);
  pinMode(HOMING_ALT, INPUT_PULLUP);
  pinMode(HOMING_SWITCH, INPUT_PULLUP);

  //homing();

  delay(500);
}

void loop () {

  //---------------Nachricht von PC--------------------
  if (Serial.available() > 0) {

    //Nachricht auslesen
    char a = Serial.read();

    //Überprüfen
    //if (check_befehl(a)) {
      //weiterleiten und speichern
      Serial1.print(a);
      #ifdef SPEICHERN
            speichern(a, 0);
      #endif
    //}
  }

  //--------------Nachricht von Serial1--------------------
  while (Serial1.available() > 0) {

    //Nachricht auslesen
    char b = Serial1.read();

    //Überprüfen
    //if (check_antwort(b)) {
    //Nachricht weiterleiten
    Serial.print(b);

    //Nachricht speichern
    #ifdef SPEICHERN
          speichern(b, 1);
    #endif
    //}
  }
  if (!digitalRead(HOMING_SWITCH)) {
    homing();
  }
}
