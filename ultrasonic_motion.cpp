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
  int time_1, time_2;
  bool flag_1 = false, flag_2 = false;
  int left_distance, right_distance, prev_right = get_distance(8, 9), prev_left = get_distance(6, 7);
  int difference = 100;
  while (true) {
    left_distance = get_distance(6, 7);
    right_distance = get_distance(8, 9);
    if ((abs(left_distance - prev_left) > difference || abs(right_distance - prev_right) > difference) && left_distance > 0 && right_distance > 0 && prev_left > 0 && prev_right > 0) {
      if (left_distance > prev_left || right_distance > prev_right) {
        Serial.print("Further\n");
      } else if (left_distance < prev_left || right_distance < prev_right) {
        Serial.print("Closer\n");
      }
    }
    prev_left = left_distance;
    prev_right = right_distance;
    if (left_distance < max_distance && left_distance > 0 && flag_1 == false) {
      time_1 = millis();
      flag_1 = true;
    }
    if (right_distance < max_distance && right_distance > 0 && flag_2 == false) {
      time_2 = millis();
      flag_2 = true;
    }
    if (time_1 > 0 && time_2 > 0) {
      if (time_1 < time_2) {
        Serial.print("Left to right\n");
      } else if (time_1 > time_2){
        Serial.print("Right to left\n");
      }
      time_1 = 0;
      time_2 = 0;
      flag_1 = false;
      flag_2 = false;
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
