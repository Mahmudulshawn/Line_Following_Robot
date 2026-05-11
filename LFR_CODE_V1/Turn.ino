void turnRight(int L, int R) {
  while(sensorDigital[0] != 1) { //loop breaks when sensor no 4 detects line
    motor(L, -R);           // right motor forward left motor backward
    read_black_line();      // continuously check sensor value
  }
  direction = "straight"; //after turn set direction to default
}

void turnLeft(int L, int R) {
  while(sensorDigital[7] != 1) { //loop breaks when sensor no 4 detects line
    motor(-L, R);           // right motor backward left motor forward
    read_black_line();      // continuously check sensor value
  }
  direction = "straight"; // after turn set direction to default
}

// void uTurn(int L, int R) {
//   String dir = "right";
//   // Phase 1: leave the line — spin until center loses it
//   while (sensorDigital[4] == 1) {
//     if (dir == "right") motor(L, -R);
//     else                motor(-L, R);
//     read_black_line();
//   }

//   delay(50);

//   // Phase 2: complete 180° — wait for opposite edge sensor
//   if (dir == "right") {
//     while (sensorDigital[7] != 1) {   // far right sensor confirms 180°
//       motor(L, -R);
//       read_black_line();
//     }
//   } else {
//     while (sensorDigital[0] != 1) {   // far left sensor confirms 180°
//       motor(-L, R);
//       read_black_line();
//     }
//   }

//   direction = "straight";
// }

void hard_stop() {
  while(1) motor(0, 0);
}

void stop() {
  motor(0, 0);
}

// void distance_calibration(uint16_t test_time) {
//   unsigned long startTime = millis();
//   while(millis() - startTime < test_time) {
//     motor(base_speed, base_speed); // forward movement
//   }
//   stop(); // stop after covering the required distance
// }

void distance(uint16_t dist) {
  int time_per_cm = test_time / measured_distance;
  unsigned long moveTime = (unsigned long)dist * time_per_cm;
  unsigned long startTime = millis();

  while(millis() - startTime < moveTime){
    motor(base_speed, base_speed);
  }
}