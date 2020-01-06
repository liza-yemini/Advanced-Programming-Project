//
// Created by liza on 25/12/2019.
//

#include <string>
#include <algorithm>
#include "EqualCommand.h"
#include <cctype>

int EqualCommand::execute() {

    Interpreter* i = new Interpreter();
    Expression* e = nullptr;
    try {
        string vars = GetVariables();
        i->setVariables(vars);
        string exp = Code[INDEX + 1];

        exp.erase(remove_if(exp.begin(), exp.end(), [](char c){
            return isspace(static_cast<unsigned char>(c));
        }), exp.end());
        e = i->interpret(exp);
        Mutex_lock.lock();
        double value = e->calculate();
        // update the value of the variable
        varsTable[Code[INDEX - 1]]->setValue(value);
        varsTable[Code[INDEX - 1]]->setToSend(true);
        Mutex_lock.unlock();
        delete i;
        delete e;
    } catch (const char* er) {
        if (e != nullptr) {
            delete e;
        }
        if (i != nullptr) {
            delete i;
        }
        std::cout << er << std::endl;
    }

    return 2;
}