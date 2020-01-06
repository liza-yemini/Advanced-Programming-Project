//
// Created by ziv on 24/12/2019.
//

#include <unistd.h>
#include "SleepCommand.h"

int SleepCommand::execute() {
    //handaling with expressions
    Interpreter* i = new Interpreter();
    Expression* e = nullptr;
    e = i->interpret(Code[INDEX + 1]);
    unsigned  int time = e->calculate();
    // sleep's argument is time in second (1 sec = 1000 milisec)
    sleep(time/1000);
    return 2;
}