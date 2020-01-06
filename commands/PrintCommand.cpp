//
// Created by ziv on 24/12/2019.
//

#include "PrintCommand.h"
#include "../MathInterpreter/Calc.h"

int PrintCommand::execute() {
    string printingStr;

    if((Code[INDEX + 1].front()) == '"') {
        // case string
        int length = Code[INDEX + 1].length() -2;
        printingStr = Code[INDEX + 1].substr(1,length);
    } else {
        // case variable can also handle with expressions
        Interpreter* i = new Interpreter();
        Expression* e = nullptr;
        string vars = GetVariables();
        i->setVariables(vars);
        e = i->interpret(Code[INDEX + 1]);
        printingStr = to_string(e->calculate());
    }
    //printing the result
    cout << printingStr <<endl;

    return 2;
}