//
// Created by ziv on 24/12/2019.
//

#include "SimCommand.h"

int SimCommand::execute() {
    string temp = Code[INDEX + 1];
    temp.erase(temp.begin());
    temp.erase(temp.end() - 1);
    Mutex_lock.lock();
    simTable[temp] = varsTable[Code[INDEX - 2]];
    varsTable[Code[INDEX - 2]]->setSim(Code[INDEX + 1]);
    Mutex_lock.unlock();
    return 2;
}