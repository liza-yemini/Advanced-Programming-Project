//
// Created by liza on 24/12/2019.
//
// updated by ziv on 05/01/2020.
#include <fstream>
#include "Lexer.h"


void Push(string com, vector<string>* command) {
    if (com != "") {
        command->push_back(com);
    }

}
vector<string> Lexer::Interpet(string path) {
    int pertFlag = 0;
    ifstream fp;
    fp.open(path);
    if( !fp.is_open()) {
        printf("cant  read");
        throw "error";
    }
    vector<string> commands;

    char c;
    string com = "";
    while(fp.get(c)) {
        //if space or tab skip
        if((c == ' ' || c == '\t')){
            // if in string
            if(com.front() == '"'){
                com += c;
            }
            continue;
        }
        //if <=, >=, ==, !=
        if ((com == "<" || com == ">" || com == "=" || com == "!") && c == '=' ) {
            com +=c;
            Push(com,&commands);
            com = "";
            continue;
        }
        // var, while, if
        if (com == "var" || com == "while" || com == "if") {
            Push(com,&commands);
            com = c;
            continue;

        }
        // if <- or ->
        if ((com == "<" && c == '-') || (com == "-" && c == '>')) {
            com +=c;
            Push(com,&commands);
            com = "";
            continue;
        }
        // if <, >
        if ((c != '=') && (com == "<" ||  com == ">"  || com == "!") ) {
            Push(com, &commands);
            com = c;
            continue;
        }
        // if = ,< ,>, -, ! and not in pretheses()
        if ((c == '=' || c == '<' || c == '-' || c == '>' || c == '!') && pertFlag == 0) {
            Push(com, &commands);
            com = c;
            continue;
        }
        //if = alone
        if (com == "=" && ( c != '=')) {
            Push(com,&commands);
            getline(fp,com);
            Push(c + com,&commands);
            com = "";
            continue;
        }
        // for (,) , , , \n, { and all the other chars
        else {
            switch(c){

                case '(': pertFlag = 1;
                    Push(com,&commands);
                    com = "";
                    break;
                case ')': pertFlag = 0;
                    Push(com,&commands);
                    com = "";
                    break;
                case ',': Push(com,&commands);
                    com = "";
                    break;
                case '\n': Push(com,&commands);
                    com = "";
                    break;
                case '{':
                    Push(com,&commands);
                    Push("{",&commands);
                    com = "";
                    break;
                default:

                    com += c;
                    break;
            }
        }

    }
    // add the last string to the vector
    if (com != "") {
        Push(com,&commands);
    }
    fp.close();

    //return the vector
    return commands;
}
