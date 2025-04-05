#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>

#define TRIG_PIN D3
#define ECHO_PIN D4
#define FIREBASE_HOST "your-project.firebaseio.com"
#define FIREBASE_AUTH "your-firebase-auth-key"
#define WIFI_SSID "your-WiFi-SSID"
#define WIFI_PASSWORD "your-WiFi-password"

FirebaseData firebaseData;

void setup() {
  Serial.begin(115200);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("Connected!");

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
  long duration;
  float distance;
  
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration * 0.034 / 2; // Convert to cm

  Serial.print("Waste Level: ");
  Serial.print(distance);
  Serial.println(" cm");

  Firebase.setFloat(firebaseData, "/bin1/level", distance);

  delay(5000);
}
