# Working principle

1. DHT11 senses ambient temperature and humidity.
2. ACS712 produces an analog voltage related to current in its current path.
3. ESP32 samples the sensors and estimates current using a starting offset and sensitivity.
4. ESP32 publishes readings to MQTT topics over Wi-Fi.
5. Node-RED subscribes to the topics and displays live values.
6. Example firmware switches the relay output OFF if configured temperature/current thresholds are crossed.

ACS712 readings need calibration. DHT11 is a basic sensor. Thresholds and relay behavior are illustrative, not certified protection. Decide the safe relay state based on the real application.
