**Testing Alat Final Project**

Repositori ini berisi progres pengembangan Sistem Monitoring Ketinggian Air berbasis NodeMCU ESP8266, yang digunakan sebagai bagian dari tugas akhir/skripsi.

Branch: wifi-feature

Branch ini berisi pengembangan tambahan untuk integrasi fitur WiFi, meliputi konfigurasi koneksi jaringan, pengiriman data sensor melalui protokol MQTT, serta optimasi komunikasi antara NodeMCU dan server.

Konsep Broker & Subscriber
1. Subscriber (CMD)
Menggunakan Mosquitto sebagai MQTT client untuk menerima data sensor:
mosquitto_sub.exe -h broker.mqtt-dashboard.com -t rafi/sensor

2. Publisher (ESP8266)
ESP8266 mengirim data ke MQTT Broker dengan konfigurasi:
const char* mqtt_server = "broker.mqtt-dashboard.com";
const int mqtt_port = 1883;

Mengirim data dengan:
client.publish("rafi/sensor", payload.c_str());

