
// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

unsigned long bpmLastUpdate = 0;
unsigned long bpmUpdate = 400;
unsigned long buzzerTime = 100;
unsigned long buzzerStartTime = 0;
unsigned long lastPeriod = 0;
bool buzzerOn = false;
const int buzzer = 9;

void setup() {
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Beats Per Minute");
}

void loop() {
  unsigned currentTime = millis();
  int potReading = analogRead(A1) / 5;
  if(potReading > 180) {
    potReading = 180;
  }
  
  if(currentTime - bpmLastUpdate >= bpmUpdate) {
    bpmLastUpdate = currentTime;
    lcd.clear();
    lcd.print("Beats Per Minute");
    lcd.setCursor(0, 1);
    lcd.print(potReading);
    Serial.println(potReading);
  }

  int period = 60000 / potReading;

  if(currentTime - lastPeriod >= period) {
    lastPeriod = currentTime;
    tone(buzzer, 300);
    buzzerOn = true;
    buzzerStartTime = currentTime;
  }

  if (buzzerOn  && currentTime - buzzerStartTime >= buzzerTime) {
      noTone(buzzer);
      buzzerOn = false;
  }
}
