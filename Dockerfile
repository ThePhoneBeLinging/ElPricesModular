# Use the latest Ubuntu image
FROM ubuntu:latest

# Set the maintainer label
LABEL maintainer="EAL"

# Install dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    g++ \
    git \
    libssl-dev \
    libsqlite3-dev \
    libfmt-dev \
    xorg-dev \
    gdb \
    && rm -rf /var/lib/apt/lists/*

# Set the working directory
WORKDIR /app

# Copy project files
COPY . /app