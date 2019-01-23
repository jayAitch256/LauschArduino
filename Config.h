/*
--------------------------------------------------------------------------------------
Config-Datei LauschArduino

Damit Änderungen wirksam werden, muss der Sketch neu auf den Arduino hochgeladen werden!
--------------------------------------------------------------------------------------
ZUM AKTIVIEREN ODER DEAKTIVIEREN VON OPTIONEN AUSKOMMENTIEREN BZW KOMMENTARSTRICHE VOR DEM 'DEFINE' LÖSCHEN

*/

#ifndef Config_h
#define Config_h

#include <Arduino.h>


//BAUD RATES
#define USB_BAUDRATE 9600
#define SERIAL1_BAUDRATE 9600

//Speichern der Konversation von Arduino und PC
//#define SPEICHERN

//Ausgabebefehl
//Nach Eingabe von diesem wird eine gespeicherte
//Konversation auf dem PC ausgegeben 
#define AUSGABEBEFEHL '|'

//Verwendeter EEPROM-Speicher, in Bytes
//(falls nicht angegeben, wird die volle Speicherkapazität ausgeschöpft)
//#define SPEICHER 1000


#endif
