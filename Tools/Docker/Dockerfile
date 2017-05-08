FROM        gluttton/lacquer:5.6.2
MAINTAINER  gluttton@ukr.net
LABEL       Description="Container for building https://gitlab.com/Gluttton/PslRK." Version="0.2"
RUN         sed 's/main/main contrib non-free/g' /etc/apt/sources.list \
         && apt-get update -qq \
         && apt-get install -y -qq \
                google-mock \
                libboost-filesystem-dev \
                libboost-system-dev \
                libpugixml-dev \
                libqcustomplot-dev \
         && mkdir /usr/src/gmock/build \
         && cd /usr/src/gmock/build \
         && cmake .. && make \
         && cd /usr/lib \
         && ln -s /usr/src/gmock/build/libgmock.a . \
         && ln -s /usr/src/gmock/build/libgmock_main.a . \
         && ln -s /usr/src/gmock/build/gtest/libgtest.a . \
         && ln -s /usr/src/gmock/build/gtest/libgtest_main.a . \
         && for FILE in $(find /var/log/ -type f); \
            do \
                : > ${FILE}; \
            done \
         && rm -rf /usr/share/doc/* \
         && rm -rf /usr/share/man/* \
         && rm -rf /var/lib/apt/lists/*
