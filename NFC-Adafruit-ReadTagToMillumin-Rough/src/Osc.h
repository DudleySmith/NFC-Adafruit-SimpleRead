/*
   OSC File :
   1/ Connect into UDP via Wifi
   2/ Send OSC Command
*/

#include <Arduino.h>
//#include "NCNS-ArduinoTools.h"

#define CTRL_LED 13

// Wifi Dependencies ----------------------------
#include <WiFiLink.h>
#include <WiFiUdp.h>

// OSC Dependencies -----------------------------
#include <OSCMessage.h>

// -------------------------------------------------
// Wifi Section
// -------------------------------------------------
char ssid[] = "linksys-MedenAgan";          // your network SSID (name)
char pass[] = "Edwood72";                    // your network password

WiFiUDP Udp;
const unsigned int localPort = 2390;        // local port to listen for UDP packets (here's where we send the packets)

// -------------------------------------------------
// OSC Section
// -------------------------------------------------
//destination IP
IPAddress outIp(192, 168, 2, 31);
const unsigned int outPort = 5000;

// -------------------------------------------------
// Specials Eurocave Section
// -------------------------------------------------
#define X_BASE_COL 2
#define S_BASE_COL 10
#define M_BASE_COL 18
#define L_BASE_COL 26

#define IN_BONUS  0
#define OUT_BONUS 1

//int xColBonus, sColBonus, mColBonus, lColBonus;
int numVignette;

  // ----------------------------------------------------------
// Do blink a led without delay
// First you have to setup your pin with this line below
// pinMode(LED_BUILTIN, OUTPUT);
// ----------------------------------------------------------
void ledBlink(unsigned int _led, unsigned int _delayMs) {
  float alternativeSignal = (millis() % _delayMs) / (float)_delayMs;
  if (alternativeSignal > 0.5) {
    digitalWrite(_led, HIGH);
  } else {
    digitalWrite(_led, LOW);
  }
}

void OscInit() {

  randomSeed(analogRead(0));

  // IPs are static, DHCP does not look easy with arduino
  // My static IP
  IPAddress ip = IPAddress(192, 168, 2, 11);

  // WiFi Init --------------------------------
  byte mac[6];
  WiFi.macAddress(mac);
  Serial.print("MAC Address: ");
  Serial.print(mac[0], HEX);
  Serial.print(":");
  Serial.print(mac[1], HEX);
  Serial.print(":");
  Serial.print(mac[2], HEX);
  Serial.print(":");
  Serial.print(mac[3], HEX);
  Serial.print(":");
  Serial.print(mac[4], HEX);
  Serial.print(":");
  Serial.println(mac[5], HEX);

  Serial.print("Connecting to SSID [");
  Serial.print(ssid);
  Serial.print("] pass [");
  Serial.print(pass);
  Serial.println("]");

  WiFi.config(ip);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    // Blink Led
    ledBlink(CTRL_LED, 50);
  }

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  Serial.println("Starting UDP");
  Udp.begin(localPort);
  Serial.print("Local port: ");
  Serial.println(localPort);

  // Init the column bonuses
  /*
  xColBonus = random(4);
  sColBonus = random(4);
  mColBonus = random(4);
  lColBonus = random(4);
  numVignette = random(3);
  */
}

/*
   Check and comment via Serial
*/
void wifiCheck() {

  // Control the connection (led #0)
  if (WiFi.status() != WL_CONNECTED) {
    // not connected => Message + Blink Short
    Serial.println("Wifi Not Connected :(");
    ledBlink(CTRL_LED, 50);
  }

}

