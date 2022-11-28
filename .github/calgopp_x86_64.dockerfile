FROM ubuntu:20.04
SHELL ["/bin/bash", "-o", "pipefail", "-c"]

ARG DEBIAN_FRONTEND=noninteractive

# Initialize args
ARG CMAKE_VER=3.23.2
ARG CMAKE_URL="https://github.com/Kitware/CMake/releases/download/v${CMAKE_VER}/cmake-${CMAKE_VER}-linux-x86_64.tar.gz"
ARG HADOLINT_URL="https://github.com/hadolint/hadolint/releases/download/v2.10.0/hadolint-Linux-x86_64"

# Install base packages
RUN apt-get update && \
    apt-get install -y --no-install-recommends build-essential=12.8ubuntu1.1 g++=4:9.3.0-1ubuntu2 llvm=1:10.0-50~exp1 \
    python3=3.8.2-0ubuntu2 python3-pip=20.0.2-5ubuntu1.6 shellcheck=0.7.0-2build2 git=1:2.25.1-1ubuntu3.6 make=4.2.1-1.2 \
    clang-format=1:10.0-50~exp1 clang-tidy=1:10.0-50~exp1 wget=1.20.3-1ubuntu2 xz-utils=5.2.4-1ubuntu1.1 valgrind=1:3.15.0-1ubuntu9.1 \
    lcov=1.14-2 curl=7.68.0-1ubuntu2.14 gnupg=2.2.19-3ubuntu2.2 flex=2.6.4-6.2 bison=2:3.5.1+dfsg-1 \
    clang-tools=1:10.0-50~exp1 python-is-python2=2.7.17-4 rsync=3.1.3-8ubuntu0.4 && \
    ln -s /usr/bin/clang++-10 /usr/bin/clang++ && \
    ln -s /usr/bin/clang-10 /usr/bin/clang && \
    apt-get autoremove -y && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /root

# Download run-clang-format wrapper
RUN git clone https://github.com/Sarcasm/run-clang-format.git
WORKDIR /root/run-clang-format
RUN git checkout 39081c9c42768ab5e8321127a7494ad1647c6a2f . && \
    ln -s /root/run-clang-format/run-clang-format.py /usr/bin/

WORKDIR /root

# Install custom CMake version
RUN curl -o "cmake_v${CMAKE_VER}" -L "${CMAKE_URL}" && \
    mkdir -p "/opt/cmake/${CMAKE_VER}" && \
    tar -xf "$(basename cmake_v${CMAKE_VER})" -C "/opt/cmake/${CMAKE_VER}" --strip-components=1 && \
    rm "$(basename cmake_v${CMAKE_VER})" && \
    ln -s /opt/cmake/"${CMAKE_VER}"/bin/* /usr/bin/ && \
    apt-get autoremove -y && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

# Install hadolint - Dockerfile linter
RUN curl -o /usr/bin/hadolint -L "${HADOLINT_URL}" && \
    chmod 775 /usr/bin/hadolint

# Install base python packages
RUN pip3 --no-cache-dir install scipy==1.9.1 numpy==1.23.3 pylint==2.12.2

# Install doxygen
RUN curl https://www.doxygen.nl/files/doxygen-1.9.5.src.tar.gz -o doxygen-1.9.5.src.tar.gz && \
    tar -xvzf ./doxygen-1.9.5.src.tar.gz && \

WORKDIR /root/doxygen-1.9.5

RUN mkdir build && \
    cd build && \
    cmake -G "Unix Makefiles" .. && \
    make && \
    make install
