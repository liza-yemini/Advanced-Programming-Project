//
// Created by liza on 24/12/2019.
//

#ifndef FLYPROJECT_EXPRESSION_H
#define FLYPROJECT_EXPRESSION_H

using namespace std;
/**
 * Expression Interface
 */
class Expression {

public:
    virtual double calculate() = 0;
    virtual ~Expression() {}
};

#endif //FLYPROJECT_EXPRESSION_H
