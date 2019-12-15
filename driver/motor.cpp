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

  // PWMの式
  // PWM周波数 = 19.2MHz / clock / range
  // 19.2Mhzはラズパイの水晶発振子のクロック数

  // duty比 = duty / range
  // wiringPiでは rangeを1024固定とし、clockとduty
  //の2つのパラメータで制御する。

  constexpr unsigned int baseclock = 19200000;
  constexpr unsigned int range = 1024;
  constexpr double interval = 10.0; // 10ms
  constexpr double hz = 1 / (interval * 0.001);
  constexpr int clock = (baseclock / range / hz);

  double pulse = interval * powerStrength / 100;
  double dutyRatio = pulse / interval;
  int duty = (dutyRatio * range);

  int gpio = gpio_forward;
  if (powerPercentage < 0){
    gpio = gpio_backward;
  }

  pinMode(gpio, PWM_OUTPUT);
  pwmSetMode(PWM_MODE_MS);
  pwmSetClock(clock);
  pwmSetRange(range);
  pwmWrite(gpio, duty);

}
