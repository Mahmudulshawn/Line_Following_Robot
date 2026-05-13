void turnRight(int L, int R) {
  while(sensorDigital[3] != 1 && sensorDigital[4] != 1) { //loop breaks when sensor no 4 detects line
    motor(0, R);           // right motor forward left motor backward
    read_black_line();      // continuously check sensor value
  }
}

void turnLeft(int L, int R) {
  while(sensorDigital[3] != 1 && sensorDigital[4] != 1) { //loop breaks when sensor no 4 detects line
    motor(L, 0);           // right motor backward left motor forward
    read_black_line();      // continuously check sensor value
  }
}

void sharpRight(int L, int R) {
  unsigned long beginTime = millis();
  while(!(sensorDigital[3] || sensorDigital[4])) { //loop breaks when sensor no 4 detects line
    motor(-L, R);           // right motor backward left motor forward
    read_black_line();      // continuously check sensor value

    // timeout after 500ms
    // if(millis() - beginTime > 500) {
    //   stop();
    //   break;
    // }
  }
}

void sharpLeft(int L, int R) {
  unsigned long beginTime = millis();
  while(!(sensorDigital[3] || sensorDigital[4])) { //loop breaks when sensor no 4 detects line
    motor(L, -R);           // right motor backward left motor forward
    read_black_line();      // continuously check sensor value

    // timeout after 500ms
    // if(millis() - beginTime > 500) {
    //   stop();
    //   break;
    // }
  }
}

void hard_stop() {
  while(1) motor(0, 0);
}

void stop() {
  motor(0, 0);
}

void distance(uint16_t dist) {
  int time_per_cm = test_time / measured_distance;
  unsigned long moveTime = (unsigned long)dist * time_per_cm;
  unsigned long startTime = millis();

  while(millis() - startTime < moveTime){
    motor(base_speed, base_speed);
    read_black_line();
  }
}
