//Stopwatch with LCD-screen
#include <LiquidCrystal.h>

//Variabler
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const int btnStart = 6;
const int btnReset = 7;

long lastPressedStart = 0; //Last millisecond we pressed btnStart
long lastPressedReset = 0; //Last millisecond we pressed btnReset

//Should the system run?
boolean runs = false;

//The button states
int btnStartState = LOW;      //The value the btnStart reads
int btnStartCurrState = LOW;  //The last value of btnStart
int btnResetState = LOW;      //The value of btnStart
int btnResetCurrState = LOW;  //The last value of btnReset

//The timer
long timer = 0;

//Time variables
int hour = 0;
int minu = 0;
int sec = 0;
int desi = 0;

void setup() {
  lcd.begin(16,2);
  pinMode(btnStart, INPUT);
  pinMode(btnStart, INPUT);
  
  lcd.print("Press Start");
  lcd.setCursor(0,1);
  lcd.print("00:00:00.00");
}

void loop() {
  tickingClock(); //start the clock
  btnStartState = digitalRead(btnStart);
  btnResetState = digitalRead(btnReset);
  checkStart();
  checkClear();
}

/**
 * Check if btnStart is pushed. If true, be sure that there is at least 100ms
 * since the last press and switch the running state. And change btnStartCurrState 
 * to btnStartState.
 */
void checkStart() {
  if(btnStartState != btnStartCurrState) { //check if button state is changed
    if(btnStartState == LOW) {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("00:00:00");
    } else if(btnStartState == HIGH && (millis()-lastPressedStart) > 100 || lastPressedStart == 0) {
      lastPressedStart = millis();
      runs = !runs;
    }    
  }
  btnStartCurrState = btnStartState;
}

/**
 * Check if btnReset is pushed. If true, be sure that there is at least 100 since
 * last press and clear display. And change btnResetCurrState to btnResetState.
 */
void checkClear() {
  if(btnResetState != btnResetCurrState) { //check if button state is changed
    if(btnResetState == LOW) {
      updateLCDreset();
    } else if(btnResetState == HIGH && (millis()-lastPressedReset) > 100 || lastPressedReset == 0) {  
      lastPressedReset = millis();
      clearAll();
    }    
  }
  btnResetCurrState = btnResetState;
}
 /**
  * Update the LCD-display when reset is pushed and display
  * the last time on the screen.
  */
void updateLCDreset() {
  lcd.clear();
  lcd.begin(16,2);
  lcd.print("Press Start");
  lcd.setCursor(0,1);
  lcd.print("Last: ");
  
  if(hour < 10) { // If hour doesn't have 2 digits
     lcd.print("0");
  }
  
  lcd.print(hour, DEC);
  lcd.print(":");
  
  if(minu < 10) {    // If minute doesn't have 2 digits
    lcd.print("0");
  }
  
  lcd.print(minu,DEC);
  lcd.print(":");

  if(sec < 10) {  // If second doesn't have 2 digits
    lcd.print("0");
  }

  lcd.print(sec, DEC);
  lcd.print(".");

  lcd.print(desi, DEC);
}

/**
 * For each tenth of a second call the tick() function
 */
void tickingClock() {
  Serial.println(millis() /10);
  if((timer - millis()/100) >= 100 || timer == 0) {
    tick();
    timer = millis()/100;
  }
}

/** 
 * Ticks one tenth of a second, if run is set to true
 */
void tick() {
  if(runs) {
    updateLCD();
    
    if(desi == 9) {
      desi = 0;
      
      if(sec == 59) {
        sec = 0;
        if(minu == 59) {
          minu = 0;
          hour++;
        } else {
          minu++;
        }
      } else {
        sec++;
      }
    } else {
      desi++;
    }
  }
}

/**
 * Update the LCD-display
 */
void updateLCD() {
  lcd.setCursor(0,0);
  if(hour < 10) { // If hour doesn't have 2 digits
     lcd.print("0");
  }
  
  lcd.print(hour, DEC);
  lcd.print(":");
  
  if(minu < 10) {    // If minute doesn't have 2 digits
    lcd.print("0");
  }
  
  lcd.print(minu,DEC);
  lcd.print(":");

  if(sec < 10) {  // If second doesn't have 2 digits
    lcd.print("0");
  }

  lcd.print(sec, DEC);
  lcd.print(".");

  lcd.print(desi, DEC);
}

/**
 * Clear the display. Set time variables equal 0
 */
void clearAll() {
  runs = false;
  sec = 0;
  minu = 0;
  desi = 0;
}
