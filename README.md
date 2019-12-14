## Build
```
git submodule update --init
cd third_party/WiringPi
./build
cd ../../
colcon build
```

## Run
```
$ tmux
Ctrl-b %
$ ros2 run blackchicken image
Ctrl-b o
$ ros2 run blackchicken power
```