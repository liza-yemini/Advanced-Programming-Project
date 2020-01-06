**Flight Simulator Project**

An interpreter for controlling remote-piloted vehicle(RPV) using virtual space of the flight simulator
of Flight-Gear.

**Description**

The Flight-Gear simulator used as a Server and Client. As a server the simulator send's to out program the
information about the values the diffrent parameters of the flight in real time. 
As a client the simulator get's from the server of our project the values that have to inject to the simulator
for flying the airplane.

**Getting Started**

First of all download the FlightGear, the project and fly.txt.
At the home page of the FlightGear simulator enter to the Setting and then enter at the Additional Settings:
"--telnet=socket,in,10,127.0.0.1,5402,tcp --httpd=8080
 --generic=socket,out,10,127.0.0.1,5400,tcp,generic_small"
The first definition tell's the simulator to open at the background Server that every telnet client can connect
him.
The second definition tell's the simulator to open at the background client which will connect to our Server
by socket.
for making this definition work we have to open our Server before starting the simulator.
10 is the frequency of the recieve(in) or send(out).
After that on the cmd cd into the folder which the program download in and write:
"g++ main.cpp" - for compiling the program.
"./a.out fly.txt" - for running the program with the file fly.txt
and then click Fly on the FlightGear.
now the airplane should fly.

**Authors**

Ziv Zaarur 
Liza Yemini
