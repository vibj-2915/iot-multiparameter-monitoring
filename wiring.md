# Wiring (example GPIO assignments)

| Module | Pin | ESP32 |
|---|---|---|
| DHT11 | DATA | GPIO 4 |
| DHT11 | VCC | 3V3 (check module spec) |
| DHT11 | GND | GND |
| ACS712 | OUT | GPIO 34 through safe signal conditioning |
| ACS712 | GND | Common GND for low-voltage setup |
| Relay module | IN | GPIO 26 |
| Relay module | VCC/GND | As specified by module |

ACS712 VCC depends on the module (often 5V). Do not connect its output directly to ESP32 ADC unless you have verified it stays within the ESP32 input limits. Use an appropriately designed divider/conditioning circuit. Verify relay polarity with no load. Begin with low-voltage DC only; mains wiring is not covered here.
