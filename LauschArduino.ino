/***********************************************
  
  !!!   EINSTELLUNGEN IN CONFIG.H-FILE     !!!

  !!!   EIGENER CODE IN SKETCH.INO!        !!!  

***********************************************/

#include "Config.h"


void setup () {
  Serial.begin(USB_BAUDRATE);
  Serial1.begin(SERIAL1_BAUDRATE);
  sketch_setup();
}

void loop () {

  //---------------Nachricht von PC--------------------
  if (Serial.available() > 0) {

    //Nachricht auslesen
    char a = Serial.read();

    //Überprüfen
    if (check_befehl(a)) {
        //weiterleiten und speichern
        Serial1.print(a);
        #ifdef SPEICHERN
              speichern(a, 0);
        #endif
    }
  }

  //--------------Nachricht von Serial1--------------------
  while (Serial1.available() > 0) {

    //Nachricht auslesen
    char b = Serial1.read();

    //Überprüfen
    if (check_antwort(b)) {
      //Nachricht weiterleiten
      Serial.print(b);
  
      //Nachricht speichern
      #ifdef SPEICHERN
            speichern(b, 1);
      #endif
    }
  }
  sketch_loop();
}
