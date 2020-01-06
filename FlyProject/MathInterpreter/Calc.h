//
// Created by liza on 24/12/2019.
//

#ifndef FLYPROJECT_CALC_H
#define FLYPROJECT_CALC_H


#include <iostream>
#include <string>
#include <map>
#include "Expression.h"
using namespace std;
class Variable : public Expression {
private:
    string name;
    double value;
public:
    Variable(string n, double v);
    double calculate();
    Variable &operator++();
    Variable &operator--();
    Variable &operator+=(double);
    Variable &operator-=(double);
    Variable &operator--(int);
    Variable &operator++(int);
    string getName() {
        return this->name;
    }
    virtual ~Variable() {}
};

class Value : public Expression {
private:
    double val;

public:
    Value(double);
    double calculate();
    virtual ~Value() {}
};

class UnaryOperator : public Expression {
protected:
    Expression *exp;
public:
    virtual double calculate() = 0;
    virtual ~UnaryOperator() {}
};

class UPlus : public UnaryOperator {
public:
    UPlus(Expression *);
    double calculate();
    virtual ~UPlus();
};

class UMinus : public UnaryOperator {
public:
    UMinus(Expression *);
    double calculate();
    virtual ~UMinus();
};

class BinaryOperator : public Expression {
protected:
    Expression *left;
    Expression *right;

public:
    virtual double calculate() = 0;
    virtual ~BinaryOperator() {}
};
// all benary operator classes.
class Plus : public BinaryOperator {
public:
    Plus(Expression *, Expression *);
    double calculate();
    virtual ~Plus();
};

class Minus : public BinaryOperator {
public:
    Minus(Expression *, Expression *);
    double calculate();
    virtual ~Minus();
};

class Mul : public BinaryOperator {
public:
    Mul(Expression *, Expression *);
    double calculate();
    virtual ~Mul();
};

class Div : public BinaryOperator {
public:
    Div(Expression *, Expression *);
    double calculate();
    virtual ~Div();
};

class Interpreter {
private:
    // vector of variable
    map<string, double> vars;
public:
    void setVariables(string);
    double getValue(string);
    Expression *interpret(string expression);
    bool isGreater(char, char);
    virtual ~Interpreter();

};

#endif //FLYPROJECT_CALC_H
