#include <Arduino.h>
#include <EEPROMWrapper.h>

void setup() {

  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

}

void readMe(){
  String s = readString(0);

  Serial.print("EEPROM read, Game setup is ");
  Serial.println(s);

}

void loop() {

  if (Serial.available()) {
    char charRead = Serial.read();

    Serial.print("Instruction sent : ");
    Serial.println(charRead);

    if(charRead == '1'){
      // Write ID
      writeString(0, "COCO");readMe();

    }else if (charRead == '2') {
      // Write ID
      writeString(0, "PRLV");readMe();

    }else if (charRead == '3') {
      // Write ID
      writeString(0, "PYRO");readMe();

    }else if (charRead == '4') {
      // Write ID
      writeString(0, "COEU");readMe();

    }else if (charRead == '5') {
      // Write ID
      writeString(0, "CAGE");readMe();

    }else if (charRead == '6') {
      // Write ID
      writeString(0, "ISOC");readMe();

    }else if (charRead == '7') {
      // Write ID
      writeString(0, "BIPD");readMe();

    }else if (charRead == '8') {
      // Write ID
      writeString(0, "COLN");readMe();

    }else if (charRead == '?') {
      readMe();

    }else{
      // Nothing ------------------------
    }

  }
}
