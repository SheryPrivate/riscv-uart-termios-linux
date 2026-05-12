# UART Communication using termios API in Linux

## Overview

This project demonstrates UART (Universal Asynchronous Receiver/Transmitter) communication in Linux using the `termios` API. The implementation configures a serial interface, transmits a test message, receives incoming data using non-blocking I/O with `select()`, and handles runtime errors gracefully.

The project was developed as part of the coding challenge for:

**RISC-V ACT Framework Enablement and M-Mode Firmware Validation on Hardware Board**

---

## Features

- UART initialization and configuration
- Configurable baud rate, parity, stop bits, and data bits
- Transmission of test messages over UART
- Non-blocking UART receive using `select()`
- Error handling for:
  - Invalid device paths
  - Permission issues
  - Read/write failures
- Clean and well-structured implementation
- Virtual UART testing using `socat`

---

## UART Configuration

| Parameter   | Value     |
|-------------|-----------|
| Baud Rate   | 115200    |
| Data Bits   | 8         |
| Parity      | None      |
| Stop Bits   | 1         |
| Flow Control| Disabled  |

---

## Technologies Used

- C Programming
- Linux System Programming
- termios API
- POSIX File Handling
- select() System Call
- socat Virtual Serial Ports

---

## Build Instructions

Compile the program using GCC:

```bash
gcc project.c -o project
