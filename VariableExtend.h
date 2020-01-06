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
    double _value = 0;
    string _sim;
    InOrOut _in;
    bool _toSend = false;
public:
    //getters and setters
    VariableExtend( string name, double value, string sim, InOrOut in) : _name(name), _value(value), _sim(sim), _in(in){};
    VariableExtend() = default;
    void setValue(double value);
    void setName(string name);
    void setSim(string sim);
    void setIn(InOrOut in);
    void setToSend(bool toSend);
    double getValue();
    string getName();
    string getSim();
    InOrOut getIn();
    bool  getToSend();

    ~VariableExtend(){};
};


#endif //FLYPROJECT_VARIABLE_H
