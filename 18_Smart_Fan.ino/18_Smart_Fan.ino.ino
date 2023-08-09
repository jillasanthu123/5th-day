const int irPin = 5;                // Arduino 2nd pin connected to signal pin of IR sensor
const int ledPin = 12;              // Arduino 12th pin connected to LED
const int motorPin1 = 3;            // Arduino 3rd pin connected to L293D pin Input1
const int motorPin2 = 4;            // Arduino 4th pin connected to L293D pin Input2
//const int motorPin3 = 8;            // Arduino 8th pin connected to L293D pin Input3
//const int motorPin4 = 9;            // Arduino 9th pin connected to L293D pin Input4
const int enablePin = 10;           // Arduino 10th pin connected to L293D pin Enable2
int detectionCount = 0;             // variable to keep track of number of detections

void setup() 
{
  pinMode(irPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  //pinMode(motorPin3, OUTPUT);
  //pinMode(motorPin4, OUTPUT);
  pinMode(enablePin, OUTPUT);
  Serial.begin(9600);
}

void clockwise() {
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  //digitalWrite(motorPin3, LOW);
  //digitalWrite(motorPin4, HIGH);
  analogWrite(enablePin, 255);
}

void anticlockwise() {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  //digitalWrite(motorPin3, HIGH);
  //digitalWrite(motorPin4, LOW);
  analogWrite(enablePin, 255);
}

void stopMotor() {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  //digitalWrite(motorPin3, LOW);
  //digitalWrite(motorPin4, LOW);
}

void loop()
{
  int irValue = digitalRead(irPin);
            // debounce delay

  if (irValue == 0) {
    digitalWrite(ledPin, LOW);
    detectionCount++;
    Serial.print("Object detected. Count: ");
    Serial.println(detectionCount);
    delay(2000);       // wait for 500ms to prevent multiple counts of the same object

    if (detectionCount % 2 == 1) {
      Serial.println("Even detection count. Rotating anticlockwise.");
      anticlockwise();
      delay(2000);
    } else  if (detectionCount % 2 == 0) {
      Serial.println("Odd detection count. Rotating clockwise.");
      clockwise();
      delay(2000);
    }
  } else {
    digitalWrite(ledPin, HIGH);
    stopMotor();
  }
}
