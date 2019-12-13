FROM ubuntu:bionic

ENV DEBIAN_FRONTEND=noninteractive
RUN apt update && apt install -y curl gnupg2 lsb-release bash-completion git
RUN curl http://repo.ros2.org/repos.key | apt-key add -
RUN sh -c 'echo "deb [arch=amd64,arm64] http://packages.ros.org/ros2/ubuntu `lsb_release -cs` main" > /etc/apt/sources.list.d/ros2-latest.list'
ENV CHOOSE_ROS_DISTRO=dashing
RUN apt update && apt install -y ros-${CHOOSE_ROS_DISTRO}-desktop
RUN apt install -y python3-colcon-common-extensions python3-rosdep python3-argcomplete
RUN echo "source /opt/ros/${CHOOSE_ROS_DISTRO}/setup.bash" >> ~/.bashrc
RUN apt-get update && apt-get install -y ros-dashing-cv-bridge
