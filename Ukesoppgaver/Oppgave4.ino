//2.4. Debounce
int buttonPin = 3;
long lastDebounceTime = 0;
long debounceDelay = 200;    // debounce tid
int pushed;

void setup() {
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  int buttonState = digitalRead(buttonPin);
  if ( (millis() - lastDebounceTime) > debounceDelay) {
    if ( buttonState == HIGH ) {
      lastDebounceTime = millis(); 
      pushed++;
    } else if ( buttonState == HIGH) { //&& (ledState > 0) ) {
      lastDebounceTime = millis(); //set the current time
    }
  }
  Serial.println(pushed);
}
