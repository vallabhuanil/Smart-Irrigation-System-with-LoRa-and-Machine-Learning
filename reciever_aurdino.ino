#include <SPI.h>
#include <LoRa.h>

// LoRa pin configuration (adjust if needed)
const int csPin = 10;
const int resetPin = 9;
const int irqPin = 2;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  // Initialize LoRa
  LoRa.setPins(csPin, resetPin, irqPin);
  if (!LoRa.begin(433E6)) {
    Serial.println("LoRa init failed. Check connections.");
    while (1);
  }

  Serial.println("LoRa Receiver started...");
}

void loop() {
  int packetSize = LoRa.parsePacket();

  if (packetSize) {
    String incoming = LoRa.readString();
    Serial.print("Raw packet: ");
    Serial.println(incoming);

    // Parse and display nicely
    String values[6];
    int index = 0;

    while (incoming.length() > 0 && index < 6) {
      int commaIndex = incoming.indexOf(',');
      if (commaIndex == -1) {
        values[index++] = incoming;
        break;
      } else {
        values[index++] = incoming.substring(0, commaIndex);
        incoming = incoming.substring(commaIndex + 1);
      }
    }

    if (index == 6) {
      Serial.println("------ Sensor Data ------");
      Serial.println("Temperature   : " + values[0] + " °C");
      Serial.println("Humidity      : " + values[1] + " %");
      Serial.println("Soil Moisture : " + values[2]);
      Serial.println("Water Level   : " + values[3]);
      Serial.println("Flow Rate     : " + values[4] + " L/min");
      Serial.println("Pump Status   : " + values[5]);
      Serial.println("--------------------------\n");
    } else {
      Serial.println("⚠️ Error: Incomplete data received.");
    }
  }
}
