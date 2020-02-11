/*
Written, maintained by : Sébastien Albert
V 0.0.1
*/

#include <NFCWrapper.h>
#include <cnam_game.h>


#define CTRL_LED 13

#define PIN_GREEN_LIGHT 10
#define PIN_RED_LIGHT   11
#define PIN_WHITE_LIGHT 12

NFCMifareWrapper NfcWrapper;
CnamGame cnamGame;

void setup() {
  // Init the serial
  Serial.begin(115200);

  pinMode(CTRL_LED, OUTPUT);
  pinMode(PIN_GREEN_LIGHT, OUTPUT);
  pinMode(PIN_RED_LIGHT, OUTPUT);
  pinMode(PIN_WHITE_LIGHT, OUTPUT);

  // Init the NFC Shield  // NFC Init -------------------------------------
  Serial.println("NDEF Writer");
  NfcWrapper.setup();
  // NFCInit();

}

// NO TAG !
void lightsShutOff(){
  // All lights Off
  digitalWrite(PIN_GREEN_LIGHT, HIGH);
  digitalWrite(PIN_RED_LIGHT,   HIGH);
  digitalWrite(PIN_WHITE_LIGHT, HIGH);

  Serial.println("All lights shut off. ================");

}
// The right tag
void greenLights(){
  // Green and white on together
  digitalWrite(PIN_GREEN_LIGHT, LOW);
  digitalWrite(PIN_WHITE_LIGHT, LOW);
  // Red off
  digitalWrite(PIN_RED_LIGHT,   HIGH);

  Serial.println("Good answer !!! Say hey !!! +++++++++");

}
// The wrong tag
void redLights(){
  // Green and white on together
  digitalWrite(PIN_GREEN_LIGHT, HIGH);
  digitalWrite(PIN_WHITE_LIGHT, HIGH);
  // Red off
  digitalWrite(PIN_RED_LIGHT,   LOW);

  Serial.println("Bade answer !!! Say Boo !!! --------");

}

void loop() {

  if (NfcWrapper.isTagPresent()) {
    // We got a tag, ask an answer
    String valueString = NfcWrapper.readMifareBlock(4);

    Serial.print("Tag present : ");
    Serial.println(valueString);

    if(cnamGame.isTagOk(valueString) == true){
      greenLights();
    }else{
      redLights();
    }

  }else{
    lightsShutOff();
  }

  //
  // return newTag;
  //
  //
  // char currentTag = nfcGetNewTag();
  //
  // // --------------------------------------------------
  // // IN = First, I had no tag and I put it in
  // // --------------------------------------------------
  // if (lastTag == TAGR_EMPTY && currentTag != TAGR_EMPTY) {
  //   // -------------------------------------------
  //   Serial.print("Brand New Tag : [");
  //   Serial.print(String(currentTag));
  //   Serial.println("]");
  //
  //   /*
  //   DO Something --------------------------------------
  //   */
  //
  //   lastTag = currentTag;
  // }
  //
  // // --------------------------------------------------
  // // OUT = Second, I had a tag and put it out
  // // --------------------------------------------------
  // else if (lastTag != TAGR_EMPTY && currentTag == TAGR_EMPTY) {
  //   // -------------------------------------------
  //   Serial.print("Removed old Tag : [");
  //   Serial.print(String(lastTag));
  //   Serial.println("]");
  //
  //   /*
  //   DO Something --------------------------------------
  //   */
  //
  //   lastTag = currentTag;
  // }
  //
  // // --------------------------------------------------
  // // nothing, print a dot
  // // --------------------------------------------------
  // else {
  //   Serial.print("Current Tag : [");
  //   Serial.print(String(currentTag));
  //   Serial.print("]");
  //   Serial.print(" Last Tag : [");
  //   Serial.print(String(lastTag));
  //   Serial.println("]");
  //
  //   /*
  //   ShutAllDown --------------------------------------
  //   */
  //
  //
  // }

}
