//Importerer nødvendige biblioteker
#include <SPI.h>
#include <MFRC522.h>
#include <Adafruit_NeoPixel.h>
#include <SdFat.h>
#include <SdFatUtil.h>
#include <Wire.h>

//Definere PINs som skal brukes
#define SS_PIN 10
#define RST_PIN 9
#define arcade_btn 4
#define arcade_btn_LED 3
const int neoLedPin = 6;
const int btnStartProsess = 5;

//Oppretter klasser av NeoPixel, MFRC522
Adafruit_NeoPixel neoStrip =  Adafruit_NeoPixel(60, neoLedPin, NEO_GRB + NEO_KHZ800);
MFRC522 rfid(SS_PIN, RST_PIN);

/**
   En array som holder på ID til RFID-kortene
   som senere skal bli brukt for inn- og utsjekk av oppgaver.
*/
byte idLager[8][4] = { 0 };

/**
 * en array som har alle ID-ene til rfid-kortene. skal brukes til
 * å verfisere om et kort er gyldig
 */
byte gjoremal[12][4] = {
  {208, 107, 135, 124}, //rad 0: Støvsuging
  {112, 182, 139, 124}, //rad 1: Vaske klær
  {160, 199, 93, 126}, //rad 2: Henge opp klær
  {144, 200, 88, 126}, //rad 3: Trening
  {160, 80, 145, 124}, //rad 4: Dusje
  {80, 124, 143, 124}, //rad 5: Sette inn i oppvaskmaskin
  {96, 119, 92, 126}, //rad 6: Ta ut av oppvaskemaskin
  {96, 139, 88, 126}, //rad 7: Tømme søppel
  {96, 119, 138, 124}, //rad 8: Pusse tenner
  {224, 236, 136, 124}, //rad 9: Lage mat
  {144, 199, 93, 126}, //rad 10: Dra på jobb
  {96, 172, 143, 124} //rad 11: Gå på tur/frisk luft
};

//Variabler for aktiverte oppgaver
int lednr = 0; //hvilken rekke som skal på
int antLed = 0; //hvor mange lys som skal på til slutt
int antBlink = 5; //Lyset for oppgaven blinker fem ganger

//Variabler for avsluttete oppgaver
int ferdigBelonning = 0; //Antall oppgaver utført

//Knappenes tilstand
int btnStateFerdig = LOW;

//variabler for debounce      
bool button2Pressed = false;      
int button2PushCounter = 0;     
int button2State = 0;     
int button2LastState = 0;

//Variabler for mp3
char trackName[] = "track001.mp3"; // antar at filen heter "track001.mp3"
uint8_t result;

void setup() {
  Serial.begin(9600);
  Serial.println("Legg på kort");

  Wire.begin(2); //gjør klar koblingen mellom arduinoene.

  SPI.begin();
  rfid.PCD_Init();

  neoStrip.begin();
  neoStrip.show();
  pinMode(neoLedPin, OUTPUT);

  pinMode(btnStartProsess, INPUT);
  pinMode(arcade_btn, INPUT_PULLUP);
  pinMode(arcade_btn_LED, OUTPUT);

  //Slår av lyset til Arkadeknappen
  analogWrite(arcade_btn_LED, 255);

  while(digitalRead(btnStartProsess) == LOW) {
    Serial.println("Venter på startsignal");
  }
}

void loop() {
  btnStateFerdig = digitalRead(arcade_btn);
  if (btnStateFerdig == HIGH && ferdigBelonning == 8) {
    belonning(btnStateFerdig);
  }
  
  if (!rfid.PICC_IsNewCardPresent()) {
    delay(200);
    return;
  }

  if (!rfid.PICC_ReadCardSerial()) {
    return;
  }

  //Lagrer id-en i en array
  byte id[4];
  for (byte i = 0; i < 4; i++) {
    id[i] = rfid.uid.uidByte[i];
  }

  for (int i = 0; i < 12; i++) {
    //sjekker om id-en finnes i gjoremal
    if (gjoremal[i][0] == id[0] && gjoremal[i][1] == id[1] && gjoremal[i][2] == id[2] && gjoremal[i][3] == id[3]) {
      lagreID(i);
    }
  }
}


