// Blynk Template Settings
#define BLYNK_TEMPLATE_ID   "TMPL3MCgXiEBi"
#define BLYNK_TEMPLATE_NAME "Health Monitoring System for Elderly"
#define BLYNK_AUTH_TOKEN    "0exrm5eCGUP4e2gJSRsRy6_IRqOgV4yb"

// Libraries
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include "DHT.h"
#include <Wire.h>
#include <MPU6050.h>

// WiFi credentials
char ssid[] = "Wokwi-GUEST";  
char pass[] = "";  

// DHT22 Setup
#define DHTPIN 4  
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// MPU6050 Setup
MPU6050 mpu;
int16_t ax, ay, az;
int fallThreshold = 15000;  // Adjust as per testing

// Timers
BlynkTimer timer;

// Function to read sensors
void sendSensorData() {
  // Read DHT22
  float temp = dht.readTemperature();
  float hum  = dht.readHumidity();

  if (isnan(temp) || isnan(hum)) {
    Serial.println("❌ Failed to read from DHT sensor!");
    return;
  }

  Serial.print("🌡 Temp: "); Serial.print(temp);
  Serial.print(" °C  |  💧 Hum: "); Serial.print(hum); Serial.println(" %");

  // Send to Blynk
  Blynk.virtualWrite(V0, temp);  // Temp
  Blynk.virtualWrite(V1, hum);   // Humidity

  // Read MPU6050
  mpu.getAcceleration(&ax, &ay, &az);
  long accTotal = abs(ax) + abs(ay) + abs(az);

  Serial.print("📉 Acc Value: "); Serial.println(accTotal);

  if (accTotal > fallThreshold) {
    Serial.println("⚠️ FALL DETECTED!");
    Blynk.virtualWrite(V2, "Fall Detected!");
    Blynk.logEvent("fall_alert", "⚠️ Fall Detected! Immediate Help Needed!");
  } else {
    Blynk.virtualWrite(V2, "Normal");
  }
}

void setup() {
  Serial.begin(115200);

  // Blynk + WiFi
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // DHT
  dht.begin();

  // MPU6050
  Wire.begin();
  mpu.initialize();
  if (!mpu.testConnection()) {
    Serial.println("❌ MPU6050 connection failed!");
  } else {
    Serial.println("✅ MPU6050 Connected!");
  }

  // Run every 2s
  timer.setInterval(2000L, sendSensorData);
}

void loop() {
  Blynk.run();
  timer.run();
}
