# Heater Control System 🔥

This is a basic heater control system built using Arduino. It uses a DHT22 temperature sensor to read the current temperature and controls a simulated heater. The system turns the heater on or off based on temperature thresholds.

## What it Does

- Reads temperature from the DHT22 sensor
- Turns heater ON when the temperature is low
- Turns heater OFF when target temperature is reached
- Shows the current temperature and system state on an LCD display
- Logs data to the Serial Monitor

## States of the System

- **Idle** – Temperature is normal, no action
- **Heating** – Heater is ON because temp is low
- **Target Reached** – Heater is OFF, ideal temp reached
- **Overheat** – Temperature is too high, shows a warning
- **Sensor Error** – In case sensor doesn’t give data

## Hardware Used

- Arduino Uno
- DHT22 temperature sensor
- 16x2 LCD display with I2C

## How to Run (Wokwi)

You can simulate the full setup using [Wokwi](https://wokwi.com/). Just open the project, run it, and adjust the temperature slider to see how the system reacts.

## Future Ideas

- Add BLE support (using ESP32)
- Make heating profiles for different use cases
- Add a buzzer or alarm for overheat
- Use FreeRTOS to handle tasks better

---

This project was made as part of an internship assignment. It simulates a simple and practical heating control system.
