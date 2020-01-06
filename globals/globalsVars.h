//
// Created by liza on 24/12/2019.
//

#ifndef FLYPROJECT_GLOBALSVARS_H
#define FLYPROJECT_GLOBALSVARS_H

#include <thread>
#include <map>
#include <string>
#include <vector>
#include <mutex>
#include "../commands/Command.h"
#include "../MathInterpreter/Calc.h"
#include "../VariableExtend.h"

using namespace std;

//global mutex for the maps(2)
extern mutex Mutex_lock;

// global - true when done read Code
extern bool IsDone;

// gloval variable for indexing the output of lexer
extern int INDEX;
extern vector<string> Code;

// maps for name or sim to variableExtended
extern map<string,VariableExtend*> varsTable;
extern map<string,VariableExtend*> simTable;

//get the variables from var table and return them as string for interperter
static string GetVariables() {
    Mutex_lock.lock();
    string vars = "";
    map<string,VariableExtend*>::iterator itor;
    //make the string
    for(itor = varsTable.begin(); itor != varsTable.end(); itor ++) {
        if(vars != "")
        {
            vars += ";" + itor->first + "=" + to_string(itor->second->getValue());
        }else {
            vars += itor->first + "=" + to_string(itor->second->getValue());
        }
    }
    Mutex_lock.unlock();
    return vars;
}
#endif //FLYPROJECT_GLOBALSVARS_H
