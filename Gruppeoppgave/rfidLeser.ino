#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9
#define SS_PIN          10
MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600); 
  while (!Serial);
  SPI.begin();
  mfrc522.PCD_Init();
}

void loop() {
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }
  dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size);
}

void dump_byte_array(byte *buffer, byte bufferSize) {
  Serial.println("Start Dump");
  for (byte i = 0; i < bufferSize; i++) {
   // Serial.print(buffer[i] < 0x10 ? "0" : ""); 
    Serial.println(buffer[i]);
  }
  Serial.println();
  delay(1000);
}
