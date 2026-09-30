# CampusGuard 2026

## Practical 5

CampusGuard 2026 is an emergency-response platform designed to coordinate campus incidents, response teams, access control, and operator actions.

The project demonstrates the integration of six Gang of Four (GoF) design patterns:

1. **Command**
2. **Mediator**
3. **Adapter**
4. **Facade**
5. **State**
6. **Observer**

The system is implemented in **C++11** and demonstrates how these patterns can work together in a single coherent application.

---

# 1. Project Overview

CampusGuard models an emergency-response environment in which an operator can report and manage incidents occurring on campus.

The system coordinates:

* Emergency incidents
* Security teams
* Medical teams
* Facilities teams
* Access-control systems
* Operator commands
* Incident state transitions
* Notifications between response units
* Incident monitoring and logging

The application also integrates a legacy access-control system whose interface is incompatible with the interface expected by the modern CampusGuard system.

The integration is demonstrated through two runtime scenarios:

### Scenario 1 – Laboratory Fire

A fire is reported in the Science Building.

The system:

1. Creates the incident.
2. Restricts access to the affected area.
3. Dispatches the security team.
4. Assigns medical and facilities teams.
5. Moves the incident through its response states.
6. Coordinates communication between response teams.
7. Evacuates the area.
8. Activates an emergency alarm.
9. Resolves the incident.
10. Releases the response teams.
11. Restores access to the affected area.

### Scenario 2 – Cancelled Security Incident

An unauthorized-access incident is reported at a residence hall.

The system:

1. Creates the incident.
2. Restricts access to the affected area.
3. Assigns response teams.
4. Cancels the incident.
5. Releases the assigned teams.
6. Attempts an evacuation command after cancellation.
7. Correctly rejects the invalid operation.
8. Restores access to the affected area.

---

# 2. Design Patterns

## 2.1 Command Pattern

The Command pattern encapsulates operator actions as command objects.

Commands implemented in the system include:

* `DispatchUnitCommand`
* `IssueEvacuationCommand`
* `ActivateAlertCommand`
* `CancelActionCommand`

The `Command` interface provides a common abstraction for executing operator actions.

`OperatorConsole` executes commands and maintains command history.

Example:

```cpp
console.execute(
    new IssueEvacuationCommand(security, *fire));
```

This allows the operator interface to work with different operations without directly implementing their behaviour.

---

## 2.2 Mediator Pattern

The Mediator pattern centralizes communication between response units.

The main mediator is:

```text
IncidentCoordinator
```

Response units communicate through the coordinator instead of directly depending on every other response unit.

The coordinator registers:

* Security
* Medical
* Facilities

For example, when Security reports that an area has been secured, the mediator can notify other registered response units.

This reduces direct coupling between the different response teams.

---

## 2.3 Adapter Pattern

The Adapter pattern integrates the legacy access-control system with the modern CampusGuard interface.

CampusGuard expects the following abstraction:

```text
AccessControlService
```

The legacy system instead provides:

```text
LegacyAccessControlSystem
```

with operations such as:

```text
lockDoorById()
unlockDoorById()
```

The adapter:

```text
AccessControlAdapter
```

implements `AccessControlService` and translates CampusGuard operations into calls to the legacy system.

Conceptually:

```text
CampusGuard
     |
     v
AccessControlService
     |
     v
AccessControlAdapter
     |
     v
LegacyAccessControlSystem
```

For example:

```cpp
accessControl.restrictArea(area);
```

is translated by the adapter into:

```cpp
legacySystem->lockDoorById(area.getId());
```

The Facade and the rest of the application therefore depend on the modern interface rather than the legacy implementation.

---

## 2.4 Facade Pattern

The Facade pattern provides a simplified entry point into the emergency-response subsystem.

The main facade is:

```text
EmergencyResponseFacade
```

Its primary operation is:

```cpp
reportEmergency(...)
```

This operation coordinates several subsystem operations, including:

1. Creating an `Incident`
2. Restricting access through `AccessControlService`
3. Registering response units with `IncidentCoordinator`
4. Creating and executing a dispatch command
5. Assigning additional response units
6. Returning the created incident to the caller

The facade therefore hides the complexity of coordinating these subsystems from `main()`

## 2.5 State Pattern

The State pattern represents the lifecycle of an incident.

An incident can move through states including:

```text
Reported
   |
   v
Dispatched
   |
   v
InProgress
   |
   v
Resolved
```

An incident can also be cancelled:

```text
Reported / Dispatched / InProgress
              |
              v
          Cancelled
```

The state classes determine which operations are valid in each state.

For example, attempting an evacuation after an incident has already been cancelled is rejected by the system.

This prevents the application from relying on large conditional statements to determine the behaviour of an incident.

---

## 2.6 Observer Pattern

The Observer pattern is used to monitor incident state changes.

