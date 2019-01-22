//Homing-Sketch

//*********************Bibliotheken*******************************

//**********************Variablen*********************************

//***********************Funktionen*******************************
void homing() {
  Serial1.print(":hR#"); //Unpark
  Serial1.print(":R9#"); //Set rate to move
  Serial1.print(":Mw#"); //Move telescope west
  Serial1.print(":Mn#"); //Move telescope north

  //Solange fahren, bis Taster gedrückt
  boolean azm_fertig = false;
  boolean alt_fertig = false;
  while ((!azm_fertig) || (!alt_fertig)) {
    if (!digitalRead(HOMING_AZM) && !azm_fertig) {
      azm_fertig = true; Serial1.print(":Qw#");
    }
    if (!digitalRead(HOMING_ALT) && !alt_fertig) {
      alt_fertig = true; Serial1.print(":Qn#");
    }
  }

  char befehl [10];
  //Sync
  strcpy(befehl, ":Sr");
  strcat(befehl, HOME_AZM);
  Serial1.print(befehl);
  strcpy(befehl, ":Sds");
  strcat(befehl, HOME_ALT);
  Serial1.print(befehl);
  Serial1.print(":CS#");
}

