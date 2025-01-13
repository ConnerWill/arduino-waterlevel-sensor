/*
 * Arduino Water Sensor Example
 * LED turns ON when no water is detected, OFF when water is detected.
 */

#define LED_PIN     2
#define POWER_PIN   7
#define SIGNAL_PIN  A5
#define THRESHOLD   300   // Water detection threshold
#define SAMPLE_COUNT 10   // Number of samples for averaging
#define LOOP_DELAY  500   // Delay between readings (ms)

int value = 0;

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  pinMode(POWER_PIN, OUTPUT);
  digitalWrite(POWER_PIN, LOW); // Start with sensor OFF
  digitalWrite(LED_PIN, LOW);   // Start with LED OFF
}

void turnSensorOn() {
  digitalWrite(POWER_PIN, HIGH);
}

void turnSensorOff() {
  digitalWrite(POWER_PIN, LOW);
}

int getAverageReading() {
  int total = 0;
  for (int i = 0; i < SAMPLE_COUNT; i++) {
    total += analogRead(SIGNAL_PIN);
  }
  return total / SAMPLE_COUNT;
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
  turnSensorOn();  // Power the sensor
  delay(10);       // Stabilization delay
  checkWater();    // Check sensor reading
  turnSensorOff(); // Power down the sensor
  delay(LOOP_DELAY); // Delay before the next loop
}
