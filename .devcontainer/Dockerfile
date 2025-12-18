FROM mcr.microsoft.com/devcontainers/cpp:1-ubuntu-22.04

RUN apt-get update \
    && export DEBIAN_FRONTEND=noninteractive \
    && apt-get install -y --no-install-recommends \
        build-essential \
        cmake \
        ninja-build \
        clang \
        gdb \
        git \
        python3 \
        python3-pip \
        libomp-dev \
        openmpi-bin \
        libopenmpi-dev \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*
