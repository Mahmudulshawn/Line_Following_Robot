void motor(int LPWM, int RPWM) {
  LPWM = constrain(LPWM, -255, 255);
  RPWM = constrain(RPWM, -255, 255);
  // LEFT MOTOR
  if(LPWM > 0) {
    digitalWrite(left_motor_forward, LOW);
    digitalWrite(left_motor_backward, HIGH);
  }else {
    digitalWrite(left_motor_forward, HIGH);
    digitalWrite(left_motor_backward, LOW);
  }

  // RIGHT MOTOR
  if(RPWM > 0) {
    digitalWrite(right_motor_forward, LOW);
    digitalWrite(right_motor_backward, RIGHT);
  }else {
    digitalWrite(right_motor_forward, RIGHT);
    digitalWrite(right_motor_backward, LOW);
  }

  analogWrite(left_motor_speed, abs(LPWM));
  analogWrite(right_motor_speed, abs(RPWM));
}