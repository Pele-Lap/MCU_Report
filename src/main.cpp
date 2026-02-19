#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd_1(0x27, 16, 2);

int lastState = -1;

int LED1 = 4;
int LED2 = 5;
int LED3 = 6;
int LED4 = 7;
int leds[] = {LED1, LED2, LED3, LED4};

int buzz = 8;
int StartFeq = 500;

int btn = 9;
int State = 0;

void setup() {
  lcd_1.init();
  lcd_1.backlight();
  for (int i = 0; i < 4; i++) {
    pinMode(leds[i], OUTPUT);
  }
  pinMode(buzz, OUTPUT);
  pinMode(btn, INPUT);
  Serial.begin(9600);
}

void loop() {
  
  int BtnState = digitalRead(btn);
  if(BtnState == HIGH){
    State++;
    if (State > 5) State = 0; 
    delay(500);
  }

  if (State != lastState) {
    lcd_1.clear(); 
    lcd_1.setCursor(0,0);
    lcd_1.print("Current :");
    
    lcd_1.setCursor(0,1);
    switch(State) {
      case 0: lcd_1.print("Mode 0 : OFF"); break;
      case 1: lcd_1.print("Mode 1 : 60bpm"); break;
      case 2: lcd_1.print("Mode 2 : 90bpm"); break;
      case 3: lcd_1.print("Mode 3 : 120bpm"); break;
      case 4: lcd_1.print("Mode 4 : 150bpm"); break;
      case 5: lcd_1.print("Resetting..."); break;
    }
    lastState = State; 
  }

  
  switch(State) {
    case 0:
      for (int i = 0; i < 4; i++) {
        digitalWrite(leds[i], LOW);
      }
      noTone(buzz);
      break;
    case 1: mode1(); break;
    case 2: mode2(); break;
    case 3: mode3(); break;
    case 4: mode4(); break;
    case 5: State = 0; break; 
  }
}

void mode1(){
  for (int i = 0; i < 4; i++) {
    digitalWrite(leds[i], HIGH); 
    tone(buzz, StartFeq);            
    delay(500);                  
    digitalWrite(leds[i], LOW);  
    noTone(buzz);
    delay(500);
  }
}

void mode2(){
  for (int i = 0; i < 4; i++) {
    digitalWrite(leds[i], HIGH); 
    tone(buzz, StartFeq);            
    delay(335);                  
    digitalWrite(leds[i], LOW);  
    noTone(buzz);
    delay(335);
  }
}

void mode3(){
  for (int i = 0; i < 4; i++) {
    digitalWrite(leds[i], HIGH); 
    tone(buzz, StartFeq);            
    delay(250);                  
    digitalWrite(leds[i], LOW);  
    noTone(buzz);
    delay(250);
  }
}

void mode4(){
  for (int i = 0; i < 4; i++) {
    digitalWrite(leds[i], HIGH); 
    tone(buzz, StartFeq);            
    delay(200);                  
    digitalWrite(leds[i], LOW);  
    noTone(buzz);
    delay(200);
  }
}