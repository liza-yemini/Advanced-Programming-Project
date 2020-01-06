//
// Created by liza on 24/12/2019.
//

#include <iterator>
#include <thread>
#include "OpenServerCommand.h"

vector<string> getVarsOrder(){
    vector<string> sims;
    sims.push_back("/instrumentation/airspeed-indicator/indicated-speed-kt");
    sims.push_back("/sim/time/warp");
    sims.push_back("/controls/switches/magnetos");
    sims.push_back("/instrumentation/heading-indicator/offset-deg");
    sims.push_back("/instrumentation/altimeter/indicated-altitude-ft");
    sims.push_back("/instrumentation/altimeter/pressure-alt-ft");
    sims.push_back("/instrumentation/attitude-indicator/indicated-pitch-deg");
    sims.push_back("/instrumentation/attitude-indicator/indicated-roll-deg");
    sims.push_back("/instrumentation/attitude-indicator/internal-pitch-deg");
    sims.push_back("/instrumentation/attitude-indicator/internal-roll-deg");
    sims.push_back("/instrumentation/encoder/indicated-altitude-ft");
    sims.push_back("/instrumentation/encoder/pressure-alt-ft");
    sims.push_back("/instrumentation/gps/indicated-altitude-ft");
    sims.push_back("/instrumentation/gps/indicated-ground-speed-kt");
    sims.push_back("/instrumentation/gps/indicated-vertical-speed");
    sims.push_back("/instrumentation/heading-indicator/indicated-heading-deg");
    sims.push_back("/instrumentation/magnetic-compass/indicated-heading-deg");
    sims.push_back("/instrumentation/slip-skid-ball/indicated-slip-skid");
    sims.push_back("/instrumentation/turn-indicator/indicated-turn-rate");
    sims.push_back("/instrumentation/vertical-speed-indicator/indicated-speed-fpm");
    sims.push_back("/controls/flight/aileron");
    sims.push_back("/controls/flight/elevator");
    sims.push_back("/controls/flight/rudder");
    sims.push_back("/controls/flight/flaps");
    sims.push_back("/controls/engines/engine/throttle");
    sims.push_back("/controls/engines/current-engine/throttle");
    sims.push_back("/controls/switches/master-avionics");
    sims.push_back("/controls/switches/starter");
    sims.push_back("/engines/active-engine/auto-start");
    sims.push_back("/controls/flight/speedbrake");
    sims.push_back("/sim/model/c172p/brake-parking");
    sims.push_back("/controls/engines/engine/primer");
    sims.push_back("/controls/engines/current-engine/mixture");
    sims.push_back("/controls/switches/master-bat");
    sims.push_back("/controls/switches/master-alt");
    sims.push_back("/engines/engine/rpm");
    return sims;
}
vector<string> splitMsg(string msg) {
    vector<string> values;
    string val = "";
    for (unsigned int i = 0; i<msg.length(); i++) {
        string c = msg.substr(i,1);
        if (c == ",") {
            values.push_back(val);
            val = "";
        } else {
            val += c;
        }
    }
    values.push_back(val);
    //cout<<values.back();
    return values;
}
void handlingMsg(string msg) {
    //split the massage to strings of values
    vector<string> values = splitMsg(msg);
    vector<string> varsOrder = getVarsOrder();
    //assert the value to the variable->value
    Mutex_lock.lock();
    for(unsigned int i = 0 ; i<varsOrder.size(); i++) {
        if (simTable.find(varsOrder[i]) != simTable.end()) {
            if (simTable[varsOrder[i]]->getIn() == InOrOut::in){
                simTable[varsOrder[i]]->setValue(stoi(values[i]));
            }
        } else {
        }

    }
    Mutex_lock.unlock();
}

int startServer(int client_socket) {
 /*
    // transfer the port number expression into int
    Interpreter* i = new Interpreter();
    Expression* e = nullptr;
    e = i->interpret(portString);
    int port = e->calculate();
    //create socket
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
        //error
        std::cerr << "Could not create a socket"<<std::endl;
        //return -1;
    }

    //bind socket to IP address
    // we first need to create the sockaddr obj.
    sockaddr_in address; //in means IP4
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; //give me any IP allocated for my machine
    address.sin_port = htons(port);
    //we need to convert our number
    // to a number that the network understands.

    //the actual bind command
    if (bind(socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
        std::cerr<<"Could not bind the socket to an IP"<<std::endl;
        //return -2;
    }

    //making socket listen to the port
    if (listen(socketfd, 5) == -1) { //can also set to SOMAXCON (max connections)
        std::cerr<<"Error during listening command"<<std::endl;
        //return -3;
    } else{
        std::cout<<"Server is now listening ..."<<std::endl;
    }

    // accepting a client
    int client_socket = accept(socketfd, (struct sockaddr *)&address,
                               (socklen_t*)&address);
    // split to thread
    if (client_socket == -1) {
        std::cerr<<"Error accepting client"<<std::endl;
        //return -4;
    }
*/

    //char buffer[1024] = {0};
    // int valread = read(client_socket, buffer, 1024);
    // std::cout << buffer << std::endl;
    while(!IsDone) {
        char buffer[1024] = {0};
        //reading from client
        //cout<< "wait for recv";
        int valread = read(client_socket, buffer, 1024);
        // if the client didn't send anything stop reading his messages
        if (valread <= 0) {
            break;
        }
        handlingMsg(buffer);

    }
    return 0;
}
int InitServer(int port){
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
        //error
        std::cerr << "Could not create a socket"<<std::endl;
        //return -1;
    }

    //bind socket to IP address
    // we first need to create the sockaddr obj.
    sockaddr_in address; //in means IP4
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; //give me any IP allocated for my machine
    address.sin_port = htons(port);
    //we need to convert our number
    // to a number that the network understands.

    //the actual bind command
    if (bind(socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
        std::cerr<<"Could not bind the socket to an IP"<<std::endl;
        //return -2;
    }

    //making socket listen to the port
    if (listen(socketfd, 5) == -1) { //can also set to SOMAXCON (max connections)
        std::cerr<<"Error during listening command"<<std::endl;
        //return -3;
    }

    // accepting a client
    int client_socket = accept(socketfd, (struct sockaddr *)&address,
                               (socklen_t*)&address);
    close(socketfd); //closing the listening socket
    return client_socket;
}
int OpenServerCommand::execute() {
    string portString = Code[INDEX + 1];

    // transfer the port number expression into int
    Interpreter* i = new Interpreter();
    Expression* e = nullptr;
    e = i->interpret(portString);
    int port = e->calculate();
    delete i;
    delete e;

    //create socket
    int client_socket = InitServer(port);

    
    std::thread serverTrhead(startServer,client_socket);
    //threads.push_back(serverTrhead);
    serverTrhead.detach();
    //startServer();
    return 2;
}
