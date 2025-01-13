/*
 *
 *
*/

#define LED_PIN     2
#define POWER_PIN   7
#define SIGNAL_PIN  A5
#define THRESHOLD   300

int value = 0;

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  pinMode(POWER_PIN, OUTPUT);
  digitalWrite(POWER_PIN, LOW);
  digitalWrite(LED_PIN, LOW);
}

void turnSensorOn() {
  digitalWrite(POWER_PIN, HIGH);
}

void turnSensorOff() {
  digitalWrite(POWER_PIN, LOW);
}

int getAverageReading() {
  int total = 0;
  const int numSamples = 10;
  for (int i = 0; i < numSamples; i++) {
    total += analogRead(SIGNAL_PIN);
    delay(10);
  }
  return total / numSamples;
}

void checkWater() {
  value = getAverageReading();
  if (value > THRESHOLD) {
    Serial.println("Water is detected");
    digitalWrite(LED_PIN, LOW);  // Turn LED OFF when water is detected
  } else {
    Serial.println("Water is NOT detected");
    digitalWrite(LED_PIN, HIGH); // Turn LED ON when no water is detected
  }
}

void loop() {
  turnSensorOn();
  delay(10);
  checkWater();
  turnSensorOff();
  delay(500); // Add delay to reduce sensor readings frequency
}

