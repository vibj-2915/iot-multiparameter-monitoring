# IoT-Based Multi-Parameter Monitoring Dashboard

Example project package: ESP32 reads temperature/humidity (DHT11) and electrical current (ACS712), publishes values over MQTT, and Node-RED displays them. An optional relay output demonstrates threshold-based switching.

**Status:** This package provides example code and design documentation. Physical assembly, calibration, and testing are pending; do not claim verified operation until completed.

## Files
- `esp32_monitor.ino` — Arduino IDE firmware
- `node_red_flow.json` — example Node-RED dashboard flow
- `wiring.md` — pin mapping and voltage/safety notes
- `working_principle.md` — system explanation
- `testing_calibration.md` — bring-up and validation checklist

Install ESP32 board support, DHT sensor library, and PubSubClient. Configure Wi-Fi/MQTT settings in the sketch, import the flow into Node-RED, and calibrate the ACS712 for your exact board.

**Safety:** Start with a low-voltage DC load. ACS712 boards commonly run at 5V and may output a voltage unsafe for ESP32 ADC pins; use suitable signal conditioning and verify with a meter. Do not connect mains voltage without appropriate training, isolation, enclosure, and rated components. Example thresholds are not safety protection.
