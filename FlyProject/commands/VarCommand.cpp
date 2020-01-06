//
// Created by ziv on 24/12/2019.
//

#include "VarCommand.h"
#include "../MathInterpreter/Calc.h"
#include "../VariableExtend.h"

int VarCommand::execute() {
    Mutex_lock.lock();
    varsTable[Code[INDEX + 1]] = new VariableExtend();
    varsTable[Code[INDEX + 1]]->setName(Code[INDEX + 1]);
    Mutex_lock.unlock();
    return 2;
}