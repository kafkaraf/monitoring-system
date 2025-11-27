# **Testing Alat Final Project**

Repositori ini berisi progres pengembangan **Sistem Monitoring Ketinggian Air berbasis NodeMCU ESP8266**, yang digunakan sebagai bagian dari **tugas akhir/skripsi**.

---

## **Branch: wifi-feature**

Branch ini mencakup pengembangan fitur:  

- **Integrasi dan konfigurasi WiFi**  
- **Pengiriman data sensor melalui MQTT**  
- **Optimasi komunikasi antara ESP8266 → Broker → Subscriber**

  ## **Setup Proyek**

### **1. Instalasi Library ESP8266 & MQTT**
- Buka **Arduino IDE** → **Tools** → **Manage Libraries**  
- Install library **ESP8266** dan **PubSubClient**

### **2. Koneksi Hardware**
- Sambungkan **sensor ultrasonik** ke NodeMCU sesuai pin yang telah dikonfigurasi  
- Sambungkan **NodeMCU** ke komputer/laptop via USB

### **3. Konfigurasi WiFi**
- Masukkan **SSID** dan **Password** WiFi Anda di kode  
- Pastikan **NodeMCU** dapat terhubung ke jaringan

---

## **Konsep Broker & Subscriber**

### **1. Subscriber (CMD)**  
Menggunakan **Mosquitto** sebagai MQTT client untuk menerima data sensor:

```bash
mosquitto_sub.exe -h broker.mqtt-dashboard.com -t rafi/sensor

bash```

### **2. Publisher (ESP8266)**  
ESP8266 mengirim data ke **MQTT Broker** dengan konfigurasi:

```cpp
const char* mqtt_server = "broker.mqtt-dashboard.com";
const int mqtt_port = 1883;






