//
// Created by liza on 24/12/2019.
//

#include <thread>
#include "globalsVars.h"
#include "../MathInterpreter/Calc.h"
std::mutex Mutex_lock;
bool IsDone = false;
int INDEX = 0;
vector<string> Code;
map<string,VariableExtend*> varsTable;
map<string,VariableExtend*> simTable;

