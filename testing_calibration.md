# Testing and calibration checklist

## Pre-power checks
- [ ] Confirm exact ESP32, DHT11, ACS712 variant, and relay module.
- [ ] Verify ACS712 signal conditioning keeps ADC voltage within ESP32 limits.
- [ ] Verify relay active-high/active-low behavior with no load.
- [ ] Use a low-voltage DC test load first; keep mains disconnected.

## Validation
- [ ] Confirm Wi-Fi connection and MQTT publishing.
- [ ] Confirm Node-RED receives each topic and displays values.
- [ ] Compare DHT11 readings with a reference instrument; record conditions.
- [ ] Record ACS712 zero-current ADC readings and calibrate offset.
- [ ] Compare current readings against a suitable reference meter at several safe load levels.
- [ ] Test threshold/relay logic using controlled test values.
- [ ] Record actual results and any firmware changes.

| Test | Expected | Result |
|---|---|---|
| Wi-Fi/MQTT | Connected; topics received | Pending |
| DHT11 | Plausible temperature/humidity | Pending |
| ACS712 | Calibrated current estimate | Pending |
| Relay | Correct state at test threshold | Pending |
| Node-RED | Live readings/status visible | Pending |
