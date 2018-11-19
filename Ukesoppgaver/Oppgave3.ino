unsigned long previousTime = 0;
unsigned long currentTime;
int interval = 5000;

void setup() {
  Serial.begin(9600); 
}

void loop() {
 currentTime = millis();

 if (currentTime - previousTime == interval) {
    Serial.print("Det har gått ");
    Serial.print(interval/1000);
    Serial.print(" sekunder");
 }
}
