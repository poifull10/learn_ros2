#include <unistd.h>
#include "wiringPi/wiringPi.h"

int main()
{
  if (wiringPiSetupGpio() == -1) {
    return 1;
  }

  int gpio_18 = 18;

  //PWMの式
  //PWM周波数 = 19.2MHz / clock / range
  // 19.2Mhzはラズパイの水晶発振子のクロック数

  //duty比 = duty / range
  //wiringPiでは rangeを1024固定とし、clockとduty
  //の2つのパラメータで制御する。

  int baseclock = 19200000;
  int range = 1024;

  double interval = 10.0; //10ms
  double pulse = 0.0; //0ms

  double dutyRatio = pulse / interval;

  double hz = 1 / (interval * 0.001);
  int clock = (int)(baseclock / range / hz);
  int duty = (int)(dutyRatio * range );
  
  pinMode(gpio_18, PWM_OUTPUT);
  pwmSetMode(PWM_MODE_MS);
  pwmSetClock(clock);
  pwmSetRange(range);

  pulse = 9.9;
  while (1) {

    dutyRatio = pulse / interval;
    duty = (int)(dutyRatio * range );
    pwmWrite(gpio_18, duty);

    sleep(1);
  }

  return 0;
}
