//
// Created by liza on 24/12/2019.
//

#ifndef FLYPROJECT_COMMAND_H
#define FLYPROJECT_COMMAND_H

#include <iostream>
#include <string>
#include "../globals/globalsVars.h"
using namespace std;
class Command {
public:
    virtual int execute() = 0;
};


#endif //FLYPROJECT_COMMAND_H
