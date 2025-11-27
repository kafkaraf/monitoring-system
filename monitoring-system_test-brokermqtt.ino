#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// -------------------------------------------------
// KONFIGURASI PIN
// -------------------------------------------------
#define DHTPIN D5
#define DHTTYPE DHT22

const int trigPin = D6;
const int echoPin = D7;

const int rainPin = D8;

// Tinggi bak / sungai (cm)
const float tinggiBak = 100.0;

// -------------------------------------------------
// WIFI
// -------------------------------------------------
const char* ssid = "Nama-Wifi";
const char* password = "Password-Wifi";

// -------------------------------------------------
// MQTT
// -------------------------------------------------
const char* mqtt_server = "broker.mqtt-dashboard.com";
const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

// -------------------------------------------------
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

// -------------------------------------------------
void setupWiFi() {
  delay(10);
  Serial.println();
  Serial.print("Menghubungkan ke WiFi ");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

// -------------------------------------------------
void reconnectMQTT() {
  while (!client.connected()) {
    Serial.print("Menghubungkan ke MQTT...");
    if (client.connect("ESP8266-Monitoring-Rafi")) {
      Serial.println("OK!");
    } else {
      Serial.print("Gagal. rc=");
      Serial.print(client.state());
      Serial.println(" coba lagi 5 detik");
      delay(5000);
    }
  }
}

// -------------------------------------------------
void setup() {
  Serial.begin(115200);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(rainPin, INPUT);

  dht.begin();

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print(" Water Monitor ");
  delay(1500);
  lcd.clear();

  setupWiFi();
  client.setServer(mqtt_server, mqtt_port);
}

// -------------------------------------------------
void loop() {

  // --- MQTT autoreset ---
  if (!client.connected()) reconnectMQTT();
  client.loop();

  // ==== ULTRASONIC JSN ====
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  float distance = duration * 0.034 / 2.0;

  float tinggiAir = tinggiBak - distance;
  if (tinggiAir < 0) tinggiAir = 0;

  // ==== DHT22 ====
  float suhu = dht.readTemperature();
  float lembap = dht.readHumidity();
  if (isnan(suhu) || isnan(lembap)) {
    suhu = 0;
    lembap = 0;
  }

  // ==== MH-RD ====
  bool hujan = digitalRead(rainPin) == LOW;
  String statusHujan = hujan ? "Hujan" : "Cerah";

  // ==== STATUS SIAGA ====
  String statusSiaga;
  if (distance < 37.5) statusSiaga = "Siaga 4";
  else if (distance <= 62.5) statusSiaga = "Siaga 3";
  else if (distance <= 75) statusSiaga = "Siaga 2";
  else statusSiaga = "Siaga 1";

  // ==== SERIAL OUTPUT ====
  Serial.print("Air: "); Serial.print(tinggiAir);
  Serial.print(" | Suhu: "); Serial.print(suhu);
  Serial.print(" | Hum: "); Serial.print(lembap);
  Serial.print(" | Cuaca: "); Serial.print(statusHujan);
  Serial.print(" | Status: "); Serial.println(statusSiaga);

  // -------------------------------------------------
  // 🔥 MQTT PUBLISH JSON
  // -------------------------------------------------
  String payload = "{";
  payload += "\"tinggi_air\":"; payload += tinggiAir; payload += ",";
  payload += "\"suhu\":"; payload += suhu; payload += ",";
  payload += "\"lembap\":"; payload += lembap; payload += ",";
  payload += "\"cuaca\":\""; payload += statusHujan; payload += "\",";
  payload += "\"siaga\":\""; payload += statusSiaga; payload += "\"";
  payload += "}";

  client.publish("rafi/sensor", payload.c_str());

  Serial.print("Publish → ");
  Serial.println(payload);

  // ==== LCD ====
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("A:");
  lcd.print(tinggiAir, 0);
  lcd.print("cm ");

  lcd.print(suhu, 0);
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print(statusHujan);
  lcd.print(" ");

  if (statusSiaga == "Siaga 4") lcd.print("S4");
  else if (statusSiaga == "Siaga 3") lcd.print("S3");
  else if (statusSiaga == "Siaga 2") lcd.print("S2");
  else lcd.print("S1");

  delay(1000);
}
