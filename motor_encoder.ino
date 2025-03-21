#define ENA 9   // PWM Speed control
#define IN1 7   // Motor direction control
#define IN2 8   // Motor direction control

#define ENCODER_A 2  // Encoder A phase (must be interrupt)
#define ENCODER_B 3  // Encoder B phase (must be interrupt)

volatile int encoderCount = 0;
int prevEncoderCount = 0;
float speed = 0;
void encoderISR() {
  if (digitalRead(ENCODER_A) == digitalRead(ENCODER_B)) {
    encoderCount++;  // Forward rotation
  } else {
    encoderCount--;  // Reverse rotation
  }
}

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(ENCODER_A, INPUT_PULLUP);
  pinMode(ENCODER_B, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(ENCODER_A), encoderISR, CHANGE);
  digitalWrite(IN1, HIGH);
digitalWrite(IN2, LOW);
analogWrite(ENA, 50); // Speed (0-255)


  Serial.begin(9600);
}
void loop() {
  // Move Forward

  delay(1000);
  Serial.print("Encoder Count: ");
  Serial.println(encoderCount);
  Serial.print("Speed (RPM): ");
  speed = (encoderCount-prevEncoderCount)*60.0/(450.0);

  Serial.println(speed);

  prevEncoderCount = encoderCount;

  // Move Backward
  //digitalWrite(IN1, LOW);
  //digitalWrite(IN2, HIGH);
  //analogWrite(ENA, 100);
  //delay(1000);
  //Serial.print("Encoder Count: ");
  //Serial.println(encoderCount);
  // Stop


}
