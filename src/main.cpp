#include <Arduino.h>

// Motor A
#define IN1 16
#define IN2 17
#define ENA 5

// Motor B
#define IN3 18
#define IN4 19
#define ENB 4

// PWM
#define PWM_CH_A 0
#define PWM_CH_B 1
#define PWM_FREQ 200
#define PWM_RES  8

// PWM values
#define PWM_RUN 200
#define PWM_MAX 255

void setForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void pwmWrite(int v) {
  ledcWrite(PWM_CH_A, v);
  ledcWrite(PWM_CH_B, v);
}

void arranqueMartillo() {
  setForward();

  // === ELECTRIC HAMMERING ===
  for (int i = 0; i < 25; i++) {
    pwmWrite(PWM_MAX);
    delay(25);
    pwmWrite(0);
    delay(25);
  }

  // === FINAL PUSH ===
  pwmWrite(PWM_MAX);
  delay(400);

  // === WORKING SPEED ===
  pwmWrite(PWM_RUN);
}

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  ledcSetup(PWM_CH_A, PWM_FREQ, PWM_RES);
  ledcSetup(PWM_CH_B, PWM_FREQ, PWM_RES);

  ledcAttachPin(ENA, PWM_CH_A);
  ledcAttachPin(ENB, PWM_CH_B);

  arranqueMartillo();
}

void loop() {
  // maintain rotation
  pwmWrite(PWM_RUN);
}
