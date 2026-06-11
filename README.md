# Network Tools in C

A networking project written in C to explore low-level socket programming, process management, and TCP/IP communication on Unix-like systems.

## Overview

This project contains two independent utilities:

- **Reverse Shell**: establishes an outgoing TCP connection and redirects a shell through the socket.
- **Port Listener**: listens for incoming TCP connections and accepts remote clients.

The objective of this project is educational: understanding how network communication and process interaction work at a low level.

## Features

### Reverse Shell

- TCP client implementation
- Remote connection to a specified host and port
- Standard stream redirection (`stdin`, `stdout`, `stderr`)
- Shell execution through the established connection

### Port Listener

- TCP server implementation
- Port binding and listening
- Connection acceptance
- Basic communication handling

## Technologies

- C99
- POSIX Sockets
- Unix System Calls
- GCC
- CMake

## Build

```bash
mkdir build
cd build

cmake ..
make
```

## Usage

### Start the Listener

```bash
./listener <host> <mode> <port>
```

Example:

```bash
./listener 127.0.0.1 1 65335
```

### Start the Reverse Shell

```bash
./reverse_shell <host> <port>
```

Example:

```bash
./reverse_shell 127.0.0.1 4444
```

## Learning Objectives

This project was developed to gain practical experience with:

- TCP/IP networking
- Socket programming
- Process creation and execution
- File descriptor management
- Client/server architectures
- Build automation with CMake

## Project Structure

```text
.
├── CMakeLists.txt
├── port_listener
│   ├── listener.c
│   └── reverseShell.c
└── README.md
```

## Disclaimer

This repository is intended for educational and research purposes only. All testing should be performed in controlled environments and on systems for which explicit authorization has been granted.