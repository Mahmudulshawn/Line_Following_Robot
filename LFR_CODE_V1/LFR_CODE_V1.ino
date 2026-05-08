#include<QTRSensors.h>
#include<EEPROM.h>
QTRSensors qtr;

#define sensorNumber 8
uint16_t sensorValues[sensorNumber];
const uint16_t threshold = 500;

// MOTOR PINS
#define left_motor_forward 5        //BIN1
#define left_motor_backward 6       //BIN2

#define right_motor_forward 2       //AIN2
#define right_motor_backward 4      //AIN1

#define left_motor_speed 9          //PWMB
#define right_motor_speed 3         //PWMA

#define delay_before_turn 50
#define turnSpeed 150

String T_direction = "left";

// timers
#define stop_time 20

// inverse parameter
bool inverseON = 0; //0 = Normal Line, 1 = Inverse Line.

// distance calibration parameters
uint16_t test_time = 500;   //needs to be adjusted after building the bot
int measured_distance = 10;

#define cal_button 11
#define run_button 12
#define stop_button 13

#define LED 8

int sensorDigital[sensorNumber];
int weightValue[sensorNumber] = {10, 20, 30, 40, 50, 60, 70, 80};
int bitWeight[sensorNumber] = {1, 2, 4, 8, 16, 32, 64, 128};
int sumOnSensor; 
int sensorWeight;
int bitSensor;
int Max_Value[sensorNumber];
int Min_Value[sensorNumber];
int Reference_Value[sensorNumber];

// PID Variables
float line_position;
float center_position = 45;
float error;
float derivative, previous_error;
int base_speed = 200;
int kp = 8;
int kd = 0;

// turn variable
String direction = "straight";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  qtr.setTypeAnalog();
  qtr.setSensorPins((const uint8_t[]){A7, A6, A5, A4, A3, A2, A1, A0}, sensorNumber);
  qtr.setEmitterPin(7);

  pinMode(LED, OUTPUT);

  pinMode(left_motor_forward, OUTPUT);
  pinMode(left_motor_backward, OUTPUT);
  pinMode(right_motor_forward, OUTPUT);
  pinMode(right_motor_backward, OUTPUT);

  pinMode(left_motor_speed, OUTPUT);
  pinMode(right_motor_speed, OUTPUT);

  pinMode(cal_button, INPUT_PULLUP);
  pinMode(run_button, INPUT_PULLUP);
  pinMode(stop_button, INPUT_PULLUP);

  LoadCalibration(); //load calibration value from eeprom when arduino starts
}

void loop() {
  // motor(100, 100);
  // side_calibrate();
  // PID_Controller(base_speed, kp, kd);

  // distance(10); //go 10cm and stop
  // stop();

  // calibrateSensor();

  //Final Version
  // if(digitalRead(cal_button) == 0) {
  //   while(1){
  //     calibrateSensor();
  //   }
  // } 

  // if(digitalRead(run_button) == 0) {
  //   while(1) {
  //     PID_Controller();
  //   }
  // }

  // if(digitalRead(stop_button) == 0) {
  //   while(1) {
  //     stop();
  //   }
  // }
}
