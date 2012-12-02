#include <Servo.h>

#define LED_PIN 11
#define SERVO_PIN 3

#define WAKE_STATE 0
#define SLEEP_STATE 1

#define SERVO_ROTATE_MAX 90

Servo rot;
byte state = WAKE_STATE;

void wait(unsigned long waitMillis) {
  unsigned long writeMillis = millis();
  while (millis() - writeMillis < waitMillis);
}

void setup() {
  wait(1000);
  pinMode(LED_PIN, OUTPUT);
  rot.attach(SERVO_PIN);
  for (int i = 0; i <= SERVO_ROTATE_MAX; i++) {
    rot.write(i);
    wait(40);
  }
}

void loop() {
  if (state == WAKE_STATE) {
    wakeCycle();
    if (random(0, 200) == 0) {
      state = !state;
    }
  } else if (state == SLEEP_STATE) {
    sleepCycle();
    if (random(0, 10) == 0) {
      state = !state;
    }
  } else {
    state = SLEEP_STATE;
  }
}

void wakeCycle() {
  analogWrite(LED_PIN, 255);
  if (random(0, 20) == 0) {
    rot.write(random(0, SERVO_ROTATE_MAX));
    if (random(0, 3) == 0) {
      rot.write(random(0, SERVO_ROTATE_MAX));
    }
  }
  wait(100);
}

void sleepCycle() {
  for (int i = 255; i >= 0; i--) {
    analogWrite(LED_PIN, i);
    wait(10);
  }
  wait(100 * random(1, 20));
  for (int i = 0; i < 256; i++) {
    analogWrite(LED_PIN, i);
    wait(10);
  }
}