/**
*  Funksjon som lagrer ID-en i idLager[][]. Når en ID-er registrert
*  vil lysrekka for den ID-en blinke.
*  param r: forteller hvilken rad i gjoremal id-en ligger i
*/
void lagreID(int r) {
  if (lednr == 0) {
    if (isEmpty(idLager) == true) {
      leggInn(r, 0);
    } else {
      Serial.print("Error: ikke tom array, men lednr == 0");
    }
  } else if (lednr > 0 && lednr <= 8) {
    if (isFull(idLager) == false && lednr != 8) {
      for (int i = 0; i < 8; i++) {
        if ((idLager[i][0] == 0) && (idLager[i][1] == 0) && (idLager[i][2] == 0) && (idLager[i][3] == 0)) {
          leggInn(r, i);
          return; //går tilbake til loopen, etter at gjøremålet er registret, for å unngå duplisering
        }
      }
    } else if (isFull(idLager) == true) {
      for (int i = 0; i < 8; i++) {
        //hvis gjøremålet allerede er registrert skal den slettes fra idLager
        if ((idLager[i][0] == gjoremal[r][0]) && (idLager[i][1] == gjoremal[r][1]) && (idLager[i][2] == gjoremal[r][2]) && (idLager[i][3] == gjoremal[r][3])) {
          slettID(i);
          ferdigBelonning++;
        }
      }
    }
  } else {
    Serial.print("Error: ugyldig lednr ");
    Serial.println(lednr);
  }
}

/**
*  Sletter ID dersom id-en allerede er lagret i filen. Dette betyr at oppgaven er gjort.
*  param idnr: refferer til hvilken rad som skal fjernes
*  param lednr: refferer til hvilken LED-rekke som skal på
*/
void slettID(int idnr) {
  for (int i = 0; i < 4; i++) {
    idLager[idnr][i] = 1;
  }
  ledPaa(idnr);
}

/**
* LED-lysrekke for en gitt oppgave blinker et gitt antall ganger,
* før den slåes av. Denne blir kalt når en oppgave er registrert.
* param rekke: forteller systemet hvilket led-lys som skal blinke
*/
void blinkLedRekke(int rekke) {
  for (int i = 0; i < antBlink; i++) {
    ledPaa(rekke);
    delay(300);
    ledAv(rekke);
    delay(100);
  }
  antLed += 4;
}

/**
*  Setter LED-lysrekke på når den blir kalt.
*  param rekke: forteller systemet hvilket LED-rekke som skal på
*/
void ledPaa(int rekke) {
  if (rekke == 0) {
    //Setter LED-lyset til Rød
    for (int led = 0; led < 4; led++) {
      neoStrip.setPixelColor(led, 255, 0, 0);
    }
  } else if (rekke == 1) {
    //Setter LED-lyset til Oransj
    for (int led = 4; led < 8; led++) {
      neoStrip.setPixelColor(led, 255, 125, 0);
    }
  } else if (rekke == 2) {
    //Setter LED-lyset til Gul
    for (int led = 8; led < 12; led++) {
      neoStrip.setPixelColor(led, 255, 255, 0);
    }
  } else if (rekke == 3) {
    //Setter LED-lyset til Grønn
    for (int led = 12; led < 16; led++) {
      neoStrip.setPixelColor(led, 0, 128, 0);
    }
  } else if (rekke == 4) {
    //Setter LED-lyset til Blå
    for (int led = 16; led < 20; led++) {
      neoStrip.setPixelColor(led, 0, 0, 255);
    }
  } else if (rekke == 5) {
    //Setter LED-lyset til Lysblå
    for (int led = 20; led < 24; led++) {
      neoStrip.setPixelColor(led, 0, 255, 255);
    }
  } else if (rekke == 6) {
    //Setter LED-lyset til Lilla
    for (int led = 24; led < 28; led++) {
      neoStrip.setPixelColor(led, 75, 0, 130);
    }
  } else if (rekke == 7) {
    //Setter LED-lyset til Rosa
    for (int led = 28; led < 32; led++) {
      neoStrip.setPixelColor(led, 255, 20, 147);
    }
  }
  neoStrip.setBrightness(255);
  neoStrip.show();
}

