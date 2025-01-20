/*
 * Arduino Water Sensor Example with Three LEDs
 * Green LED turns ON when water is detected,
 * Yellow LED turns ON when low water is detected,
 * Red LED turns ON when no water is detected.
 */

#define GREEN_LED_PIN  2
#define YELLOW_LED_PIN 3
#define RED_LED_PIN    4
#define POWER_PIN      7
#define SIGNAL_PIN     A5
#define WATER_THRESHOLD       300   // Water detected threshold
#define LOW_WATER_THRESHOLD   100   // Low water level threshold
#define SAMPLE_COUNT          10    // Number of samples for averaging
#define LOOP_DELAY            500   // Delay between readings (ms)

int value = 0;

void setup() {
  Serial.begin(9600);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(YELLOW_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(POWER_PIN, OUTPUT);
  digitalWrite(POWER_PIN, LOW); // Start with sensor OFF
  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(YELLOW_LED_PIN, LOW);
  digitalWrite(RED_LED_PIN, LOW);
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

void updateLEDs(bool green, bool yellow, bool red) {
  digitalWrite(GREEN_LED_PIN, green ? HIGH : LOW);
  digitalWrite(YELLOW_LED_PIN, yellow ? HIGH : LOW);
  digitalWrite(RED_LED_PIN, red ? HIGH : LOW);
}

void checkWater() {
  value = getAverageReading();
  Serial.print("Sensor Reading: ");
  Serial.println(value);

  if (value > WATER_THRESHOLD) {
    Serial.println("Water is detected:");
    Serial.println(value);
    updateLEDs(true, false, false);  // Green ON, Yellow OFF, Red OFF
  } else if (value > LOW_WATER_THRESHOLD) {
    Serial.println("Low water level detected:");
    Serial.println(value);
    updateLEDs(false, true, false); // Green OFF, Yellow ON, Red OFF
  } else {
    Serial.println("No water detected:");
    Serial.println(value);
    updateLEDs(false, false, true); // Green OFF, Yellow OFF, Red ON
  }
}

void loop() {
  turnSensorOn();  // Power the sensor
  delay(10);       // Stabilization delay
  checkWater();    // Check sensor reading
  turnSensorOff(); // Power down the sensor
  delay(LOOP_DELAY); // Delay before the next loop
}

