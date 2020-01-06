//
// Created by liza on 05/01/2020.
//

#include "IfCommand.h"
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
#include "WhileCommand.h"

//add for each string the definition his command
/*void IfCommand::updateMap() {
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

int IfCommand::execute() {
    // update the command map
    updateMap();
    Command* c = NULL;
    string sign = Code[INDEX + 2];
    //create new condition
    Condition* condition = new Condition();
    updateLeftAndRight();
    INDEX += 5;
    // check if the condition id true or false
    if(condition->isTrue(left, sign, right))
    {
        //while we didn't finished all the commands in the parentheses  keep going
        while (Code[INDEX].compare("}") != 0) {
            c = commandsMap[Code[INDEX]];
            if (c == NULL) {
                INDEX++;
                continue;
            }
            INDEX += c->execute();
        }
    } else {
        // jump INDEX to the end of the if section
        while (Code[INDEX].compare("}") != 0) {
            INDEX++;
        }
    }
    deleteMap();
    // we need to keep going after '}'
    return 1;
}