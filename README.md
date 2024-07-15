# TCP Server-Client Socket

This project demonstrates a simple TCP server-client communication using C. The server and client can exchange messages over a specified port, making it an ideal example for understanding basic socket programming.

## Table of Contents
- [Features](#features)
- [Requirements](#requirements)
- [Usage](#usage)
- [Compilation](#compilation)
- [Running the Server](#running-the-server)
- [Running the Client](#running-the-client)
- [Error Handling](#error-handling)
- [License](#license)

## Features
- Simple TCP server that listens for client connections.
- Client connects to the server and exchanges messages.
- Basic error handling for socket operations.
- Communication using the `select()` function for asynchronous handling.

## Requirements
- GCC compiler
- Unix-based operating system (Linux, macOS) (will work on Windows with Unix environment setup too)
- Basic knowledge of C Programming.

## Usage
1. Compile the server and client programs.
2. Run the server and client on the same or different machines.
3. Specify the hostname and port for the client to connect to the server.

## Compilation
```bash
gcc -o server server.c
gcc -o client client.c
```

## Running the Server
Start the server by specifying a port number:
```bash
./server [port]
```

## Running the Client
Start the server by specifying the hostname and same port number as the server:
```bash
./client [hostname] [port]
```

## Error Handling
- The server and client programs use the `error` function to print error messages and terminate the program when a critical error occurs.
- Proper error handling ensures that issues such as failed socket creation, binding, and connection attempts are reported.

## License
This project is open source and available under the [MIT License](https://github.com/avyuktsoni0731/socket-programming-c/blob/main/LICENSE).
