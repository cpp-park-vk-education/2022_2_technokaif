FROM gcc:latest
RUN apt update -y && \
    apt install -y cppcheck clang-tidy python3-pip libc6-dbg cmake libgtest-dev lcov libpqxx-dev openvpn qt5-default
RUN pip install cpplint
RUN wget https://sourceware.org/pub/valgrind/valgrind-3.18.1.tar.bz2 && \
    tar xfv valgrind-3.18.1.tar.bz2 && \
    cd valgrind-3.18.1 && \
    ./autogen.sh && \
    ./configure && \
    make && \
    make install
RUN cd /root && \
    wget https://boostorg.jfrog.io/artifactory/main/release/1.77.0/source/boost_1_77_0.tar.bz2 && \
    tar -xjf boost_1_77_0.tar.bz2 && \
    mv boost_1_77_0 /usr/local && \
    cd /usr/local/boost_1_77_0 && \
    ./bootstrap.sh && \
    ./b2 --with-system --with-thread --with-date_time --with-regex --with-serialization stage
