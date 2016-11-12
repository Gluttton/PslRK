FROM        debian:jessie
MAINTAINER  gluttton@ukr.net
LABEL       Description="Container for building https://gitlab.com/Gluttton/PslRK." Version="0.1"
RUN         sed 's/main/main contrib non-free/g' /etc/apt/sources.list \
         && apt-get update -qq \
         && apt-get install -y -qq \
                cmake \
                g++ \
                gcovr \
                google-mock \
                libboost-filesystem-dev \
                libboost-system-dev \
                libpugixml-dev \
                make \
                qt5-default \
         && mkdir /usr/src/gmock/build \
         && cd /usr/src/gmock/build \
         && cmake .. && make \
         && cd /usr/lib \
         && ln -s /usr/src/gmock/build/libgmock.a . \
         && ln -s /usr/src/gmock/build/libgmock_main.a . \
         && ln -s /usr/src/gmock/build/gtest/libgtest.a . \
         && ln -s /usr/src/gmock/build/gtest/libgtest_main.a . \
         && rm -rf /var/lib/apt/lists/*
