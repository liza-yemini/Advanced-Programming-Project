//
// Created by liza on 24/12/2019.
//

#include <string>
#include <stack>
#include <queue>
#include <regex>
#include "Calc.h"
#include "../globals/globalsVars.h"

using namespace std;
bool isOperand(string s) {
    for (unsigned int i = 0; i < s.length(); i++) {
        if ((s[i] == 42) || (s[i] == 43) || (s[i] == 45) || (s[i] == 47) || (s[i] == 40) || (s[i] == 41) || s[i] == 35
            || s[i] == 36) {
            return false;
        }
    }
    return true;
}

bool isValue(string s) {

    regex b("^[-]*\\d+\\.?\\d*$");
    if (!regex_match(s, b)) {
        return false;
    }
    return true;
}

bool isValid(string s) {
    regex b("[a-zA-Z_][a-zA-Z_0-9]*");
    if (!regex_match(s, b)) {
        return false;
    }
    return true;
}
//Variable methods.............................................................
Variable::Variable(string n, double v) {
    name = n;
    value = v;
}

double Variable::calculate() {
    return value;
}
Variable &Variable::operator++() {
    value++;
    return *this;
}

Variable &Variable::operator--() {
    value--;
    return *this;
}

Variable &Variable::operator-=(double val) {
    value -= val;
    return *this;
}

Variable &Variable::operator+=(double val) {
    value += val;
    return *this;
}

Variable &Variable::operator--(int) {
    value--;
    return *this;
}

Variable &Variable::operator++(int) {
    value++;
    return *this;
}

//end variable methods.........................................................

// value methods...............................................................

Value::Value(double v) {
    this->val = v;
}
double Value::calculate() {
    return val;
}


//end value methods............................................................

//UnaryOperator methods........................................................
UPlus::UPlus(Expression *expression) {
    exp = expression;
}
double UPlus::calculate() {
    try {
        return exp->calculate();
    } catch (const char *e) {
        throw e;
    }
}
UPlus::~UPlus() {
    delete (exp);
}

UMinus::UMinus(Expression *expression) {
    exp = expression;
}
double UMinus::calculate() {
    try {
        double result = exp->calculate();
        result = -result;
        return result;
    } catch (const char *e) {
        throw e;
    }

}
UMinus::~UMinus() {
    delete (exp);
}

// end UnaryOperator methods...................................................


//BinaryOperator methods.......................................................

Plus::Plus(Expression *l, Expression *r) {
    this->left = l;
    this->right = r;
}

Minus::Minus(Expression *l, Expression *r) {
    this->left = l;
    this->right = r;
}

Mul::Mul(Expression *l, Expression *r) {
    this->left = l;
    this->right = r;
}

Div::Div(Expression *l, Expression *r) {
    this->left = l;
    this->right = r;
}

double Plus::calculate() {
    try {
        return left->calculate() + right->calculate();

    } catch (const char *e) {
        throw e;
    }
}
double Minus::calculate() {
    try {
        return left->calculate() - right->calculate();

    } catch (const char *e) {
        throw e;
    }
}
double Mul::calculate() {
    try {
        return left->calculate() * right->calculate();

    } catch (const char *e) {
        throw e;
    }
}
double Div::calculate() {
    try {
        double rightC = right->calculate();

        if (rightC == 0) {
            throw "bad input";
        }
        return left->calculate() / rightC;
    } catch (const char *e) {
        throw e;
    }
}

Plus::~Plus() {
    delete (left);
    delete (right);
}
Minus::~Minus() {
    delete (left);
    delete (right);
}
Mul::~Mul() {
    delete (left);
    delete (right);
}
Div::~Div() {
    delete (left);
    delete (right);
}
//end BinaryOperator methods...................................................

//interpreter methods..........................................................

void Interpreter::setVariables(string var) {
    unsigned int i = 0;
    while (i < var.length()) {
        size_t pos = var.find("=", i);
        string name;
        if (pos != string::npos) {
            name = var.substr(i, pos - i);
            if (!isValid(name)) {
                throw "bad input";
            }
            i = pos + 1;
        } else {
            break;
        }
        pos = var.find(";", i);
        if (pos == string::npos) {
            pos = var.length();
        }
        string value = var.substr(i, pos - i);
        if (!isValue(value)) {
            throw "bad input";
        }
        i = pos + 1;
        if (getValue(name) == '\0') {
            vars.insert(pair<string, double>(name, stod(value)));
        } else {
            vars.erase(name);
            vars.insert(pair<string, double>(name, stod(value)));
        }
    }
}

