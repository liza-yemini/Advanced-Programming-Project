//
// Created by ziv on 24/12/2019.
//

#ifndef FLYPROJECT_VARIABLE_H
#define FLYPROJECT_VARIABLE_H

#include <string>
using namespace std;

enum InOrOut {in = 0,out = 1};
class VariableExtend {
    string _name;
    int _value = 0;
    string _sim;
    InOrOut _in;
    bool _toSend = false;
public:
    VariableExtend( string name, int value, string sim, InOrOut in) : _name(name), _value(value), _sim(sim), _in(in){};
    VariableExtend() = default;
    void setValue(int value);
    void setName(string name);
    void setSim(string sim);
    void setIn(InOrOut in);
    void setToSend(bool toSend);
    int getValue();
    string getName();
    string getSim();
    InOrOut getIn();
    bool  getToSend();

    ~VariableExtend(){};
};


#endif //FLYPROJECT_VARIABLE_H
