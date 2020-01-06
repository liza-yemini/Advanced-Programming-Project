//
// Created by liza on 24/12/2019.
//

#ifndef FLYPROJECT_OPENSERVERCOMMAND_H
#define FLYPROJECT_OPENSERVERCOMMAND_H

#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include "Command.h"

using namespace std;

// key: openDataServer
class OpenServerCommand : public Command {
    int numOfValues = 2;
    int port;
public:
    int execute ();
};



#endif //FLYPROJECT_OPENSERVERCOMMAND_H
