void PID_Controller(int base_speed, float p, float d) {
  read_black_line();

  if(sumOnSensor > 0){
    line_position = (float)sensorWeight / sumOnSensor;
    error = center_position - line_position;
  } else {
    error = previous_error;
  }

  switch(bitSensor) {
    // SOFT LEFT
    case 0b11100000:
    case 0b11000000:
      direction = LEFT;
      Last_Line = LEFT;
      break;

    // SOFT RIGHT
    case 0b00000111:
    case 0b00000011:
      direction = RIGHT;
      Last_Line = RIGHT;
      break;
    
    // SHARP LEFT
    case 0b11110000:
    case 0b11111000:
      direction = SHARP_LEFT;
      Last_Line = LEFT;
      break;

    // SHARP RIGHT
    case 0b00001111:
    case 0b00011111:
      direction = SHARP_RIGHT;
      Last_Line = RIGHT;
      break;
    
    // STRAIGHT
    case 0b00011000:
    case 0b00011100:
    case 0b00111000:
    case 0b00111100:
    case 0b00110000:
    case 0b00001100:
      direction = STRAIGHT;
      break;

    default:         
      direction = Last_Line; 
      break;
  }

  if(bitSensor == 0) {
    // delay(delay_before_turn);
    if(direction == RIGHT) {
      Last_Line = RIGHT;
      // distance(5);
      read_black_line();
      if(bitSensor == 0) {
        turnRight(turnSpeed, turnSpeed);
      }
    } else if(direction == SHARP_RIGHT) {
      Last_Line = RIGHT;
      // distance(5);
      read_black_line();
      if(bitSensor == 0 ){
        sharpRight(turnSpeed, turnSpeed);
        // delay(30);
      }
    } else if(direction == SHARP_LEFT) {
      Last_Line = LEFT;
      // distance(5);
      read_black_line();
      if(bitSensor == 0 ){
        sharpLeft(turnSpeed, turnSpeed);
        // delay(30);
      }
    } else if(direction == LEFT) {
      Last_Line = LEFT;
      distance(5);
      read_black_line();
      if(bitSensor == 0 ){
        turnLeft(turnSpeed, turnSpeed);
      }
    } 
  }
  //   else {
  //     if(Last_Line == LEFT) {
  //       sharpLeft(turnSpeed, turnSpeed);
  //     } else if(Last_Line == RIGHT) {
  //       sharpRight(turnSpeed, turnSpeed);
  //     }else {
  //       stop();
  //     }
  //   }
  //   previous_error = error;
  //   return;
  // }

  else if(bitSensor == 255) 
    {
    distance(10);
    read_black_line();
    while(bitSensor == 255) 
    {
      stop();
      read_black_line();
    }
    if(bitSensor == 0) {
      direction = T_direction;
      Last_Line = T_direction;
    } else if(bitSensor > 0 && bitSensor < 255) {
      direction = STRAIGHT;
      Last_Line = STRAIGHT;
    }
    previous_error = error;
    return;
  } else if(bitSensor == 231 || bitSensor == 247 ||
            bitSensor == 243 || bitSensor == 239 || bitSensor == 207) {
    inverseON = !inverseON;
    previous_error = error;
    return;
  }

  // -----------------PID Logic-------------------
  derivative = error - previous_error;
  int correction = (int)(error*p + derivative*d);
  correction = constrain(correction, -150, 150);

  previous_error = error;

  int left_motor_correction  = constrain(base_speed + correction, 0, 255);
  int right_motor_correction = constrain(base_speed - correction, 0, 255);

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