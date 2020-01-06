#include <iostream>
#include <thread>
#include "globals/globalsVars.h"


#include "Lexer.h"
#include "commands/ConnectCommand.h"
#include "commands/OpenServerCommand.h"
#include "commands/VarCommand.h"
#include "commands/SimCommand.h"
#include "commands/ExportCommand.h"
#include "commands/ImportCommand.h"
#include "commands/PrintCommand.h"
#include "commands/SleepCommand.h"
#include "MathInterpreter/Calc.h"
#include "commands/EqualCommand.h"
#include "commands/IfCommand.h"
#include "commands/WhileCommand.h"

void DeleteAll(map<string, Command*> commandsMap){
    map<string,VariableExtend*>::iterator itor;
    for(itor = varsTable.begin(); itor != varsTable.end(); itor ++) {
        delete itor->second;
    }
    map<string,Command*>::iterator  it;
    for(it = commandsMap.begin(); it != commandsMap.end(); it++) {
        delete it->second;
    }
}

/*
void ThreadFunction(Command* command) {
    command->execute();
}
*/

void Parser(){
    // interpreter will have all the definitions of all the variables in the program
    Interpreter* interpreter;

    //add for each string the definition his command
    map<string, Command*> commandsMap;
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

    // loop Variable and commands
    Code = Lexer::Interpet("fly.txt");
    Command* c = NULL;
    while (INDEX < Code.size()) {
        c = commandsMap[Code[INDEX]];
        if (c == NULL) {
            INDEX++;
            continue;
        }
        INDEX += c->execute();
    }
    IsDone = true;

    //free all alocated memory.
    DeleteAll(commandsMap);
}


int main() {
    Parser();
}

