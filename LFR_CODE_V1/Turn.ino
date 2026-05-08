void turnRight(int L, int R) {
  while(sensorDigital[4] != 1) { //loop breaks when sensor no 4 detects line
    motor(R, -L);           // right motor forward left motor backward
    read_black_line();      // continuously check sensor value
    direction = "straight"; //after turn set direction to default
  }
}

void turnLeft(int L, int R) {
  while(sensorDigital[4] != 1) { //loop breaks when sensor no 4 detects line
    motor(-L, R);           // right motor backward left motor forward
    read_black_line();      // continuously check sensor value
    direction = "straight"; // after turn set direction to default
  }
}

void hard_stop() {
  while(1) motor(0, 0);
}

void stop() {
  motor(0, 0);
}

void distance_calibration(uint16_t test_time) {
  unsigned long startTime = millis();
  while(millis() - startTime < test_time) {
    motor(base_speed, base_speed); // forward movement
  }
  stop(); // stop after covering the required distance
}

void distance(uint16_t dist) {
  int time_per_cm = test_time / measured_distance;
  unsigned long moveTime = dist * time_per_cm;
  unsigned long startTime = millis();

  while(millis() - startTime < moveTime){
    motor(base_speed, base_speed);
  }
}