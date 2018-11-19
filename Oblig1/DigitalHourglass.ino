// 1.6. Modularisering av «Digital Hourglass»
unsigned long currentTime; //flytter deklareringen av currentTime utenfor loop()
void loop() {
  currentTime = millis();
  checkTime(currentTime);
  switchState = digitalRead(switchPin);
  checkState(switchState);
}
//flyttet if-løkkene ut for å rydde opp koden
void checkTime(int ct) {
  if(ct - previousTime > interval) {
    previousTime = ct;
    digitalWrite(led, HIGH);
    led++;
    if(led == 7) {
    }
  }
}
//flyttet if-løkkene ut for å rydde opp koden
void checkState(int state) {
  if(state != prevSwitchState) {
    for(int x = 2; x < 8; x++) {
      digitalWrite(x, LOW);
    }
    led = 2;
    previousTime = currentTime;
  }
}