/**
*  Setter LED-lyset av når oppgave er registrert.  BYTTE TIL NÅR EN OPPGAVE ER REGISTRERT
*  param rekke: forteller systemet hvilket LED-lys rekke som skal av
*/
void ledAv(int rekke) {
  if (rekke == 0) {
    for (int led = 0; led < 4; led++) {
      neoStrip.setPixelColor(led, 0, 0, 0);
    }
  } else if (rekke == 1) {
    for (int led = 4; led < 8; led++) {
      neoStrip.setPixelColor(led, 0, 0, 0);
    }
  } else if (rekke == 2) {
    for (int led = 8; led < 12; led++) {
      neoStrip.setPixelColor(led, 0, 0, 0);
    }
  } else if (rekke == 3) {
    for (int led = 12; led < 16; led++) {
      neoStrip.setPixelColor(led, 0, 0, 0);
    }
  } else if (rekke == 4) {
    for (int led = 16; led < 20; led++) {
      neoStrip.setPixelColor(led, 0, 0, 0);
    }
  } else if (rekke == 5) {
    for (int led = 20; led < 24; led++) {
      neoStrip.setPixelColor(led, 0, 0, 0);
    }
  } else if (rekke == 6) {
    for (int led = 24; led < 28; led++) {
      neoStrip.setPixelColor(led, 0, 0, 0);
    }
  } else if (rekke == 7) {
    for (int led = 28; led < 32; led++) {
      neoStrip.setPixelColor(led, 0, 0, 0);
    }
  }
  neoStrip.show();
}

/**
   Legger inn gjøremal inn i idLager
   param rg: rad i gjoremal
   param ri: rad i idLager
*/
void leggInn(int rg, int ri) {
  for (int j = 0; j < 4; j++) {
    idLager[ri][j] = gjoremal[rg][j];
  }

  blinkLedRekke(lednr);
  lednr++;
}

/**
*  Sjekker om arrayen er tom ved å gå igjennom hver kolonne og hver rad.
*  Returnerer true hvis den er tom, false ellers.
*  param arr: arrayen vi skal sjekke.
*/
bool isEmpty(byte arr[][4]) {
  int tomteller = 0;
  int tomrad = 0;

  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 4; j++) {
      if (arr[i][j] == 0) {
        tomteller++;
      }
    }

    if (tomteller == 4) {
      tomrad++;
      tomteller = 0; //setter tomteller til 0 etter at hver rad er sjekket
    } else {
      tomteller = 0;
    }
  }

  if (tomrad == 8) {
    return true;
  }

  return false;
}

/**
*  Sjekker om idLager er full.
*  param arr: arrayen vi skal sjekke
*/
bool isFull(byte arr[][4]) {
  int teller = 0;
  int fullrad = 0;

//  Serial.println("Sjekker om idLager er full");
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 4; j++) {
      if (arr[i][j] != 0) {
        teller++;
      }
    }

    if (teller == 4) {
      fullrad++;
      teller = 0; //setter tomteller til 0 etter at hver rad er sjekket
    } else {
      teller = 0;
    }
  }

  if (fullrad == 8) {
    return true;
  }
  return false;
}

/**
   spiller av musikk når alle oppgavene er gjort.
   sender info til den andre arduinoen om dette slik
   at musikken kan spilles.
*/
void belonning(int btnState) {
  int x = 0;
  Serial.println(btnState);
  
  if (btnState != button2LastState && button2Pressed == false) {
   
    if (btnState == HIGH) {
      Serial.println("knappen er trykket");
      Wire.beginTransmission(8); // transmit to device #8
      Wire.write(x);              // sends one byte
      Wire.endTransmission();    // stop transmitting

      x++;
      delay(500);
    } else {
      Serial.println("knappet er ikke trykket");
    }
  }
  button2LastState = button2State;
}
