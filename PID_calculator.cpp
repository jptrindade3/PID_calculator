/*
  PID_calculator.cpp

  Author: jptrindade3
  April, 2020

  Description: The objective of this library is to create a single function 
  that can be called in any code and, with especific parameters, can easily
  return the total sum of the PID. Besides that, it can operate the total PID
  with the expected strip value and return an usable value to use in the actuator.
*/
#include "PID_calculator.h"

/*
    -----// function void PID::PID_total_val(float kp, float ki, float kd, float error, float desired_val) //-----
  This function will get, respectively, the proportional, the integral and the derivative constans; 
  the actual value mesured and the desired value. With this 5 values, It'll calculate the error and 
  the total PID.
*/
void PID::PID_total_val(float kp, float ki, float kd, float actual_val, float desired_val){
  float PID_p, PID_i, PID_d;
  float time_prev, time;
  
  if(PID::PID_begin == false){
    time = millis();
    PID_p = 0;
    PID_i = 0;
    PID_d = 0;
    PID::PID_begin = true;
  }
  else{
    PID_i = PID::PID_i_val;
    time = PID::time_prev;
  }
  float error = actual_val - desired_val;
  float previous_error = PID::previous_error;

  /*Proportional part*/
  PID_p = kp * error;

  /*Integral part*/
  PID_i = PID_i + (ki * error);

  /*Derivative part*/
  time_prev = time;
  time = millis();
  PID_d = kd * ((error - previous_error)/((time - time_prev)/1000));
  
  //Updating values
  PID::time_prev = time;
  PID::PID_i_val = PID_i;
  PID::previous_error = error;
  PID::PID_val = PID_p + PID_i + PID_d; /*PID total value*/

  Serial.println(time);
}
/*-----//--------------------//-------------------//-----*/




/*
    -----// function void PID::PID_to_actuator(int min_val, int max_val) //-----
  This function will get your current PID value, check if it is between the expected values (min_val and max_val,
  the needed parameters) and then returns and permmited PID value to your actuator. The function will only work
  if the PID was calculated al least once before. 
*/
void PID::PID_to_actuator(float min_val, float max_val){
  
  if(PID::PID_begin == true){  
  
    float PID_val = PID::PID_val;
  
    if(PID::actuator_begin == false){
      float minimum, maximum;
      if(min_val < 0){
        minimum = min_val * (-1);
      }
      else{
        minimum = min_val;
      }
  
      if(max_val < 0){
        maximum = max_val * (-1);
      }
      else{
        maximum = max_val;
      }
  
      _max_variation = (maximum - minimum);
      _max = maximum;
      _min = minimum;
      
      PID::actuator_begin = true;
    }
    
    if(PID_val < -_max_variation){
      PID_val = -_max_variation;
    }
    if(PID_val > _max_variation){
      PID_val = _max_variation;
    }
    
    
    PID::PID_val = PID_val;
    
  }
}
/*-----//--------------------//-------------------//-----*/




/*
    -----// function void PID::PID_reset() //-----
  This function will reset the current processes of the functions "PID_total_val()"
  and "PID_to_actuator()".
*/
void PID::PID_reset(){
  PID::PID_begin = false;
  PID::actuator_begin = false;
  PID::previous_error = 0;
}
/*-----//--------------------//-------------------//-----*/
