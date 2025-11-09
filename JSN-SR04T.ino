// Ultrasonic JSN-SR04T
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int trigPin = 6;   // Pin Trig ke D6
const int echoPin = 7;   // Pin Echo ke D7

// Alamat LCD bisa 0x27 atau 0x3F tergantung modul
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print(" Sensor Air Aktif ");
  delay(1500);
  lcd.clear();
}

void loop() {
  // Kirim pulsa trigger
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Baca durasi echo
  long duration = pulseIn(echoPin, HIGH);

  // Hitung jarak (cm)
  float distance = duration * 0.034 / 2;

  // Tentukan status siaga sesuai batas baru
  String statusSiaga;
  if (distance < 37.5) {
    statusSiaga = "Normal";
  } else if (distance >= 37.5 && distance <= 62.5) {
    statusSiaga = "Siaga 3";
  } else if (distance > 62.5 && distance <= 75) {
    statusSiaga = "Siaga 2";
  } else if (distance > 75) {
    statusSiaga = "Siaga 1";
  }

  // Tampilkan ke Serial Monitor
  Serial.print("Jarak: ");
  Serial.print(distance);
  Serial.print(" cm | Status: ");
  Serial.println(statusSiaga);

  // Tampilkan ke LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Jarak: ");
  lcd.print(distance, 1);
  lcd.print("cm");

  lcd.setCursor(0, 1);
  lcd.print("Status: ");
  lcd.print(statusSiaga);

  // Delay antar pengukuran
  delay(500);
}
