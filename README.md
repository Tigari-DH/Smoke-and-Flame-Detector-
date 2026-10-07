# Smoke-and-Flame-Detector-
Arduino-based smoke and flame detection system with MQ-2, flame sensor, DHT11, LCD monitoring, buzzer alarm, and relay control.




# 🔥 Smoke / Fire Detector

An Arduino-based smoke and fire detection system that monitors smoke, flame, temperature, and humidity in real time. When smoke or a flame is detected, the system activates an alarm and relay while displaying the status and sensor readings on an I2C LCD.

## 🚨 Features

- Smoke detection using an MQ-2 sensor
- Flame detection using a digital flame sensor
- Temperature and humidity monitoring using a DHT11
- 16x2 I2C LCD status display
- Buzzer alarm during dangerous conditions
- Relay activation when an alarm is detected
- Real-time sensor information through the Serial Monitor
- Configurable smoke detection threshold

## 🛠️ Hardware Used

- Arduino
- MQ-2 Smoke/Gas Sensor
- Flame Sensor
- DHT11 Temperature & Humidity Sensor
- 16x2 I2C LCD
- Active Buzzer
- Relay Module
- Jumper Wires
- Breadboard

## 🔌 Pin Configuration

| Component | Arduino Pin |
|-----------|-------------|
| MQ-2 Analog Output | A0 |
| Flame Sensor Digital Output | D3 |
| DHT11 Data | D4 |
| Buzzer | D5 |
| Relay Module IN | D6 |
| LCD SDA | A4 |
| LCD SCL | A5 |

## ⚙️ How It Works

The Arduino continuously reads data from the MQ-2 smoke sensor and flame sensor.

The MQ-2 sensor value is compared with a predefined smoke threshold:

```cpp
const int SMOKE_THRESHOLD = 300;
