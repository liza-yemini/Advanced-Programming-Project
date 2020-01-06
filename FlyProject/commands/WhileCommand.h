//
// Created by liza on 05/01/2020.
//

#ifndef FLYPROJECT_WHILECOMMAND_H
#define FLYPROJECT_WHILECOMMAND_H


#include "Command.h"
#include "ConditionParser.h"

class WhileCommand: public ConditionParser {
    //map<string, Command*> commandsMap;
    //void updateMap();
   // int numOfValues = 0;
public:
    int execute();
};


#endif //FLYPROJECT_WHILECOMMAND_H
