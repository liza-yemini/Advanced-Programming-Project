//
// Created by liza on 24/12/2019.
//

#include <thread>
#include "globalsVars.h"
#include "../MathInterpreter/Calc.h"
std::mutex Mutex_lock;
int INDEX = 0;
bool IsDone = false;
vector<string> Code;
map<string,VariableExtend*> varsTable;
map<string,VariableExtend*> simTable;
vector<std::thread> threads;
map<string, Command*> commandsMap;

