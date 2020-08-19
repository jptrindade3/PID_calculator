/*
  PID_calculator example

  Author: jptrindade3
  April, 2020
*/
#include <PID_calculator.h>

PID pid;

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  pid.PID_total_val(2, 1, 4, 6, 0);
  Serial.println(pid.PID_val);
  Serial.println("-----//-----//-----");
}
