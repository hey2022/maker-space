int get_distance(int echo, int trig);

void setup() {
  Serial.begin(9600);
  pinMode(6, INPUT);
  pinMode(7, OUTPUT);
  pinMode(8, INPUT);
  pinMode(9, OUTPUT);
}

void loop() {
  const int max_distance = 20;
  int time_1;
  int time_2;
  int left_distance;
  int right_distance;
  while (true) {
    left_distance = get_distance(6, 7);
    right_distance = get_distance(8, 9);
    if (left_distance < max_distance && left_distance > 0) {
      time_1 = millis();
    } else if (right_distance < max_distance && right_distance > 0) {
      time_2 = millis();
    }
    if (time_1 > 0 && time_2 > 0) {
      if (time_1 < time_2) {
        Serial.print("Left to right\n");
      } else if (time_1 > time_2){
        Serial.print("Right to left\n");
      }
      time_1 = 0;
      time_2 = 0;
    }
  }
}

int get_distance(int echo, int trig) {
  digitalWrite(trig, LOW);
  delayMicroseconds(1);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  int T = float (pulseIn(echo, HIGH, 18000)) / 58;
  return T;
}
