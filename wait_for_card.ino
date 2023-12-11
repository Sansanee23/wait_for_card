#include <SoftwareSerial.h>
SoftwareSerial RFID(5, 4); // RX and TX

String text;
String CardNumber = "1100773C55";

const int WAIT_FOR_CARD = 1;
const int CONFIRMATION = 2;
const int SELECT_JOB = 3;
const int BACKFLUSH = 4;
const int REWORD = 5;
const int DOWNTIME = 6;

int state;
bool cardPresent = false;

void setup() {
  Serial.begin(9600);
  Serial.println("Bring your RFID Card Closer...");
  RFID.begin(9600);
  state = WAIT_FOR_CARD;
  
}

void loop() {

  if (state == WAIT_FOR_CARD) {
    Serial.println("Bring your RFID Card Closer...");

    // Reset cardPresent flag
    cardPresent = false;

    while (!RFID.available()) {  
      delay(100);
    }

    char c;
    while (RFID.available()) {
      c = RFID.read();
      if (c == '\n') {
        break;
      }
      text += c;
      delay(5);
    }

    if (text.length() > 0) {
      Serial.println("Card ID : " + text);
      Serial.println("Access ID : " + CardNumber);

      if (CardNumber == text) {
        Serial.println("Access accepted");
        cardPresent = true; // Set cardPresent to true if the card is accepted
      } else {
        Serial.println("Access denied");
      }

      text = "";
      state = CONFIRMATION;
    }
  } else if (state == CONFIRMATION) {
    // Add code for confirmation here

    // Reset state to WAIT_FOR_CARD if card is not present
    if (!cardPresent) {
      state = WAIT_FOR_CARD;
    }
  } else if (state == SELECT_JOB) {
    // Add code for job selection here
  } else if (state == BACKFLUSH) {
    // Add code for backflush here
  } else if (state == DOWNTIME) {
    // Add code for downtime here
  }

  delay(1000);
}
