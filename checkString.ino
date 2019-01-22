//Überprüfen von empfangenen Strings auf bestimmte
//Zeichen und Schlüsselbefehle

//**********************Konstanten*********************************
//| | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
//v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v v
//                       KEYWÖRTER!!!

const int keywords_anzahl = 4;
const char keywords [keywords_anzahl][14] = { "Apfel", "Birne", "Banane", "Und so weiter"};

//*****************************************************************

//-----------------------------Überprüfen einer Zeichenkette von USB--------------------------------
int check_befehl (char befehl) {
  switch (befehl) {

    /*********************************
      AKTIONEN NACH ZEICHEN BEI USB
      (CASE: 'ZEICHEN'
        tue();
        return false;)
      |           |           |
      v           v           v
    *********************************/


    //Ausgabebefehl für die aufgezeichnete Konversation erteilt
    case AUSGABEBEFEHL:
      #ifdef SPEICHERN
            usb_ausgabe();
      #endif
      return false;

    case '\n':
      return true;

    //Keywords überprüfen
    //Bei Verdacht (erstes Zeichen stimmt überein):
    //an verdacht() weiterleiten
    default:
      int verdacht_ergebnis = -1; //Kein Treffer = -1, Treffer = Index in Keywordliste

      //Alle Keywords durchgehen
      for (int x = 0; x < keywords_anzahl; x++) {
        if (befehl == keywords[x][0]) {

          verdacht_ergebnis = verdacht(befehl, 0);

          //Ergebnis der Analyse verarbeiten
          if (verdacht_ergebnis >= 0) {
            switch (verdacht_ergebnis) {

              /******************************
                AKTIONEN NACH KEYWORDS BEI USB
                (CASE: LISTENINDEX)
                |           |           |
                v           v           v
              *******************************/



              default:
                //Serial.println("ERWISCHT");
                Serial1.print(keywords[verdacht_ergebnis]);
            }
          }
          return false;
        }
      }
      return true;
  }
}


//-----------------------------Überprüfen einer Zeichenkette von Serial1-----------------------------
int check_antwort (char antwort) {
  switch (antwort) {

    /*********************************
      AKTIONEN NACH ZEICHEN BEI Serial1
      (CASE: 'ZEICHEN'
        tue();
        return false;)
      |           |           |
      v           v           v
    *********************************/

    case '\n':
      return true;

    //Keywords überprüfen
    //Bei Verdacht (erstes Zeichen stimmt überein):
    //an verdacht() weiterleiten
    default:
      int verdacht_ergebnis = -1; //Kein Treffer = -1, Treffer = Index in Keywordliste

      //Alle Keywords durchgehen
      for (int x = 0; x < keywords_anzahl; x++) {
        if (antwort == keywords[x][0]) {

          verdacht_ergebnis = verdacht(antwort, 1);

          //Ergebnis der Analyse verarbeiten
          if (verdacht_ergebnis >= 0) {
            switch (verdacht_ergebnis) {

              /******************************
                AKTIONEN NACH KEYWORDS BEI Serial1
                (CASE: LISTENINDEX)
                |           |           |
                v           v           v
              *******************************/



              default:
                Serial.println("ERWISCHT");
                Serial.println(keywords[verdacht_ergebnis]);
            }
          }
          return false;
        }
      }
      return true;
  }
}


//-----------------------------Keyword-Kontrolle-----------------------------
int verdacht (char befehl, int vonwem) {
  
  #ifdef SPEICHERN
      speichern(befehl, vonwem);
  #endif
  
  
  char befehl_ausgelesen [15];
  befehl_ausgelesen[0] = befehl; befehl_ausgelesen[1] = '\0';

  //Alle Keywörter durchgehen
  for (int i = 0; i < keywords_anzahl; i++) {
    int j = -1;

    do {
      j++;
      //Wenn Zeichen noch unbekannt: Einlesen
      if (!befehl_ausgelesen[j] || befehl_ausgelesen[j] == '\0') {
        
        int timeout = 0;

        //Den richtigen seriellen Port auslesen
        if (!vonwem) {
          //Serial-available-bug... Port braucht seine Zeit,
          //um korrekten Wert auszugeben
          while (!Serial.available() && timeout < 1000) timeout++;

          if (Serial.available() > 0) {
            befehl_ausgelesen[j] = Serial.read();
            befehl_ausgelesen[j + 1] = '\0';

            #ifdef SPEICHERN
                speichern(befehl_ausgelesen[j], vonwem);
            #endif
          }
          else continue;
        }
        else {
          while (!Serial1.available() && timeout < 1000) timeout++;

          if (Serial1.available() > 0) {
            befehl_ausgelesen[j] = Serial1.read();
            befehl_ausgelesen[j + 1] = '\0';

             #ifdef SPEICHERN
                speichern(befehl_ausgelesen[j], vonwem);
            #endif
          }
          else continue;
        }
      }

      //Wenn Keyword zu Ende: Verdacht bestätigt!
      if (keywords[i][j] == '\0') {
        //Serial.println(i);
        return i;
      }
      //Serial.println(befehl_ausgelesen);
    }
    while (befehl_ausgelesen[j] == keywords[i][j]);
  }

  //Verdacht unbegründet
  if (vonwem == 0) Serial1.print(befehl_ausgelesen);
  else if (vonwem == 1) Serial.print(befehl_ausgelesen);
  return -1;
}
