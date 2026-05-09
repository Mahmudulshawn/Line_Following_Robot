void PID_Controller(int base_speed, int p, int d) {
  // while(1) {
  //   a:
      read_black_line();

      if(sumOnSensor > 0) line_position = sensorWeight / sumOnSensor;
      error = center_position - line_position;

      switch(bitSensor) {
        // Left Side Detection
        case 0b11111000: direction = "left"; break;
        case 0b11110000: direction = "left"; break;
        case 0b11111100: direction = "left"; break;

        // right side detection
        case 0b00011111: direction = "right"; break;
        case 0b00001111: direction = "right"; break;
        case 0b00111111: direction = "right"; break;
      }

      // turn execution when all sensors on white
      if(bitSensor == 0) {
        if(direction != "straight") {
          digitalWrite(LED, HIGH);  //turning on led as indicator when left or right is detected
          delay(delay_before_turn);

          if(direction == "right") {
          // right turn
            turnRight(turnSpeed, turnSpeed);
          }else {
          // left turn
            turnLeft(turnSpeed, turnSpeed);
          }
          digitalWrite(LED, LOW);  //LED off after turn
        }
      }else if (bitSensor == 255) { 
        //stop, T-intersection, Cross intersection
        // digitalWrite(LED, HIGH); //LED on when all black
        distance(10);            //Move additional 10cm to check
        read_black_line();       //Continuous checking for change
        while(bitSensor == 255) {//If all still black Stop
          stop();
          read_black_line();     //update sensor if its changin or not
        }

        if(bitSensor == 0) {
          direction = T_direction;
        }else {
          if(bitSensor > 0 && bitSensor < 255) {
            direction = "straight";
          }
        }
      }else if(bitSensor == 231 || bitSensor == 247 || bitSensor == 243 || bitSensor == 239 || bitSensor == 207) {
        inverseON = !inverseON;
        // digitalWrite(LED, HIGH);
        // Bit_Sensor_Show(); // For debugging Sensor values for both type of Lines.
        // goto a;
        return; // return to loop and start again immediately
      }
      // Bit_Sensor_Show();
      //digitalWrite(LED, LOW);

      // for(int i = sensorNumber; i > 0; i--) {
      //   Serial.print(String(bitRead(bitSensor, i)));
      // }

      // Serial.print(" Direction: "+String(direction));
      // Serial.println();

      derivative = error - previous_error;

      int left_motor_correction =  base_speed - (error * p + derivative * d);
      int right_motor_correction = base_speed + (error * p + derivative * d);

      previous_error = error;

      motor(left_motor_correction, right_motor_correction);
  // }
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