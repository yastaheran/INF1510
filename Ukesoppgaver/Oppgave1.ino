//Oppgave 2.1.Sos signal
int buttonPin = 2;
int ledPin = 3
int buttonState;

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  buttonState = digitalRead(buttonPin);

  if(buttonState == HIGH) {
    sos();    
  } else {
    digitalWrite(ledPin, LOW);
  }
}

void sos() {
  kortSig();
  delay(3000);
  langSig();
  delay(3000);
  kortSig(); 
}

void kortSig() {  //"S"  sender ut 3 korte signaler
  digitalWrite(ledPin, HIGH);   
  delay(1000);                  
  digitalWrite(ledPin, LOW);    
  delay(500);   
  digitalWrite(ledPin, HIGH);
  delay(1000);
  digitalWrite(ledPin, LOW);
  delay(500);
  digitalWrite(ledPin, HIGH);
  delay(1000);
  digitalWrite(ledPin, LOW);  
}

void langSig() { //"O" sender ut 3 lange signaler
  digitalWrite(ledPin, HIGH);
  delay(3000);                 
  digitalWrite(ledPin, LOW);
  delay(500);
  digitalWrite(ledPin, HIGH);
  delay(3000);
  digitalWrite(ledPin, LOW);
  delay(500);
  digitalWrite(ledPin, HIGH);
  delay(3000);                   
  digitalWrite(ledPin, LOW);
}
