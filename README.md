## Build on raspi
```
git submodule update --init
cd driver/WiringPi
./build
# type sudo password
cd ../../
colcon build
```

## Run on raspi
```
# $ tmux
# Ctrl-b %
# $ ros2 run blackchicken image
# Ctrl-b o
$ ros2 run blackchicken power
```

## Run on client
```
# connect ps4 dual-shock to pc.
$ ros2 run joy joy_node
# joystick available!
```
