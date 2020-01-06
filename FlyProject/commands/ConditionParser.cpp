//
// Created by liza on 05/01/2020.
//

#include "ConditionParser.h"
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

void ConditionParser::updateLeftAndRight() {
    Interpreter *i = new Interpreter();
    Expression *e = nullptr;
    string vars = GetVariables();
    try {
        i->setVariables(vars);
        e = i->interpret(Code[INDEX + 1]);
        left = e->calculate();
        e = i->interpret(Code[INDEX + 3]);
        right = e->calculate();
    } catch (const char *er) {
        if (e != nullptr) {
            delete e;
        }
        if (i != nullptr) {
            delete i;
        }
    }
    delete i;
    delete e;
}

void ConditionParser::updateMap() {
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
}