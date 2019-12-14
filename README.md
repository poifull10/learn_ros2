## Build on raspi
```
$ git submodule update --init
$ cd driver/WiringPi
$ ./build
# type sudo password
$ cd ../../
$ colcon build
```

## Run on raspi
```
$ ros2 run blackchicken power
```

## Run on client
```
# connect ps4 dual-shock to pc.
$ ros2 run joy joy_node
# joystick is available!
```
