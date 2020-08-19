/*
  PID_calculator.h

  Author: jptrindade3
  April, 2020

  Description: The objective of this library is to create a single function 
  that can be called in any code and, with especific parameters, can easily
  return the total sum of the PID. Besides that, it can operate the total PID
  with the expected strip value and return an usable value to use in the actuator.
*/

#ifndef PID_calculator
#define PID_calculator

#include <Arduino.h>

class PID
{
  public:
    bool PID_begin = false;
    bool actuator_begin = false;
    float time_prev;
    float previous_error = 0;
    float PID_i_val;
    float PID_val;
    void PID_total_val(float kp, float ki, float kd, float actual_val, float desired_val); 
    void PID_to_actuator(float min_val, float max_val);
    void PID_reset();

  private:
    float _max, _min, _max_variation;
};

#endif
