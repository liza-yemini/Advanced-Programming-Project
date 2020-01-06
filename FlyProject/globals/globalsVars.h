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
//global mutex
extern mutex Mutex_lock;
// gloval variable for indexing the output of lexer
extern int INDEX;
extern bool IsDone;
extern vector<string> Code;
extern map<string,VariableExtend*> varsTable;
extern map<string,VariableExtend*> simTable;
extern vector<std::thread> threads;
static string GetVariables() {
    Mutex_lock.lock();
    string vars = "";
    map<string,VariableExtend*>::iterator itor;
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
