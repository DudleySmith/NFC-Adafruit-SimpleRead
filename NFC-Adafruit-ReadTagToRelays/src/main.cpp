/*
Written, maintained by : Sébastien Albert
V 0.0.1
*/

#include "NFC.h"

#define CTRL_LED 13

void setup() {
  // Init the serial
  Serial.begin(115200);
  pinMode(CTRL_LED, OUTPUT);
  // Init the NFC Shield  // NFC Init -------------------------------------
  Serial.println("NDEF Writer");
  NfcWrapper.setup();
  // NFCInit();

}

void loop() {

  if (NfcWrapper.isTagPresent()) {
    // We got a tag, ask an answer
    String valueString = NfcWrapper.readMifareBlock(4);

    Serial.print("Tag present : ");
    Serial.println(valueString);

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