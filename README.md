# Smart Irrigation System with LoRa and Machine Learning

## Project Overview
This project is a Smart Irrigation System that leverages sensor data and embedded machine learning to automate irrigation pump operation efficiently. It uses LoRa wireless communication for long-range data transmission and a Random Forest Classifier deployed on Arduino for local decision making.

## Features
- Real-time sensor monitoring: temperature, humidity, soil moisture, water level, and water flow
- Embedded Machine Learning inference running on Arduino using EloquentTinyML
- LoRa-based wireless communication between irrigation field and receiver base station
- Automatic pump control based on ML prediction to conserve water usage

## Technologies
- Arduino Uno microcontroller
- LoRa SX1278 wireless modules
- Sensors: DHT11 (temperature & humidity), soil moisture sensor, water level sensor, YF-S201 water flow sensor
- Machine Learning: Random Forest Classifier (embedded ML model)
- Arduino IDE (C++ language) for microcontroller programming
- Python (for initial ML model training and conversion)

## Machine Learning Model Details
- **Model used:** Random Forest Classifier (RFC)
- **Training:** The RFC model was trained on environmental sensor data including temperature, humidity, soil moisture, water level, and water flow alongside corresponding pump ON/OFF states.
- **Accuracy:** The model achieved a test accuracy of 100% on collected environmental and irrigation data.
- **Conversion:** The trained model was converted to a quantized TensorFlow Lite (TFLite) model to enable embedded inference on the Arduino Uno.
- **Library:** The converted TFLite model was integrated and utilized using the EloquentTinyML library, allowing lightweight, real-time predictions on resource-constrained microcontroller hardware.
- **Upload:** The resulting embedded ML model was uploaded to the Arduino Uno as part of the Arduino sketch, which included sensor interfacing code, ML inference code, and LoRa communication code.

## Installation
1. Connect sensors and relay to Arduino as per wiring diagrams provided.
2. Install required Arduino libraries: DHT, LoRa, and EloquentTinyML.
3. Upload the sender and receiver Arduino codes (written in C++ via Arduino IDE) to respective Arduino Uno devices.
4. Ensure LoRa modules are configured to operate at 433 MHz frequency.
5. Power on the devices and verify sensor readings and pump control via Serial Monitor.

## Usage
- The system continuously monitors real-time environmental parameters via sensors.
- Sensor data is fed into the embedded ML model running locally on the sending Arduino to predict irrigation pump control (ON/OFF).
- Decisions are automatically executed by controlling a relay connected to the water pump.
- Sensor readings and pump status are transmitted wirelessly using LoRa and displayed at the receiver node's Serial Monitor.

## Results
The system successfully automates irrigation, reducing water wastage and manual oversight. The embedded ML model runs fully on the Arduino Uno with high prediction accuracy, validating the system's effectiveness.

## Future Work
- Dynamic allocation of multiple water sources with intelligent source selection.
- Integration of weather forecast APIs for proactive irrigation decision-making.
- Scalability for large agriculture farms using additional sensors and nodes.

## Author

**Sampath Magapu**  
Email: [sampathmagapu11@gmail.com](mailto:sampathmagapu11@gmail.com)  
LinkedIn: [https://www.linkedin.com/in/sampath-magapu-9b5102253/](https://www.linkedin.com/in/sampath-magapu-9b5102253/)

## License
This project is licensed under the MIT License - see the LICENSE file for details.
