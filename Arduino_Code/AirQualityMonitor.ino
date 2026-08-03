/*
 * Project: IoT Air Quality and Humidity Monitoring System
 * Author: Shikhar Baranwal
 * Board: Arduino Uno
 * Sensors: DHT11, MQ135
 * Buzzer Pin: D8
 */

#include <DHT.h>
#include <MQ135.h>

// Pin Definitions
#define DHTPIN 7
#define BUZZER_PIN 8

// DHT11 Setup
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// MQ135 Setup
MQ135 gasSensor(A0);

// Threshold Values
float temperatureThreshold = 25.0;
float humidityThreshold = 60.0;
int airQualityThreshold = 100;

void setup() {
  Serial.begin(9600);

  dht.begin();

  pinMode(BUZZER_PIN, OUTPUT);

  Serial.println("Starting IoT Air Quality Monitoring System...");
}

void loop() {

  // Read Temperature & Humidity
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Read Air Quality
  int airQuality = gasSensor.getPPM();

  // Check Sensor Reading
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    delay(2000);
    return;
  }

  // Display Readings
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C");

  Serial.print(" | Humidity: ");
  Serial.print(humidity);
  Serial.print(" %");

  Serial.print(" | Air Quality (PPM): ");
  Serial.println(airQuality);

  // Trigger Buzzer
  if (temperature > temperatureThreshold ||
      humidity > humidityThreshold ||
      airQuality > airQualityThreshold) {

    digitalWrite(BUZZER_PIN, HIGH);

  } else {

    digitalWrite(BUZZER_PIN, LOW);
  }

  delay(2000);
}
