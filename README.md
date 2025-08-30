# 📌 Health Monitoring System for Elderly (ESP32 + DHT22 + MPU6050 + Blynk)
📖 Project Overview
Elderly people often live alone and may not have immediate access to medical help.
This IoT-based project monitors temperature, humidity, and fall detection in real-time and sends alerts via Blynk IoT to caregivers.

✅ Features:
🌡️ Temperature & 💧 Humidity monitoring using DHT22
📉 Fall detection using MPU6050 accelerometer
📲 Real-time data display on Blynk App Dashboard
🚨 Automatic fall alert notifications via Blynk Events

🛠️ Components Required
ESP32 Development Board
DHT22 Sensor (Temperature & Humidity
MPU6050 Accelerometer (Fall detection)
WiFi (e.g., Wokwi-GUEST or home router)
Blynk IoT App (Free Cloud)

📲 Blynk Virtual Pins Mapping
Virtual Pin	Parameter
V0	Temperature (°C)
V1	Humidity (%)
V2	Fall Status
⚡ Blynk Setup

Create a new template in Blynk IoT (Web Dashboard or App).
Template Name: Health Monitoring System for Elderly
Hardware: ESP32
Connection: WiFi
Copy the Template ID, Template Name, Auth Token into the code.

Create Datastreams:
V0 → Temperature (Gauge or Value Display)
V1 → Humidity (Gauge or Value Display)
V2 → Fall Status (Label / Text widget)
Create an Event in Blynk:

Event Name: fall_alert
Notification: "⚠️ Fall Detected! Immediate Help Needed!"

🚀 How It Works
ESP32 reads temperature & humidity from DHT22.
MPU6050 continuously measures acceleration values.
If total acceleration crosses the fall threshold, it sends:

🚨 Notification alert via Blynk event
Updates V2 status = "Fall Detected!"
Normal state shows "Norma" in the Blynk app.

📸 Example Blynk Dashboard
V0 → Temperature (Gauge Widget)
V1 → Humidity (Gauge Widget)
V2 → Fall Status (Label Widget)
Notifications enabled for fall alerts

🖥️ Example Serial Output
🌡 Temp: 28.3 °C  |  💧 Hum: 61.2 %
📉 Acc Value: 16800
⚠️ FALL DETECTED!

✅ Future Improvements
Add Pulse Sensor for heart rate monitoring
Integrate GPS module to send location during a fall

Cloud dashboard with ThingSpeak / Firebase backup
