#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

// Configure these for your network and actual hardware.
const char* WIFI_SSID = "YOUR_WIFI_NAME";
const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";
const char* MQTT_HOST = "192.168.1.10";
const int MQTT_PORT = 1883;

#define DHT_PIN 4
#define DHT_TYPE DHT11
#define ACS_PIN 34
#define RELAY_PIN 26

// ACS712 sensitivity (mV/A): typically 185 (5A), 100 (20A), 66 (30A).
// Verify variant and calibrate offset/sensitivity for your setup.
const float ACS_SENSITIVITY_MV_PER_A = 185.0;
const float ADC_VREF = 3.3;
const int ADC_MAX = 4095;

// Demonstration thresholds only; determine suitable values for your application.
const float TEMP_LIMIT_C = 40.0;
const float CURRENT_LIMIT_A = 2.0;
const bool RELAY_ACTIVE_LOW = true;

DHT dht(DHT_PIN, DHT_TYPE);
WiFiClient wifi;
PubSubClient mqtt(wifi);

void setRelay(bool on) {
  digitalWrite(RELAY_PIN, RELAY_ACTIVE_LOW ? (on ? LOW : HIGH) : (on ? HIGH : LOW));
}

float readCurrentA() {
  const int n = 500;
  long total = 0;
  for (int i = 0; i < n; i++) {
    total += analogRead(ACS_PIN);
    delayMicroseconds(250);
  }
  float avg = (float)total / n;
  float volts = avg * ADC_VREF / ADC_MAX;
  float zeroV = ADC_VREF / 2.0; // starting assumption; calibrate this
  float sensitivity = ACS_SENSITIVITY_MV_PER_A / 1000.0;
  return (volts - zeroV) / sensitivity;
}

void connectWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) delay(500);
}

void connectMQTT() {
  while (!mqtt.connected()) {
    if (mqtt.connect("esp32-multiparameter-monitor")) break;
    delay(2000);
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(RELAY_PIN, OUTPUT);
  setRelay(false);
  analogReadResolution(12);
  dht.begin();
  connectWiFi();
  mqtt.setServer(MQTT_HOST, MQTT_PORT);
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) connectWiFi();
  if (!mqtt.connected()) connectMQTT();
  mqtt.loop();

  static unsigned long last = 0;
  if (millis() - last < 2000) return;
  last = millis();

  float t = dht.readTemperature();
  float h = dht.readHumidity();
  float amps = readCurrentA();
  bool validDHT = !isnan(t) && !isnan(h);
  bool alert = (validDHT && t >= TEMP_LIMIT_C) || (amps >= CURRENT_LIMIT_A);

  // Illustrative relay response; verify module polarity and safe state.
  setRelay(!alert);

  if (validDHT) {
    mqtt.publish("lab/monitor/temperature_c", String(t, 1).c_str(), true);
    mqtt.publish("lab/monitor/humidity_pct", String(h, 1).c_str(), true);
  }
  mqtt.publish("lab/monitor/current_a", String(amps, 2).c_str(), true);
  mqtt.publish("lab/monitor/status", alert ? "ALERT_RELAY_OFF" : "NORMAL", true);

  Serial.printf("Temp: %.1f C | Humidity: %.1f %% | Current: %.2f A | %s\n",
                t, h, amps, alert ? "ALERT" : "NORMAL");
}
