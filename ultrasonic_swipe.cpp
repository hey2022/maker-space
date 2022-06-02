int get_distance(int echo, int trig);
bool detect(

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
  int left_distance, right_distance;
  while (true) {
    left_distance = get_distance(6, 7);
    right_distance = get_distance(8, 9);
    if (detect() {
      time_1 = millis();
    }
    if (right_distance < max_distance && right_distance > 0) {
      time_2 = millis();
    }
    if (millis() - time_1 > 10000 || millis() - time_2 > 10000) {
      time_1 = 0;
      time_2 = 0;
    }
    if (time_1 > 0 && time_2 > 0 && (left_distance > max_distance || left_distance == 0) && (right_distance > max_distance || right_distance == 0)) {
      if (time_1 < time_2) {
        Serial.print("Swipe Right\n");
      } else if (time_1 > time_2){
        Serial.print("Swipe Left\n");
      }
      time_1 = 0;
      time_2 = 0;
      delay(500);
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

bool detect(int distance, int detect_range) {
  if (distance < detect_range && detect_range > 0) {
    return true;
  }
  return false;
}
