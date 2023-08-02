const unsigned int NUMBER_OF_MODES = 2;
__attribute__((section(".noinit"))) unsigned int mode;

const int trigPin = 2;
const int echoPin = 3;

const int right_for = 8; 
const int right_back = 9; 
const int left_back = 11; 
const int left_for = 10; 

long duration;
int distance;

void setup() {
  if (++mode >= NUMBER_OF_MODES) mode = 0;
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(left_back, OUTPUT);
  pinMode(left_for, OUTPUT);
  pinMode(right_for, OUTPUT);
  pinMode(right_back, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  while (mode == 1) {
  move_forward();
  if (sonar_scan() > 20) {
    continue;
  }
  turn_right();
  delay(1000);
  }
}

void move_forward () {
  digitalWrite(right_for, HIGH);
  digitalWrite(right_back, LOW);
  digitalWrite(left_for, HIGH);
  digitalWrite(left_back, LOW);
}

void move_backward () {
  digitalWrite(right_for, LOW);
  digitalWrite(right_back, HIGH);
  digitalWrite(left_for, LOW);
  digitalWrite(left_back, HIGH);
}

void turn_left () {
  digitalWrite(right_for, HIGH);
  digitalWrite(right_back, LOW);
  digitalWrite(left_for, LOW);
  digitalWrite(left_back, HIGH);
}

void turn_right () {
  digitalWrite(right_for, LOW);
  digitalWrite(right_back, HIGH);
  digitalWrite(left_for, HIGH);
  digitalWrite(left_back, LOW);
}

int sonar_scan() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration*0.034/2;

  delay(1000);

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print("\n");

  return distance;
}