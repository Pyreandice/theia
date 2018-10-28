FROM debian:jessie

MAINTAINER github.com/ramity

WORKDIR /var/project

# Install cmake
ADD https://cmake.org/files/v3.13/cmake-3.13.0-rc2-Linux-x86_64.sh /cmake-3.13.0-rc2-Linux-x86_64.sh
RUN mkdir /opt/cmake
RUN sh /cmake-3.13.0-rc2-Linux-x86_64.sh --prefix=/opt/cmake --skip-license
RUN ln -s /opt/cmake/bin/cmake /usr/local/bin/cmake
RUN cmake --version

# Install libs
RUN apt-get update -y
RUN apt-get install -y build-essential
RUN apt-get install -y git
RUN apt-get install -y libgtk2.0-dev
RUN apt-get install -y pkg-config
RUN apt-get install -y libavcodec-dev
RUN apt-get install -y libavformat-dev
RUN apt-get install -y libswscale-dev
RUN apt-get install -y python-dev
RUN apt-get install -y python-numpy
RUN apt-get install -y libtbb2
RUN apt-get install -y libtbb-dev
RUN apt-get install -y libjpeg-dev
RUN apt-get install -y libpng-dev
RUN apt-get install -y libtiff-dev
RUN apt-get install -y libjasper-dev

# Install source
RUN cd /var && git clone https://github.com/opencv/opencv.git
RUN cd /var && git clone https://github.com/opencv/opencv_contrib.git
RUN cd /var && git clone https://github.com/opencv/opencv_extra.git

# Compile source
RUN cd /var/opencv && mkdir build
RUN cd /var/opencv/build && cmake ..
RUN cd /var/opencv/build && make -j7
RUN cd /var/opencv/build && make install

# Container process
ENTRYPOINT ["tail", "-f","/dev/null"]

# Container port(s)
EXPOSE 8080
