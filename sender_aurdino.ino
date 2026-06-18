#include <DHT.h>
#include "model.h"
#include <eloquent_tinyml.h>
#include <SPI.h>

// Pin Definitions
const int tempHumiditySensorPin = 2;
const int waterFlowSensorPin = 3;
const int waterLevelSensorPin = A0;
const int soilMoistureSensorPin = A1;
const int relay1Pin = 7;

// Variables
volatile int flowPulseCount = 0;
float waterFlowRate = 0.0;
unsigned long lastTime = 0;

// Initialize DHT sensor
#define DHT_TYPE DHT11
DHT dht(tempHumiditySensorPin, DHT_TYPE);

// TinyML Configuration
#define INPUT_SIZE 5
#define OUTPUT_SIZE 1
TfLite<INPUT_SIZE, OUTPUT_SIZE> ml;

void flowSensorISR() {
  flowPulseCount++;
}

void setup() {
  Serial.begin(9600);
  while (!Serial);

  // Initialize ML model
  ml.begin(model_tflite);

  // Initialize sensors
  dht.begin();
  pinMode(waterFlowSensorPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(waterFlowSensorPin), flowSensorISR, RISING);
  digitalWrite(relay1Pin, HIGH);
}

void loop() {
  // 1. Read Sensors
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  int soilMoisture = analogRead(soilMoistureSensorPin);
  int waterLevel = analogRead(waterLevelSensorPin);
  
  // Calculate flow rate
  if (millis() - lastTime >= 1000) {
    detachInterrupt(digitalPinToInterrupt(waterFlowSensorPin));
    waterFlowRate = flowPulseCount / 7.5;
    flowPulseCount = 0;
    lastTime = millis();
    attachInterrupt(digitalPinToInterrupt(waterFlowSensorPin), flowSensorISR, RISING);
  }

  // 2. Prepare ML Input
  float input[INPUT_SIZE] = {
    temperature,
    humidity,
    soilMoisture,
    waterLevel,
    waterFlowRate
  };

  // 3. Run ML Prediction
  float output[OUTPUT_SIZE];
  ml.predict(input, output);
  bool shouldWater = output[0] > 0.5;

  // 4. Control Pump
  digitalWrite(relay1Pin, shouldWater ? LOW : HIGH);

  // 5. Print to Serial Monitor
  Serial.println("------ Sensor Data ------");
  Serial.print("Temperature   : "); Serial.print(temperature); Serial.println(" °C");
  Serial.print("Humidity      : "); Serial.print(humidity); Serial.println(" %");
  Serial.print("Soil Moisture : "); Serial.println(soilMoisture);
  Serial.print("Water Level   : "); Serial.println(waterLevel);
  Serial.print("Flow Rate     : "); Serial.print(waterFlowRate); Serial.println(" L/min");
  Serial.print("Pump Status   : "); Serial.println(shouldWater ? "ON" : "OFF");
  Serial.println("--------------------------\n");

  delay(5000);  // Wait 5 seconds
}
