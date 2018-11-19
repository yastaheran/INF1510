#include <Adafruit_NeoPixel.h>

//Er 0 hvis porten som lyttes på er LOW, er 1 ellers
int switchState = 0;

//PIN som gir OUTPUT til NeoPixel-ledet
int neoLedPin = 9;

//Definerer første og siste PIN som skal brukes til
const int forsteLedPin = 2;
const int sisteLedPin = 7;

/*
 * Definerer første og siste PIN som skal lytte etter signalet fra Master
 * arduinoen. PINs i intervallet mellom disse vil også bli brukt til dette.
 */
const int forsteLyttePin = 10;
const int sisteLyttePin = 13;

Adafruit_NeoPixel neoStrip = Adafruit_NeoPixel(60, neoLedPin, NEO_GRB + NEO_KHZ800);

//Tider til de forskjellige oppgavene i millisekunder
//const unsigned long tider[] = {100000,10000,10000,100000};

//Variable for lagring av tid
//unsigned long prevTime = 0;

//Antall Led i nedtelling
const int antLed = (sisteLedPin-forsteLedPin) + 1;

//Antall blink
//int antBlink = 8;

//Tid pr blink i millisekunder
//int tidBlink = 300;

//Variabel for aktiv oppgave
int oppgaveNr = 0;

void setup() {
  //Setter opp neoPixel objekter
  neoStrip.begin();
  neoStrip.show();

  //Setter opp lytte PINs
  for(int pinNr = forsteLyttePin; pinNr <= sisteLyttePin; pinNr++) {
    pinMode(pinNr, INPUT);
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
