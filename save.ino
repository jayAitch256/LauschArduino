//Programm zum Sichern der Konversation im EEPROM und
//zum Ausgeben derselben nach Senden eines bestimmten
//Ausgabebefehls

#ifdef SPEICHERN

//*********************Bibliotheken*******************************

#include <EEPROM.h>

//**********************Variablen*********************************

int addr_re = EEPROM.read(1); //EEPROM-Adresse zum Lesen
int addr_wr = EEPROM.read(2); //EEPROM-Adresse zum Schreiben

#ifdef SPEICHER
int speicherplatz = SPEICHER;
#else
int speicherplatz = EEPROM.length();
#endif

boolean aufnahme = true;

int last_vonwem = 2;

//***********************Funktionen********************************

//Hauptfunktion: Speichern eines Befehls
void speichern (char befehl, int vonwem) {
  if (aufnahme) {

    //Bei Anfang von Nachricht "<" bzw ">" einspeichern
    if (vonwem == 0 && vonwem != last_vonwem) eeprom_write(addr_wr, '>');
    else if (vonwem == 1 && vonwem != last_vonwem) eeprom_write(addr_wr, '<');
    last_vonwem = vonwem;

    //Buchstaben speichern
    if (!eeprom_write(addr_wr, befehl)) aufnahme = false;
  }
  save_values();
}

//Sichern der Schreib- und Lesevariablen im EEPROM
void save_values () {
  EEPROM.write(1, addr_re);
  EEPROM.write(2, addr_wr);
}

//Schreiben eines Zeichens in EEPROM
boolean eeprom_write (int addr, char c) {
  if (addr < speicherplatz - 1) {
    if (c != '\n') EEPROM.write(addr, c);
    addr_wr++;
    return true;
  }
  else return false;

}

//Ausgabe der Konversation
void usb_ausgabe () {
  Serial.println("-----------------------------------------------------");
  Serial.println("LauschArduino: Ausgabe der aufgezeichneten Konversation:");
  while (addr_re < speicherplatz) {
    char value = EEPROM.read(addr_re);
    if (value == '<' || value == '>') Serial.print("\n\n");
    if (value == '<') Serial.print('\t');
    Serial.print(value);
    if (value == '<' || value == '>') Serial.print(' ');
    addr_re++;
  }

  //Leseadresse zurücksetzen
  addr_re = 0;

  //Mitgesendetes ENTER auch noch auslesen
  Serial.read();

  //Bei Bedarf EEPROM leeren
  Serial.println("\n-----------------------------------------------------");
  Serial.println("Ende der Konversation. Clear EEPROM? [mit Ausgabebefehl bestaetigen]");

  while (Serial.available() < 1) ;
  if (Serial.read() == AUSGABEBEFEHL) {
    Serial.print("CLEARING EEPROM, PLEASE WAIT... ");
    //Werte zurücksetzen
    addr_wr = 3; EEPROM.write(2, 3);
    addr_re = 3; EEPROM.write(1, 3);
    //Restliche Daten löschen
    for (int i = 3 ; i < speicherplatz ; i++) {
      EEPROM.write(i, 0);
    }
    Serial.println("FINISHED");
  }
  Serial.println("-----------------------------------------------------");
}

#endif
