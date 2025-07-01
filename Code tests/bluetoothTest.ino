#include <SoftwareSerial.h>

SoftwareSerial BT(A0, A1); // RX (TX HC-05), TX(RX HC-05)

void setup() {
  Serial.begin(9600);
  BT.begin(9600);      // HC-05
  Serial.println("Waiting for data...");
}

void loop() {
  if (BT.available()) {
    char c = BT.read();
    Serial.print(c);
  }
}
