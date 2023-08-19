#include "./delay.h"

void delayMicroSeconds(int time){
  usleep(time);
}

void delayMilliSeconds(int time){
  usleep(time*1000);
}

void delaySeconds(int time){
  usleep(time*1000000);
}
