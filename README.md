# TCP Client-Server Application

This project implements a simple TCP client-server application using Linux sockets in C++.
The server listens on a specified port and logs messages from connected clients.
Each client connects to the server at specified intervals and sends a message containing its name and a timestamp.

## Features

- Multi-threaded server capable of handling multiple client connections simultaneously.
- Clients periodically send messages to the server with timestamps and client names.
- Server logs messages to `log.txt` with thread safety.

## Requirements

- Linux environment
- C++11 or later
- CMake 3.10 or later (optional if building with `g++` directly)

## Setup

### 1. Clone the Repository

```sh
git clone https://github.com/st43r/TCPLogger.git
cd TCPLogger
```

### 2. Build the Project
Below are example commands for different build systems:

**Using `cmake`**:

- Ensure that you have CMake installed.
- Create a build directory and navigate to it:

   ```bash
   mkdir build
   cd build
   ```

- Run `cmake` and `make`:

   ```bash
   cmake ..
   make
   ```

**Using `g++` directly**:

You can compile the project using `g++` without CMake. This involves compiling the server and client separately.

##### Compile the Server

   ```bash
   g++ -o Server server/server.cpp server/tcpserver.cpp -pthread
   ```

##### Compile the Client

   ```bash
   g++ -o Client client/client.cpp client/tcpclient.cpp -pthread
   ```

### Usage

### Start the Server

Run the server with the port number on which it should listen.

```bash
./Server <port>
```

Example:

```bash
./Server 3000
```

### Start the Clients

Run the client with the following parameters:

1. **Name**: The name of the client.
2. **Port**: The port number of the server to connect to.
3. **Interval**: The interval in seconds between sending messages.

```bash
./Client <name> <port> <interval>
```

Example:

```bash
./Client Name1 3000 1
./Client Name2 3000 2
./Client Name3 3000 3
```

### Log Output

The server logs each client's messages to `log.txt` in the following format:

```
[yyyy-mm-dd hh:mm:ss.ms] "client_name"
```

Example:

```
[2024-08-10 13:50:01.000] Name1
[2024-08-10 13:50:02.000] Name1
[2024-08-10 13:50:02.010] Name2
[2024-08-10 13:50:03.000] Name1
[2024-08-10 13:50:03.010] Name3
```

## Implementation Details

- **Server**: The server listens on a specified port and accepts incoming connections. Each client connection is handled in a separate thread, and messages are logged using a mutex for thread safety.

- **Client**: The client connects to the server and sends messages at a specified interval. Each message includes the client's name and a timestamp.
