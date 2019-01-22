/*
--------------------------------------------------------------------------------------
Config-Datei LauschArduino

Damit Änderungen wirksam werden, muss der Sketch neu auf den Arduino hochgeladen werden!
--------------------------------------------------------------------------------------
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
ZUM AKTIVIEREN ODER DEAKTIVIEREN VON OPTIONEN AUSKOMMENTIEREN BZW KOMMENTARSTRICHE VOR DEM 'DEFINE' LÖSCHEN
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
*/

#ifndef Config_h
#define Config_h

#include <Arduino.h>

//Pins
#define HOMING_AZM 50
#define HOMING_ALT 51
#define HOMING_SWITCH 12

//Startposition
#define HOME_AZM "00:00:00#"
#define HOME_ALT "00:00:00#"

//BAUD RATES
#define USB_BAUDRATE 9600
#define SERIAL1_BAUDRATE 9600

//Speichern der Konversation
//#define SPEICHERN

//Ausgabebefehl
#define AUSGABEBEFEHL '|'

//Verwendeter EEPROM-Speicher, in Bytes
//(falls nicht angegeben, wird die volle Speicherkapazität ausgeschöpft)
//#define SPEICHER 1000


#endif
