//here goes the code
#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// === Pin Definitions ===
#define DHTPIN 2            // DHT22 Data pin
#define DHTTYPE DHT22       // Sensor type
#define HEATER_PIN 3        // Output to heater relay / LED
#define LED_PIN 4           // Visual alert (for overheat)

// === Objects ===
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27, 16x2 LCD

// === Thresholds ===
const float TEMP_LOW = 22.0;
const float TEMP_TARGET = 25.0;
const float TEMP_OVERHEAT = 35.0;

void setup() {
  Serial.begin(9600);
  dht.begin();

  pinMode(HEATER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  lcd.begin(16, 2);   // ✅ Corrected to pass required arguments
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Heater System");
  lcd.setCursor(0, 1);
  lcd.print("Initializing...");
  delay(2000);
  lcd.clear();
}

void loop() {
  float temp = dht.readTemperature();

  if (isnan(temp)) {
    Serial.println("Failed to read from DHT sensor!");
    lcd.setCursor(0, 0);
    lcd.print("Sensor Error    ");
    lcd.setCursor(0, 1);
    lcd.print("Check DHT22     ");
    delay(1000);
    return;
  }

  // Determine state and control heater
  String state;

  if (temp < TEMP_LOW) {
    digitalWrite(HEATER_PIN, HIGH);   // Turn heater ON
    digitalWrite(LED_PIN, LOW);
    state = "Heating";
  } else if (temp >= TEMP_TARGET && temp < TEMP_OVERHEAT) {
    digitalWrite(HEATER_PIN, LOW);    // Heater OFF
    digitalWrite(LED_PIN, LOW);
    state = "Target OK";
  } else if (temp >= TEMP_OVERHEAT) {
    digitalWrite(HEATER_PIN, LOW);    // Emergency Heater OFF
    digitalWrite(LED_PIN, HIGH);      // Alert ON
    state = "Overheat!";
  } else {
    digitalWrite(HEATER_PIN, LOW);
    digitalWrite(LED_PIN, LOW);
    state = "Idle";
  }

  // === Serial Monitor Output ===
  Serial.print("Temp: ");
  Serial.print(temp);
  Serial.print(" C | State: ");
  Serial.print(state);
  Serial.print(" | Heater: ");
  Serial.println(digitalRead(HEATER_PIN) ? "ON" : "OFF");

  // === LCD Display Output ===
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temp, 1);
  lcd.print(" C   "); // Pad spaces

  lcd.setCursor(0, 1);
  lcd.print("State: ");
  lcd.print(state);
  int spaces = 16 - 7 - state.length();
  while (spaces-- > 0) lcd.print(" ");

  delay(1000); // Delay 1 sec
}
