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
     /*   remove_if(exp.begin(), exp.end(),
                       [](char c){
                           return isspace(static_cast<unsigned char>(c));
                       }); */
        exp.erase(remove_if(exp.begin(), exp.end(), [](char c){
            return isspace(static_cast<unsigned char>(c));
        }), exp.end());
//        exp.erase(remove(exp.begin(), exp.end(), ' '));
        e = i->interpret(exp);
        Mutex_lock.lock();
        int value = e->calculate();
        varsTable[Code[INDEX - 1]]->setValue(value);
        varsTable[Code[INDEX - 1]]->setToSend(true);
        Mutex_lock.unlock();
    } catch (const char* er) {
        if (e != nullptr) {
            delete e;
        }
        if (i != nullptr) {
            delete i;
        }
        std::cout << er << std::endl;
    }
    delete i;
    delete e;
    return 2;
}