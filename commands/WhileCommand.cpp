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
    // the sign of the condition
    string sign = Code[INDEX + 2];
    //create condition to stop the while loop
    Condition* condition = new Condition();
    INDEX += 5;
    //counter for the steps in the while ( know how much steps to go back to the beggining
    int countTotalSteps = 0;
    // while condition is true
    while(condition->isTrue(left, sign, right))
    {
        countTotalSteps = 0;
        //while we didn't finished all the commands in the parentheses  keep going
        while (Code[INDEX].compare("}") != 0) {
            c = commandsMap[Code[INDEX]];
            // not command
            if (c == NULL) {
                INDEX++;
                countTotalSteps++;

            }else {
                //execute the command and update the index
                int numOfSteps = c->execute();
                countTotalSteps += numOfSteps;
                INDEX += numOfSteps;
            }
        }
        // return index to "while"
        INDEX = INDEX - countTotalSteps - 5;
        // update the condition
        updateLeftAndRight();
        //return index to "{"
        INDEX += 5;
    }
    deleteMap();
    // we need to keep going after '}'
    return countTotalSteps + 1 ;
}