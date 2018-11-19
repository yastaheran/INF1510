//Importerer biblioteker til RFID leser
//#include <SPI.h>
//#include <MFRC522.h>

//Importerer bibliotek for lyslenke
//#include <Adafruit_NeoPixel.h>

//Definere PINs som RFID leseren skal bruke
//#define SS_PIN 10
//#define RST_PIN 9


//Knappen som kan trykkes når alle oppgaver er gjort
//const int ferdigBtn = 8;
//int btnState = 0;

//LED-lenken (Regnbuen)
//const int neoLedPin = 6;
//Adafruit_NeoPixel neoStrip =  Adafruit_NeoPixel(60, neoLedPin, NEO_GRB + NEO_KHZ800);

//Oppretter en klasse for initialisering av RFID leser og nøkkel
//MFRC522 rfid(SS_PIN, RST_PIN);

/**
 * Oppretter en array som holder på ID til NFC tag på RFID-leseren
 * som senere skal bli brukt for inn- og utsjekk av oppgaver.
 */
//byte idLager[8][4];

//Variabel for aktive oppgaver
//int oppgaveNr = 0;
int teller = 0;
//int antLed = 0; //Antall lys som skal på, representerer antall oppgaver registrert

//Variable for avlsuttet oppgaver
//const int antBlink = 5;
//int antLedFerdig = 0; //Antall oppgaver som er gjort

void setup() {
  Serial.begin(9600);
  
  //Gjør klar komponentene i RFID leseren
  SPI.begin();
  rfid.PCD_Init();

  //Setter opp NeoPixel objekter
  neoStrip.begin();
  neoStrip.show();

  //Aktiverer neoLedPin PIN-en
  pinMode(neoLedPin,OUTPUT);
  
  //Arkadeknapp/Ferdigknapp
  pinMode(ferdigBtn, INPUT);
  
}

void loop() {
  rfidScan();
}

/**
 * Leser RFID-kortet og lagrer ID-en
 */
void rfidScan() {
  if (!rfid.PICC_IsNewCardPresent()) {
    delay(20);
    return;
  }
  
  if(!rfid.PICC_ReadCardSerial()) {
    return;
  } 
  
  lagreID(rfid.uid.uidByte, rfid.uid.size);
}

/**
 * Funksjon som lagrer ID-en i idLager[][]
 */
void lagreID(byte *buffer, byte bufferSize) {
  int lednr = 0;
  for(int i = 0; i < 8; i++) {
    for(int j = 0; j < 4; j++ ) {
      if(idLager[i][j] != 0) {
        idLager[i][j] = buffer[j];
        lednr = i;
        lysPaa(lednr);
        Serial.println("Lagret");
      } else if(idLager[i][j] == buffer[j]) {
        lednr = i+1;
        slettID(i, lednr);
        Serial.println("Slettet");
      }
    }
  }
}

/**
 * Sletter ID dersom id-en allerede er lagret i filen. Dette betyr at oppgaven er gjort.
 */
void slettID(int idnr, int lednr) {
  for(int i = 0; i < 4; i++) {
    idLager[idnr][i] = 000; 
  }
  blinkLed(lednr);
  antLedFerdig++;
  ferdig();
}
/**
 * Setter LED-lyset på når oppgave er registrert. 
 * param lednr: forteller systemet hvilket LED-lys som skal på
 */
void lysPaa(int lednr) {
  if(lednr == 1) {
    //Setter LED-lyset til Rød
    neoStrip.setPixelColor(lednr, 255, 0, 0);
    neoStrip.
  } else if(lednr == 2) {
    //Setter LED-lyset til Oransj
    neoStrip.setPixelColor(lednr, 255, 128, 0);
  } else if(lednr == 3) {
    //Setter LED-lyset til Gul
    neoStrip.setPixelColor(lednr, 255, 255, 0);
  } else if(lednr == 4) {
    //Setter LED-lyset til Grønn
    neoStrip.setPixelColor(lednr, 0, 255, 0);
  } else if(lednr == 5) {
    //Setter LED-lyset til Blå
    neoStrip.setPixelColor(lednr, 0, 0, 255);
  } else if(lednr == 6) {
    //Setter LED-lyset til Turkis/Lysblå
    neoStrip.setPixelColor(lednr, 0, 255, 255);
  } else if(lednr == 7) {
    //Setter LED-lyset til Lilla
    neoStrip.setPixelColor(lednr, 75, 0, 130);
  } else if(lednr == 8) {
    //Setter LED-lyset til Rosa
    neoStrip.setPixelColor(lednr, 255, 20, 147);
  }
  neoStrip.setBrightness(255);
  neoStrip.show();  
  antLed++;
}

/**
 * Setter LED-lyset av når oppgave er registrert.  BYTTE TIL NÅR EN OPPGAVE ER REGISTRERT
 * param lednr: forteller systemet hvilket LED-lys som skal av
 */
void ledAv(int lednr){
  neoStrip.setPixelColor(lednr, 0, 0, 0);
  neoStrip.show();
}

/**
 * LED-lys for en gitt oppgave blinker et gitt antall ganger,
 * før den slåes av.
 * param lednr: forteller systemet hvilket led-lys som skal blinke
 */
void blinkLed(int lednr) {
  boolean statusLed = false;  
  for(int i = 0; i < antBlink; i++) {
    if(statusLed) {
      lysPaa(lednr);
      delay(300); 
    } else {
      ledAv(lednr);
      delay(300);
    }   
    statusLed = !statusLed;
  }
  ledAv(lednr);
}

/**
 * Sjekker om alle oppgaver er gjort.
 */
void ferdig() {
  if(antLedFerdig == 8) {
    digitalWrite(ferdigBtn, HIGH);    
  }
}
