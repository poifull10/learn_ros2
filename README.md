## Build drivers
```
git submodule update --init
cd third_party/WiringPi
./build
cd ../../
gcc -o motor motor.c  -lwiringPi -I../third_party/WiringPi -pthread -lm -lcrypt -lrt
gcc -o sonic sonic.c  -lwiringPi -I../third_party/WiringPi -pthread -lm -lcrypt -lrt
```
Note: you need sudo when driving motors.

