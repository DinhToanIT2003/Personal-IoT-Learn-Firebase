#include <ESP8266WiFi.h>
#include <Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

// Wi-Fi and Firebase information
#define WIFI_SSID ""
#define WIFI_PASSWORD ""
#define API_KEY ""
#define DATABASE_URL ""

// Connection pin
#define TRIG_PIN 16 // Trigger pin of HC-SR04
#define ECHO_PIN 12 // Echo pin of HC-SR04
#define LED_PIN 2 // LED light pin

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
bool signupOK = false;
bool ledStatus = false;

float measureDistance() {
  // Send pulse from Trigger pin
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Measure pulse time at Echo pin
  long duration = pulseIn(ECHO_PIN, HIGH);
  delay(100);
  Serial.println("duration");

  // Calculate distance (cm)
  float distance = (duration * 0.034) / 2;
  delay(100);
  return distance;
}

void setup() {
  Serial.begin(9600);

  pinMode(LED_PIN, OUTPUT);

  // Connect to WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Successfully connected to IP: ");
  Serial.println(WiFi.localIP());
  
  // Firebase configuration
  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;

  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("Firebase registration successful!");
    signupOK = true;
  } else {
    Serial.printf("Firebase registration error: %s\n", config.signer.signupError.message.c_str());
  }

  config.token_status_callback = tokenStatusCallback;
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  // Configure input/output pins
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
  if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 1000 || sendDataPrevMillis == 0)) {
    sendDataPrevMillis = millis();

    // Measure distance from ultrasonic sensor
    float distance = measureDistance();
    Serial.print("Measured distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    // Write data to Firebase
    if (Firebase.RTDB.setFloat(&fbdo, "Sensor/distance", distance)) {
      Serial.println("Data saved successfully!");
    } else {
      Serial.print("Error recording data: ");
      Serial.println(fbdo.errorReason());
    }
  }

  // Read data from Firebase
  if (Firebase.RTDB.getBool(&fbdo, "Result/led")) {
    if (fbdo.dataType() == "boolean") {
      ledStatus = fbdo.boolData();
      Serial.println("Successful READ from " + fbdo.dataPath() + ": " + ledStatus + " (" + fbdo.dataType() + ")");
      digitalWrite(LED_PIN, ledStatus);
    }
  } else {
    Serial.println("FAILED: " + fbdo.errorReason());
  }
  delay(950)

  // Study material: https://youtu.be/aO92B-K4TnQ
}