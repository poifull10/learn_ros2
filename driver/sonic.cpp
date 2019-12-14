
#include <stdlib.h>
#include <sys/time.h>

#include "bc_driver.h"

extern "C"
{
#include "wiringPi/wiringPi.h"
}

#define trigPin 2
#define echoPin 3

int pulseIn(int pin, int level, int timeout)
{
  struct timeval tn, t0, t1;
  long micros;

  gettimeofday(&t0, NULL);
  micros = 0;
  while (digitalRead(pin) != level)
  {
    gettimeofday(&tn, NULL);
    if (tn.tv_sec > t0.tv_sec)
      micros = 1000000L;
    else
      micros = 0;
    micros += (tn.tv_usec - t0.tv_usec);
    if (micros > timeout)
      return 0;
  }

  gettimeofday(&t1, NULL);
  while (digitalRead(pin) == level)
  {
    gettimeofday(&tn, NULL);
    if (tn.tv_sec > t0.tv_sec)
      micros = 1000000L;
    else
      micros = 0;
    micros = micros + (tn.tv_usec - t0.tv_usec);
    if (micros > timeout)
      return 0;
  }

  if (tn.tv_sec > t1.tv_sec)
    micros = 1000000L;
  else
    micros = 0;
  micros = micros + (tn.tv_usec - t1.tv_usec);
  return micros;
}

float measure_sonic()
{

  if (wiringPiSetupGpio() == -1)
    return 1;
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  digitalWrite(trigPin, LOW); // Added this line
  delayMicroseconds(2);       // Added this line
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH, 1000000);
  // printf("duration=%ld\n", duration);
  float distance = (duration / 2) / 29.1;
  // printf("distance=%ld cm\n", distance);
  return distance;
}