double Interpreter::getValue(string var) {
    if (vars.find(var) == vars.end()) {
        return '\0';
    }
    return vars[var];

}
// check if operator 1 is "+"/"-" and operator 2 is "*"/"/"
bool Interpreter::isGreater(char operator1, char operator2) {
    if (operator1 == '+' || operator1 == '-') {
        return true;
    } else if (operator2 == '+' || operator2 == '-') {
        return false;
    }
    return true;
}

Expression *Interpreter::interpret(string expression) {
    stack<char> operStack;
    queue<string> operQueue;
    int flag = 0;
    for (unsigned int i = 0; i < expression.length(); i++) {
        unsigned int j = i;
        // check the operand until get operator
        if (isOperand(expression.substr(i, 1))) {
            while (isOperand(expression.substr(j, 1)) && j < expression.length()) {
                j++;
            }
            operQueue.push(expression.substr(i, j - i));
            i = j - 1;
            flag = 1;
            if (!(operStack.empty()) && (operStack.top() == 35 || operStack.top() == 36)) {
                operQueue.push(string(1, operStack.top()));
                operStack.pop();
            }
        } else {
            // stack is empty
            if (operStack.empty()) {
                if (flag == 0 && expression[i] != '(') {
                    if ((expression[i] == 43)) {
                        operStack.push(35);
                    }
                    if ((expression[i] == 45)) {
                        operStack.push(36);
                    }

                } else {
                    operStack.push(expression[i]);
                }
            } else if (expression[i] == 40) {
                // == "("
                operStack.push(expression[i]);
            } else if (expression[i] == 41) {
                // == ")"
                while (operStack.top() != 40) {
                    // pop everything until "("
                    operQueue.push(string(1, operStack.top()));
                    operStack.pop();
                }
                operStack.pop();
                flag = 1;
                continue;
                // push operator
            } else if (isGreater(expression[i], operStack.top())) {
                if (flag == 0) {
                    // check for unnary operation.
                    if ((expression[i] == 43)) {
                        operStack.push(35);
                    }
                    if ((expression[i] == 45)) {
                        operStack.push(36);
                    } else {
                        // got 2 binary operators.
                        throw ("bad input");
                    }

                } else {
                    operStack.push(expression[i]);
                }
            } else {
                while (!(isGreater(expression[i], operStack.top()))) {
                    //got +,- after *,/
                    operQueue.push(string(1, operStack.top()));
                    operStack.pop();
                }
            }
            flag = 0;
        }
    }
    while (!operStack.empty()) {
        operQueue.push(string(1, operStack.top()));
        operStack.pop();
    }
    // end of change from infix to postfix

    stack<Expression *> operands;
    while (!operQueue.empty()) {
        string oper = operQueue.front();
        operQueue.pop();
        if (isOperand(oper)) {
            if (isValue(oper)) {
                Value *value = new Value(stod(oper));
                operands.push(value);
            } else if (!isValid(oper)) {
                throw "bad input";
            } else {
                double varVal = getValue(oper);
                /*if (varVal == '\0') {
                    throw "bad input";

                }*/
                Variable *var = new Variable(oper, varVal);
                operands.push(var);
            }
        } else {

            Expression *right = operands.top();
            operands.pop();
            if (!oper.compare("#")) {
                operands.push(new UPlus(right));
            } else if (!oper.compare("$")) {
                operands.push(new UMinus(right));
            } else {
                if (operands.empty()) {
                    throw "bad input";
                }
                Expression *left = operands.top();
                operands.pop();
                if (!oper.compare("*")) {
                    operands.push(new Mul(left, right));
                } else if (!oper.compare("/")) {
                    operands.push(new Div(left, right));
                } else if (!oper.compare("+")) {
                    operands.push(new Plus(left, right));
                } else if (!oper.compare("-")) {
                    operands.push(new Minus(left, right));
                } else {
                    throw "bad input";
                }
            }
        }
    }
    Expression *expression1 = operands.top();
    operands.pop();
    return expression1;
}

Interpreter::~Interpreter() {

}

//end interpreter methods......................................................