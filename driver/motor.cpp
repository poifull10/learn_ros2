#include "bc_driver.h"
#include <unistd.h>
#include <algorithm>

extern "C"
{
#include "wiringPi/wiringPi.h"
}

// 0 ~ 100のパーセンテージを引数として
// モーターの出力を制御する。
// min 0%のとき0、max 100%のとき100を引数とする。

void bc::control_motor(float powerPercentage)
{

  if (wiringPiSetupGpio() == -1)
  {
    return;
  }

  const auto powerStrength = std::clamp(std::abs(powerPercentage), static_cast<float>(0), static_cast<float>(100));
  constexpr int gpio_forward = 18;
  constexpr int gpio_backward = 15;

  constexpr unsigned int baseclock = 19200000;
  constexpr unsigned int range = 1024;
  constexpr double interval = 10.0; // 10ms
  constexpr double hz = 1 / (interval * 0.001);
  constexpr int clock = (baseclock / range / hz);

  double pulse = interval * powerStrength / 100;
  double dutyRatio = pulse / interval;
  int duty = (dutyRatio * range);

  pinMode(gpio_forward, PWM_OUTPUT);
  pinMode(gpio_backward, PWM_OUTPUT);
  pwmSetMode(PWM_MODE_MS);
  pwmSetClock(clock);
  pwmSetRange(range);
  pwmWrite(gpio, duty);

  if (powerPercentage < 0){
    digitalWrite(gpio_backward, 1);
  }else{
    digitalWrite(gpio_backward, 0);
  }
}
