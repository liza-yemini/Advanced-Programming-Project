//
// Created by liza on 05/01/2020.
//

#include "WhileCommand.h"
#include "ConnectCommand.h"
#include "OpenServerCommand.h"
#include "VarCommand.h"
#include "SimCommand.h"
#include "ExportCommand.h"
#include "ImportCommand.h"
#include "PrintCommand.h"
#include "SleepCommand.h"
#include "EqualCommand.h"
#include "Condition.h"
#include "IfCommand.h"

//add for each string the definition his command
/*
void WhileCommand::updateMap() {
    commandsMap["connectControlClient"] = new ConnectCommand();
    commandsMap["openDataServer"] = new OpenServerCommand();
    commandsMap["var"] = new VarCommand();
    commandsMap["sim"] = new SimCommand();
    commandsMap["->"] = new ExportCommand();
    commandsMap["<-"] = new ImportCommand();
    commandsMap["Print"] = new PrintCommand();
    commandsMap["Sleep"] = new SleepCommand();
    commandsMap["="] = new EqualCommand();
    commandsMap["if"] = new IfCommand();
    commandsMap["while"] = new WhileCommand();

} */
int WhileCommand::execute() {
    // update the command map
    updateMap();
    updateLeftAndRight();
    Command* c = NULL;
    string sign = Code[INDEX + 2];
    Condition* condition = new Condition();
    INDEX += 5;
    int countTotalSteps = 0;
    while(condition->isTrue(left, sign, right))
    {
        countTotalSteps = 0;
        //while we didn't finished all the commands in the parentheses  keep going
        while (Code[INDEX].compare("}") != 0) {
            c = commandsMap[Code[INDEX]];
            if (c == NULL) {
                INDEX++;
                countTotalSteps++;

            }else {
                int numOfSteps = c->execute();
                countTotalSteps += numOfSteps;
                INDEX += numOfSteps;
            }
        }
        INDEX = INDEX - countTotalSteps - 5;
        updateLeftAndRight();
        INDEX += 5;
    }
    // we need to keep going after '}'
    return countTotalSteps + 1 ;
}