The incident acts as the subject and can notify registered observers.

The implementation includes:

```text
Dashboard
IncidentLogger
```

The dashboard displays state changes, while the incident logger records them.

For example:

```text
[Dashboard] Incident #1001:
Dispatched -> InProgress
```

The logger stores these transitions for later display as an audit log.

---

# 3. Pattern Integration

The main integration flow combines multiple design patterns.

A simplified version is:

```text
Operator
   |
   v
EmergencyResponseFacade
   |
   +----> AccessControlAdapter
   |          |
   |          v
   |    LegacyAccessControlSystem
   |
   +----> Incident
   |          |
   |          +----> State
   |          |
   |          +----> Observer
   |
   +----> OperatorConsole
   |          |
   |          v
   |       Command
   |
   +----> IncidentCoordinator
              |
              v
        Response Units
```

During a typical emergency:

```text
Facade
  |
  +--> Adapter --> Legacy Access Control
  |
  +--> Command --> Incident
  |                  |
  |                  +--> State
  |                  |
  |                  +--> Observer
  |
  +--> Mediator --> Response Teams
```

This provides a single integrated workflow rather than six unrelated demonstrations of design patterns.
 
# 5. Requirements

The project requires:

* C++11-compatible compiler
* GNU Make
* Git
* Docker (for containerized execution)
* GDB (for debugging)
* Valgrind (for memory analysis)

The project has been tested with:

```text
g++
C++11
```

Compilation uses:

```text
-std=c++11
-Wall
-Wextra
-pedantic
-g
```

---

# 6. Building the Application

From the project root:

```bash
make
```

This compiles all `.cpp`:

```text
campusguard
```

The object files are placed under:

```text
build/
```

---

# 7. Running the Application

Run:

```bash
./campusguard
```

Alternatively:

```bash
make run
```

The program executes both integrated runtime scenarios and displays:

* Facade operations
* Access-control operations
* Command execution
* Incident state transitions
* Mediator communication
* Response-team activity
* Observer notifications
* Command history
* Incident audit logging
* Successful and failed operations

---

# 8. Cleaning the Build

To remove generated object files and the executable:

```bash
make clean
```

---

# 9. Docker

The project includes a Dockerfile containing the required build and debugging tools.

The Docker image is based on:

```text
ubuntu:22.04
```

The image installs:

* build-essential
* gdb
* valgrind

The application is compiled during image construction.

## Build the Docker image

```bash
docker build -t campusguard .
```

## Run the container

```bash
docker run --rm campusguard
```

The project also contains a Docker Compose configuration.

Run:

```bash
docker compose up --build
```

The container executes:

```text
./campusguard
```

---

# 10. GDB Debugging

The Makefile provides a debug target:

```bash
make debug
```

This starts:

```text
gdb ./campusguard
```

Useful GDB commands include:

```text
break main
run
next
step
continue
print variable
backtrace
quit
```

A breakpoint can also be placed inside a specific operation, for example:

```text
break EmergencyResponseFacade::reportEmergency
```

This can be used to inspect how the facade coordinates the subsystem components.

---

# 11. Valgrind

Valgrind can be used to check for memory-management problems.

The Makefile provides:

```bash
make valgrind
```

The intended command is:

```bash
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./campusguard
```

Valgrind should be used to inspect:

* Memory leaks
* Invalid reads
* Invalid writes
* Invalid frees
* Other memory-management errors

The final README should be updated with the actual Valgrind result after the project has been tested in the target environment.

---

# 12. Runtime Error Handling

The system demonstrates invalid-operation handling.

For example, once an incident has been cancelled, its response teams are released.

An attempt to execute an evacuation command afterwards is rejected.

The command system reports the failure:

```text
[Command] Security team is not assigned to Incident #1002
```

The operator console records the command as failed:

```text
[Console] FAILED
```

This demonstrates that the application does not assume that every requested operation is valid.

Other invalid conditions include:

* Executing a null command
* Dispatching an already committed response unit
* Executing the same command more than once
* Attempting operations that are invalid for the current incident state

---

# 13. Memory Ownership

The project uses explicit ownership relationships.

### EmergencyResponseFacade

The facade owns the `Incident` objects it creates.

```text
EmergencyResponseFacade
        |
        +---- owns ----> Incident
```

The incidents are deleted by the facade destructor.

### OperatorConsole

The operator console owns the command objects passed to it.

```text
OperatorConsole
       |
       +---- owns ----> Command
```

Commands are therefore not manually deleted by the caller after:

```cpp
console.execute(command);
```

### AccessControlAdapter

The adapter owns the legacy access-control object passed to it.

```text
AccessControlAdapter
        |
        +---- owns ----> LegacyAccessControlSystem
```

### Incident

An incident does not own its response units or observers.

The incident stores non-owning references/pointers to these collaborating objects.

