#include "lpf.h"
#define pi 3.14159
lpf::lpf(double freq , double samplingtime) :
  cutoff_freq(freq),
  Ts(samplingtime)
{
  coeff = (2*pi*freq*Ts)/(1+2*pi*freq*Ts) ;
  init =true;
}


double lpf::filter(double state){

  if(init){
    x = state;
    y_n = x;
    init = false;
  }else{
    x = state;
     y_n1 = coeff * x + (1-coeff) * y_n;
    y_n = x;
  }
 return y_n1;

}
