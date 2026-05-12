# UART Communication using termios API in Linux

## Overview

This project implements UART (Universal Asynchronous Receiver/Transmitter) communication in Linux using the `termios` API. It demonstrates low-level serial communication by configuring UART parameters, transmitting data, and receiving responses using non-blocking I/O mechanisms.

The project was developed as part of the coding challenge for:

**RISC-V ACT Framework Enablement and M-Mode Firmware Validation on Hardware Board**

This implementation simulates real-world embedded Linux serial communication and validates UART behavior using virtual serial interfaces in a VMware-based Ubuntu environment.

---

## Key Objectives

- Configure UART interface using Linux `termios` API
- Implement reliable data transmission over serial interface
- Enable non-blocking data reception using `select()`
- Ensure robust error handling for system-level failures
- Validate UART communication using virtual serial ports (`socat`)

---

## Features

- UART device initialization and configuration
- Configurable communication parameters:
  - Baud Rate
  - Data Bits
  - Parity
  - Stop Bits
- Data transmission over UART interface
- Non-blocking data reception using `select()` system call
- Timeout-based read mechanism
- Comprehensive error handling:
  - Invalid device path handling
  - Permission denied handling
  - Read/write failure detection
- Clean and modular Linux system programming approach
- Virtual UART testing using `socat`

---

## UART Configuration

| Parameter      | Value   |
|----------------|---------|
| Baud Rate      | 115200  |
| Data Bits      | 8       |
| Parity         | None    |
| Stop Bits      | 1       |
| Flow Control   | None    |

---

## Technologies Used

- C Programming
- Linux System Programming
- POSIX APIs
- `termios` UART configuration
- `select()` for non-blocking I/O
- Virtual serial communication using `socat`

---

## Testing Environment

- Ubuntu Linux (VMware Workstation)
- GCC Compiler
- Virtual serial ports using `socat`
- `/dev/pts/*` pseudo-terminal interfaces for UART simulation

---

## Build Instructions

Compile the project using GCC:

```bash
gcc project.c -o project
