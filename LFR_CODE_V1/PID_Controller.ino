void PID_Controller(int base_speed, int p, int d) {
  read_black_line();

  if(sumOnSensor > 0){
    line_position = (float)sensorWeight / sumOnSensor;
    error = center_position - line_position;
  } else {
    error = 0;
  }

  switch(bitSensor) {
    case 0b11110000: direction = "left";     break;
    case 0b11111000: direction = "left";     break;
    case 0b11111100: direction = "left";     break;
    case 0b11111110: direction = "left";     break;

    case 0b00001111: direction = "right";    break;
    case 0b00011111: direction = "right";    break;
    case 0b00111111: direction = "right";    break;
    case 0b01111111: direction = "right";    break;

    default:         direction = "straight"; break;
  }

  if(bitSensor == 0) {
    delay(delay_before_turn);
    if(direction == "right") {
      turnRight(turnSpeed, turnSpeed);
    } else if(direction == "left") {
      turnLeft(turnSpeed, turnSpeed);
    }
    previous_error = error;
    return;
  } else if(bitSensor == 255) {
    distance(10);
    read_black_line();
    while(bitSensor == 255) {
      stop();
      read_black_line();
    }
    if(bitSensor == 0) {
      direction = T_direction;
    } else if(bitSensor > 0 && bitSensor < 255) {
      direction = "straight";
    }
    previous_error = error;
    return;
  } else if(bitSensor == 231 || bitSensor == 247 ||
            bitSensor == 243 || bitSensor == 239 || bitSensor == 207) {
    inverseON = !inverseON;
    previous_error = error;
    return;
  }

  // PID Logic
  derivative = error - previous_error;

  int max_correction = base_speed;
  int correction = constrain((int)(error * p + derivative * d),
                              -max_correction, max_correction);

  int left_motor_correction  = constrain(base_speed + correction, 0, 255);
  int right_motor_correction = constrain(base_speed - correction, 0, 255);

  previous_error = error;

  motor(left_motor_correction, right_motor_correction);
}

void side_calibrate() {
  read_black_line();

  Serial.print("Bit Sensor in Decimal: "+String(bitSensor));
  Serial.print(" | Bit Sensor in Binary: ");

  for(int i = 0; i < sensorNumber; i++) {
    Serial.print(String(bitRead(bitSensor, i)));
  }

  // if(bitSensor == 0b10000000) {
  //   Serial.print("  SIDE: Left");
  // }else if (bitSensor == 0b00000001) {
  //   Serial.print("  SIDE: Right");
  // }else {
  //   Serial.print("  SIDE: NULL");
  // }
  Serial.println();
}