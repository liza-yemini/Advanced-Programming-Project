//
// Created by liza on 05/01/2020.
//

#ifndef FLYPROJECT_CONDITIONPARSER_H
#define FLYPROJECT_CONDITIONPARSER_H


#include "Command.h"

class ConditionParser :public Command {
    virtual int execute() = 0;

protected:
    void updateMap();
    void deleteMap();
    map<string, Command*> commandsMap;
    double left;
    double right;

    void updateLeftAndRight();

};


#endif //FLYPROJECT_CONDITIONPARSER_H
