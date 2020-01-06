//
// Created by ziv on 24/12/2019.
//

#include "ExportCommand.h"
#include "../VariableExtend.h"

int ExportCommand::execute() {
    Mutex_lock.lock();
    varsTable[Code[INDEX - 1]]->setIn(InOrOut::out);
    Mutex_lock.unlock();
    return 1;
}