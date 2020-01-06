//
// Created by ziv on 24/12/2019.
//

#include "VariableExtend.h"

InOrOut VariableExtend::getIn() { return _in;}
string VariableExtend::getName() {return _name;}
string VariableExtend::getSim() {return _sim;}
double VariableExtend::getValue() {return _value;}
bool VariableExtend::getToSend() {return _toSend;}
void VariableExtend::setValue(double value) {_value = value;}
void VariableExtend::setName(string name){_name = name;}
void VariableExtend::setSim(string sim){_sim = sim;}
void VariableExtend::setIn(InOrOut in){_in = in;}
void VariableExtend::setToSend(bool toSend) {_toSend = toSend;}