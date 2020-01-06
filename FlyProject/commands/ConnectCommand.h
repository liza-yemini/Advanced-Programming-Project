//
// Created by liza on 24/12/2019.
//
#ifndef FLYPROJECT_CONNECTCOMMAND_H
#define FLYPROJECT_CONNECTCOMMAND_H


#include "Command.h"

// key: connectControlClient
class ConnectCommand : public Command {
    int numOfValues = 3;
    const char* ip;
    int port;
    //int startClient();
public:
    int execute();
};

#endif //FLYPROJECT_CONNECTCOMMAND_H

