int get_distance();

void setup() {
  Serial.begin(9600);
  pinMode(9, OUTPUT);
  pinMode(8, INPUT);
}

void loop() {
  int distance = get_distance();
  Serial.println(distance);
}

int get_distance() {
  digitalWrite(9, LOW);
  delayMicroseconds(1);
  digitalWrite(9, HIGH);
  delayMicroseconds(10);
  digitalWrite(9, LOW);
  int T = float (pulseIn(9, HIGH, 18000)) / 58;
  return T;
}
