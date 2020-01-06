//
// Created by liza on 24/12/2019.
//

#include "ConnectCommand.h"

using namespace std;

#include <sys/socket.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <algorithm>

int startClient(string ipString, string portString) {
    string str = ipString;
    //erase the " " sign
    str.erase(str.begin());
    str.erase(str.end() - 1);
    const char *ip = str.c_str();

    // transfer the port number expression into int
    Interpreter* i = new Interpreter();
    Expression* e = nullptr;
    e = i->interpret(portString);
    int port = e->calculate();
    //create socket
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        //error
        std::cerr << "Could not create a socket" << std::endl;
        exit(1);
    }

    //We need to create a sockaddr obj to hold address of server
    sockaddr_in address; //in means IP4
    address.sin_family = AF_INET;//IP4
    address.sin_addr.s_addr = inet_addr(ip);  //the localhost address
    //address.sin_addr.s_addr = inet_addr("127.0.0.1");  //the localhost address
    address.sin_port = htons(port);
    //we need to convert our number (both port & localhost)
    // to a number that the network understands.

    // Requesting a connection
    int is_connect = connect(client_socket, (struct sockaddr *) &address, sizeof(address));
    if (is_connect == -1) {
        std::cerr << "Could not connect to host server" << std::endl;
        exit(1);
    }
    //char msg[1024];
    //cin >> msg;
    //send the msg to the server
    //int is_sent = send(client_socket, msg, strlen(msg), 0);
    int is_sent = 0;
    while (!IsDone) {
        //cin >> msg;
        //send the msg to the server
        //iterate over the vars table and send to the server all the commands
        map<string, VariableExtend*>::iterator it;
        Mutex_lock.lock();
        for (it= varsTable.begin(); it!=varsTable.end(); it++) {
            // if the sign is out ("->") and the value updated so send the server the command
            if ((it->second->getIn() == InOrOut::out) && it->second->getToSend())
            {
                //get the value and convert to string
                double value = it->second->getValue();
                string stringValue = to_string(value);
                //create the string to send
                string set = "set";
                string temp = it->second->getSim();
                temp.erase(temp.begin());
                temp.erase(temp.end() - 1);
                temp = set +" " + temp;
                temp += " ";
                temp += stringValue + "\r\n";
                const char* sendCommand = temp.c_str();
                //send the command to the server
                int is_sent = send(client_socket, sendCommand, strlen(sendCommand), 0);
                it->second->setToSend(false);
            }
        }
        //unlock the mutex
        Mutex_lock.unlock();
        is_sent = -1;

    }

    close(client_socket);
    return 1;
}
// CHECK CLIENT
int ConnectCommand::execute() {
    //get the ip and port
    string ip = Code[INDEX + 1];
    string port = Code[INDEX + 2];
    //open new thread for the client
    std::thread clientThread(startClient,ip,port);
    clientThread.detach();
    return 3;
};
