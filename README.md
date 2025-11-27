# **Testing Alat Final Project**

Repositori ini berisi progres pengembangan **Sistem Monitoring Ketinggian Air berbasis NodeMCU ESP8266**, yang digunakan sebagai bagian dari **tugas akhir/skripsi**.

---

## **Branch: wifi-feature**

Branch ini mencakup pengembangan fitur:  

- **Integrasi dan konfigurasi WiFi**  
- **Pengiriman data sensor melalui MQTT**  
- **Optimasi komunikasi antara ESP8266 → Broker → Subscriber**

---

## **Konsep Broker & Subscriber**

### **1. Subscriber (CMD)**  
Menggunakan **Mosquitto** sebagai MQTT client untuk menerima data sensor:

```bash
mosquitto_sub.exe -h broker.mqtt-dashboard.com -t rafi/sensor

### **2. Publisher (ESP8266)
ESP8266 mengirim data ke MQTT Broker dengan konfigurasi:

```bash
const char* mqtt_server = "broker.mqtt-dashboard.com";
const int mqtt_port = 1883;

Mengirim data dengan:
```bash
client.publish("rafi/sensor", payload.c_str());




