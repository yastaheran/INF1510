//2.2. Pulserende lys
int ledPin = 3;
int potPin = 5;
int styrke;

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  styrke = analogRead(potPin)/4;
  analogWrite(ledPin, styrke);
}


//Oppgave 2.2.4 andre komponenter man kan bruke: photoresistor.
//Oppgave 2.2.5. Ja, det er mulig ettersom den endrer motstand når man skrur på den.
