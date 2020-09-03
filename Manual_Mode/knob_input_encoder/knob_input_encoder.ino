#include <PIDController.h>
volatile long int encoder_pos = 0;
PIDController pos_pid; 
int motor_value = 255;

void setup() {

  Serial.begin(9600);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(5), encoder, RISING);

  pos_pid.begin();    
  pos_pid.tune(20, 0, 200);    
  pos_pid.limit(-255, 255);
}

void loop() {
pos_pid.setpoint((int)(((float)analogRead(A0)/1023) * 100.0 *1));
   motor_value = pos_pid.compute(encoder_pos);
if(motor_value > 0){
  MotorCounterClockwise(motor_value);
}else{
  MotorClockwise(abs(motor_value));
}
  Serial.println(encoder_pos);
  delay(2);
}



void encoder(){

  if(digitalRead(4) == HIGH){
    encoder_pos++;
  }else{
    encoder_pos--;
  }
}

void MotorClockwise(int power){
  if(power > 50){
  analogWrite(3, power);
  digitalWrite(2, LOW);
  }else{
    digitalWrite(3, LOW);
    digitalWrite(2, LOW);
  }
}

void MotorCounterClockwise(int power){
  if(power > 50){
  analogWrite(2, power);
  digitalWrite(3, LOW);
  }else{
    digitalWrite(3, LOW);
    digitalWrite(2, LOW);
  }
}
