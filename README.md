9. Docker

The project includes a Dockerfile containing the required build and debugging tools.

The Docker image is based on:

ubuntu:22.04

The image installs:

build-essential
gdb
valgrind

The application is compiled during image construction.

Build the Docker image
docker build -t campusguard .
Run the container
docker run --rm campusguard

The project also contains a Docker Compose configuration.

Run:

docker compose up --build

The container executes:

./campusguard
10. GDB Debugging

The Makefile provides a debug target:

make debug

This starts:

gdb ./campusguard

Useful GDB commands include:

break main
run
next
step
continue
print variable
backtrace
quit

A breakpoint can also be placed inside a specific operation, for example:

break EmergencyResponseFacade::reportEmergency

This can be used to inspect how the facade coordinates the subsystem components.

11. Valgrind

Valgrind can be used to check for memory-management problems.

The Makefile provides:

make valgrind

The intended command is:

valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./campusguard

Valgrind should be used to inspect:

Memory leaks
Invalid reads
Invalid writes
Invalid frees
Other memory-management errors