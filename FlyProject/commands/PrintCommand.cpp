//
// Created by ziv on 24/12/2019.
//

#include "PrintCommand.h"
#include "../MathInterpreter/Calc.h"

int PrintCommand::execute() {
    string printingStr;

    if((Code[INDEX + 1].front()) == '"') {
        int length = Code[INDEX + 1].length() -2;
        printingStr = Code[INDEX + 1].substr(1,length);
    } else {
        Interpreter* i = new Interpreter();
        Expression* e = nullptr;
        string vars = GetVariables();
        i->setVariables(vars);
        e = i->interpret(Code[INDEX + 1]);
        printingStr = to_string(e->calculate());
    }
    cout << printingStr <<endl;
    /*// printing string
    int length = Code[INDEX + 1].length() -2;
    string printingStr = Code[INDEX + 1].substr(1,length);
    // if string is variable print the variable value.
    if (varsTable.find(Code[INDEX + 1]) != varsTable.end()) {
      //  printingStr = varsTable[Code[INDEX + 1]]->getValue();
      cout << varsTable[Code[INDEX + 1]]->getValue() <<endl;
    } else {
        cout << printingStr <<endl;
    }*/
    return 2;
}