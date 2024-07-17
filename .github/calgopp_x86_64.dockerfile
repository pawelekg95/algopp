FROM ubuntu:22.04
SHELL ["/bin/bash", "-o", "pipefail", "-c"]

ARG DEBIAN_FRONTEND=noninteractive

# Initialize args
ARG CMAKE_VER=3.27.7
ARG CMAKE_URL="https://github.com/Kitware/CMake/releases/download/v${CMAKE_VER}/cmake-${CMAKE_VER}-linux-x86_64.tar.gz"
ARG HADOLINT_URL="https://github.com/hadolint/hadolint/releases/download/v2.10.0/hadolint-Linux-x86_64"

# Install base packages
RUN apt-get update && \
    apt-get install -y --no-install-recommends build-essential g++ llvm \
    python3 python3-pip shellcheck git make \
    clang-format clang-tidy wget xz-utils valgrind \
    lcov curl gnupg flex bison gdb \
    clang-tools python-is-python3 rsync && \
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
    mkdir doxygen-1.9.5/build

WORKDIR /root/doxygen-1.9.5/build

RUN cmake -G "Unix Makefiles" .. && \
    make && \
    make install
