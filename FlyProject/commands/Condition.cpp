//
// Created by liza on 05/01/2020.
//

#include "Condition.h"

// check if left (sign) right is an true condition
bool Condition::isTrue(double left, string sign, double right) {
    if (sign.compare("<") == 0){
        return left < right;
    }
    if (sign.compare(">") == 0){
        return left > right;
    }
    if (sign.compare("<=") == 0){
        return left <= right;
    }
    if (sign.compare(">=") == 0){
        return left >= right;
    }
    if (sign.compare("==") == 0){
        return left == right;
    }
    if (sign.compare("!=") == 0){
        return left != right;
    }
    return false;
}