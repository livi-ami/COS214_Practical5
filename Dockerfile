# TaskForge build & debug environment
FROM ubuntu:22.04

# Avoid interactive prompts during package install
ENV DEBIAN_FRONTEND=noninteractive

# g++/make for building, gdb for debugging, valgrind for memory checking
RUN apt-get update && apt-get install -y \
    build-essential \
    gdb \
    valgrind \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /campusguard

# Copy the whole project into the image
COPY . .

# Build on image creation, so a plain `docker run` has a ready binary.
# If you'd rather build inside a running container instead, remove this line.
RUN make

CMD ["/bin/bash"]