This separation prevents the incident from deleting objects whose lifetime is controlled elsewhere.

---

# 14. Runtime Scenarios

## Scenario 1: Laboratory Fire

Location:

```text
Science Building
```

Incident:

```text
#1001
```

The scenario demonstrates:

* Facade
* Adapter
* Command
* Mediator
* State
* Observer

The incident progresses from:

```text
Reported
    ↓
Dispatched
    ↓
InProgress
    ↓
Resolved
```

Security secures the area, which is communicated through the mediator.

Medical responds after receiving the corresponding notification.

Security can then issue an evacuation command and Facilities can activate the emergency alarm.

When the incident is resolved, the assigned teams are released.

---

## Scenario 2: Cancelled Security Incident

Location:

```text
Residence Hall
```

Incident:

```text
#1002
```

The incident is cancelled after the response teams have been assigned.

The state transition is:

```text
Reported
    ↓
Dispatched
    ↓
Cancelled
```

After cancellation, the teams are released.

An evacuation command is then attempted.

The command fails because Security is no longer assigned to the incident.

This demonstrates state-dependent behaviour and invalid-operation handling.

---

# 15. Expected Output

The exact output may vary slightly depending on the environment, but the application should demonstrate messages similar to:

```text
CampusGuard 2026 - Integration Demo

=== SCENARIO 1: LABORATORY FIRE ===

[Facade] === Reporting Emergency ===
[LegacyAccessControlSystem] Locking door with ID: 101

[Console] >> DispatchUnit(Campus Security -> Incident #1001)
[Console] OK

[Dashboard] Incident #1001: Dispatched -> InProgress

[Security] ...
[Medical] ...
[Facilities] ...

[Console] >> IssueEvacuation(...)
[Console] OK

[Console] >> ActivateAlert(...)
[Console] OK

[Dashboard] Incident #1001: InProgress -> Resolved

[LegacyAccessControlSystem] Unlocking door with ID: 101


=== SCENARIO 2: CANCELLED SECURITY INCIDENT ===

[Facade] === Reporting Emergency ===
[LegacyAccessControlSystem] Locking door with ID: 202

[Console] >> CancelAction(...)
[Console] OK

[Console] >> IssueEvacuation(...)
[Console] FAILED

[LegacyAccessControlSystem] Unlocking door with ID: 202
```

The actual output contains additional mediator, observer, team, history, and audit-log messages.

---

# 16. Team Responsibilities

The project was developed by a team of three members.

### Member 1

Responsible primarily for:

* Domain core
* State pattern
* Command pattern

### Member 2

Responsible primarily for:

* Mediator pattern
* Observer pattern

### Member 3

Responsible primarily for:

* Adapter pattern
* Facade pattern
* Integration
* `main.cpp`
* Makefile
* Dockerfile
* Docker Compose
* README
* Runtime scenarios
* GDB testing
* Valgrind testing

The pattern implementations were integrated into a single application rather than being treated as isolated examples.

---

# 17. Design Principles Demonstrated

The implementation demonstrates several software-design principles:

### Encapsulation

Operations are encapsulated within appropriate classes rather than being concentrated in `main()`.

### Separation of Responsibilities

Each design pattern has a specific responsibility.

For example:

```text
Command  -> encapsulates actions
Mediator -> coordinates communication
Adapter  -> translates incompatible interfaces
Facade   -> simplifies subsystem interaction
State    -> manages incident lifecycle
Observer -> monitors state changes
```

### Polymorphism

Abstract interfaces such as:

```text
Command
AccessControlService
ResponseUnit
IncidentState
IncidentObserver
```

allow different concrete implementations to be used through common interfaces.

### Reduced Coupling

The Mediator reduces direct communication between response units, while the Adapter prevents the rest of the system from depending directly on the legacy access-control interface.

### Controlled Ownership

Objects that create and own dynamically allocated resources are responsible for releasing them.

---

# 18. Compilation Command

The project is compiled using:

```bash
g++ -std=c++11 -Wall -Wextra -pedantic -g -Iinclude
```

The Makefile automatically applies these options to all source files.

---

# 19. Submission Checklist

Before submission, verify:

* [ ] Project compiles successfully with `make`
* [ ] Application runs successfully
* [ ] Both runtime scenarios execute
* [ ] Command success and failure are visible
* [ ] Adapter integration is visible
* [ ] Facade coordinates multiple subsystems
* [ ] Mediator communication is visible
* [ ] State transitions are visible
* [ ] Observer notifications/logging are visible
* [ ] At least four patterns participate in an integrated flow
* [ ] Docker image builds successfully
* [ ] Docker container runs successfully
* [ ] GDB debugging has been demonstrated
* [ ] Valgrind has been run
* [ ] UML diagrams match the implementation
* [ ] README reflects the final implementation
* [ ] Git repository contains the required source and build files

---