int incBonus(int _bonus) {
  // Increment
  _bonus++;
  // If you go too far, come back !
  if (_bonus >= 4) {
    _bonus = 0;
  }

  return _bonus;

}
/*
int getNextBonus(char _tag) {

  if (_tag == 'X' || _tag == 'x') {
    // -----------------------------------
    xColBonus = incBonus(xColBonus);
    return xColBonus;
  } else if (_tag == 'S' || _tag == 's') {
    // -----------------------------------
    sColBonus = incBonus(sColBonus);
    return sColBonus;
  } else if (_tag == 'M' || _tag == 'm') {
    // -----------------------------------
    mColBonus = incBonus(mColBonus);
    return mColBonus;
  } else if (_tag == 'L' || _tag == 'l') {
    // -----------------------------------
    lColBonus = incBonus(lColBonus);
    return lColBonus;
  }

  return 0;

}
*/
/*
int getCurrentBonus(char _tag) {

  if (_tag == 'X' || _tag == 'x') {
    // -----------------------------------
    return xColBonus;
  } else if (_tag == 'S' || _tag == 's') {
    // -----------------------------------
    return sColBonus;
  } else if (_tag == 'M' || _tag == 'm') {
    // -----------------------------------
    return mColBonus;
  } else if (_tag == 'L' || _tag == 'l') {
    // -----------------------------------
    return lColBonus;
  }

  return 0;

}
*/
int getColumnIdx(char _tag) {

  int columnIdx = -1;

  if (_tag == 'X' || _tag == 'x') {
    // -----------------------------------
    columnIdx = X_BASE_COL;
  } else if (_tag == 'S' || _tag == 's') {
    // -----------------------------------
    columnIdx = S_BASE_COL;
  } else if (_tag == 'M' || _tag == 'm') {
    // -----------------------------------
    columnIdx = M_BASE_COL;
  } else if (_tag == 'L' || _tag == 'l') {
    // -----------------------------------
    columnIdx = L_BASE_COL;
  }

  return columnIdx;

}

void sendIt(String _address, uint8_t _intValue) {

  char _addr[255];
  _address.toCharArray(_addr, 255);

  Serial.print("Sending message Addr=");
  Serial.print(_address);
  Serial.print(" Value=");
  Serial.print(String(_intValue, DEC));
  Serial.print(" To : ");
  Serial.print(outIp);
  Serial.print(",");
  Serial.println(outPort);

  OSCMessage msg(_addr);

  msg.add(_intValue);

  Udp.beginPacket(outIp, outPort);
  msg.send(Udp); // send the bytes to the SLIP stream
  Udp.endPacket(); // mark the end of the OSC Packet
  msg.empty(); // free space occupied by message

}

// ------------------------------------------------------------
// Sending TAG
// To send a tag :
// 1st step : get the base column index
// 2st step : set a bonus
//    - bonus to In animation = 0
//    - bonus to Out animation = 1
// 3rd step : get a second bonus value determined by the decorum style you want
// ------------------------------------------------------------

void sendTag(char _tag, int _inOutBonus, int _colBonus) {

  int columnIdx = getColumnIdx(_tag);
  Serial.print("Column idx : ");
  Serial.println(columnIdx);
  
  if (columnIdx >= 1) {
    // Idx is right, send it !
    // Launch a column --
    sendIt("/millumin/action/launchColumn", 26);
    //sendIt("/millumin/action/launchColumn", _inOutBonus + 2 * _colBonus + columnIdx);

    if (_inOutBonus == IN_BONUS) {
      // But Change the vignette (X, S , M ou L)
      if (_tag == 'X') {
        sendIt("/millumin/VignetteX/media/time", 10 * numVignette);
      } else if (_tag == 'S') {
        sendIt("/millumin/VignetteS/media/time", 10 * numVignette);
      } else if (_tag == 'M') {
        sendIt("/millumin/VignetteM/media/time", 10 * numVignette);
      } else if (_tag == 'L') {
        sendIt("/millumin/VignetteL/media/time", 10 * numVignette);
      }
      // Incremente le numéro de vignette
      numVignette++;
      if (numVignette > 3) {
        numVignette = 0;
      }

    }

  } else {
    // not right, print a tip
    Serial.print("Column Idx is out of range, probably wrong tag (");
    Serial.print(_tag);
    Serial.print(",");
    Serial.print(")");
    Serial.println();
  }

}


