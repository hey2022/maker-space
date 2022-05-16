int get_distance(int echo, int trig);

void setup() {
  Serial.begin(9600);
  pinMode(6, INPUT);
  pinMode(7, OUTPUT);
  pinMode(8, INPUT);
  pinMode(9, OUTPUT);
}

void loop() {
  unsigned long long miliseconds = millis();
  int left_distance = get_distance(6, 7);
  int right_distance = get_distance(8, 9);
//  Serial.print("Left: ");
//  Serial.print(left_distance);
//  Serial.print(" Right: ");
//  Serial.print(right_distance);
//  Serial.print("\n");
  if (left_distance < max_distance) {
    t1 = millis();
  } 
  else if (d2 < max_distance) {
    t2 = millis();
  }
  
  if (t1 > 0 && t2 > 0) {
    if (t1 < t2) {
      Serial.println("Left to right");
    } 
    else if (t2 < t1) {
      Serial.println("Right to left");
    }
    else {
      Serial.println("");
    }
    t1 = 0;
    t2 = 0;
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
