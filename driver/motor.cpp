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

void bc::control_motor(uint powerPercentage)
{
  // ガード処理
  const auto powerPercentage_ = std::clamp(powerPercentage, static_cast<bc::uint>(0), static_cast<bc::uint>(100));

  if (wiringPiSetupGpio() == -1)
  {
    return;
  }

  int gpio_18 = 18;

  // PWMの式
  // PWM周波数 = 19.2MHz / clock / range
  // 19.2Mhzはラズパイの水晶発振子のクロック数

  // duty比 = duty / range
  // wiringPiでは rangeを1024固定とし、clockとduty
  //の2つのパラメータで制御する。

  int baseclock = 19200000;
  int range = 1024;

  double interval = 10.0; // 10ms
  double pulse = interval * powerPercentage_ / 100;

  double dutyRatio = pulse / interval;

  double hz = 1 / (interval * 0.001);
  int clock = (int)(baseclock / range / hz);
  int duty = (int)(dutyRatio * range);

  pinMode(gpio_18, PWM_OUTPUT);
  pwmSetMode(PWM_MODE_MS);
  pwmSetClock(clock);
  pwmSetRange(range);
  pwmWrite(gpio_18, duty);

}
