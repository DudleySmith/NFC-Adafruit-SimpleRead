#ifndef EEPROMWrapper_Guard
#define EEPROMWrapper_Guard

#include <Arduino.h>
#include <EEPROM.h>

void writeString(char addr,String data);
String readString(char addr);

#endif /* end of include guard: EEPROMWrapper */
