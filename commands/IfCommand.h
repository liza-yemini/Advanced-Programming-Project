//
// Created by liza on 05/01/2020.
//

#ifndef FLYPROJECT_IFCOMMAND_H
#define FLYPROJECT_IFCOMMAND_H

#include "Command.h"
#include "ConditionParser.h"

class IfCommand:public ConditionParser {
    //map<string, Command*> commandsMap;
    //void updateMap();
    //int numOfValues = 0;
public:
    int execute();
};


#endif //FLYPROJECT_IFCOMMAND_H
