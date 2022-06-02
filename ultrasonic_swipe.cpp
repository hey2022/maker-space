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
  int left_distance, right_distance;
  while (true) {
    left_distance = get_distance(6, 7);
    right_distance = get_distance(8, 9);
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
        Serial.print("Swipe Right\n");
      } else if (time_1 > time_2){
        Serial.print("Swipe Left\n");
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
