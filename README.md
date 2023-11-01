# Flight Simulator Project

An interpreter designed to control a remote-piloted vehicle (RPV) within the virtual environment of the [Flight-Gear simulator](https://www.flightgear.org/).

## Description

The Flight-Gear simulator functions both as a Server and a Client:

- **As a Server**: The simulator provides our program with real-time data regarding various flight parameters.
  
- **As a Client**: The simulator receives values from our project's server, which are then utilized to control the aircraft's flight.

## Getting Started

### Prerequisites

1. Download [FlightGear](https://www.flightgear.org/).
2. Download the project files and `fly.txt`.

### Setup

1. Launch FlightGear.
2. Go to `Settings` on the homepage.
3. Enter the following under `Additional Settings`:

--telnet=socket,in,10,127.0.0.1,5402,tcp
--httpd=8080
--generic=socket,out,10,127.0.0.1,5400,tcp,generic_small

- The first command instructs the simulator to initiate a background server that allows telnet client connections.
- The second command directs the simulator to initiate a client which will connect to our project's server via socket.
- `10` denotes the frequency of receiving (in) or sending (out) data.

**Note**: Ensure our server is running before launching the simulator.

### Compilation and Execution

In your terminal or command prompt, navigate to the project directory and execute:

```bash
g++ main.cpp         # Compile the program
./a.out fly.txt      # Run the program using the fly.txt file
```

Finally, click Fly on FlightGear. The aircraft should now begin its flight.

### Development Environment
This project was developed on Linux.

### Authors 
Ziv Zaarur
Liza Yemini
