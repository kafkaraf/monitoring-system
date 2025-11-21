#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int rainPin = D8;   // DO raindrop (LOW = hujan)

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(115200);

  pinMode(rainPin, INPUT);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("RAINDROP TEST");
  delay(1500);
  lcd.clear();
}

void loop() {

  int rainVal = digitalRead(rainPin);   // HIGH atau LOW

  String status;
  if (rainVal == LOW) {
    status = "Hujan";
  } else {
    status = "Cerah";
  }

  // Serial Monitor
  Serial.print("Digital = ");
  Serial.print(rainVal);
  Serial.print(" | Status: ");
  Serial.println(status);

  // LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Digital: ");
  lcd.print(rainVal);   // tampilkan HIGH/LOW

  lcd.setCursor(0, 1);
  lcd.print(status);

  delay(500);
}
