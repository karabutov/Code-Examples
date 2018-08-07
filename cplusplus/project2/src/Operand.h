#ifndef OPERAND_H_
#define OPERAND_H_

#include <string>
#include <cstring>
#include <iostream>     // std::cout
#include <sstream>      // std::stringstream, std::stringbuf
#include <stdlib.h>
#include <cmath>

#include "Constants.h"
#include "Operation.h"
#include "OneOperation.h"

class Operand: public Operation {
public:

    int optype;	// 0 - double, 1 - integer, 2 - boolean

    Operand(int ind, int t);
    int getType();	// 0 - double, 1 - integer, 2 - boolean

};

class IntegerOperand: public Operand {
public:

    IntegerOperand(int ind);
    string asstring();
    string stringdetails();
    void parse(string& s);
    double dexecute();
    int iexecute();
protected:

    int value;

};

class DoubleOperand: public Operand {
public:
    double value;

    DoubleOperand(int ind);
    string asstring();
    string stringdetails();
    void parse(string& s);
    double dexecute();
    int iexecute();
};

class Field: public Operand {
public:

    string name;

    int aggrkey;

    Field();
    string asstring();
    string stringdetails();
    void setSValue(string s);
    string getSValue();
    void parse(string& s);
    double dexecute();
    int iexecute();
private:
    int readyvalue;
    string svalue;
    int ivalue;
    double dvalue;
};

class Variable: public Operand {
public:

    Operation* oper;

    string name;

    Variable();
    void freeMemory();
    string asstring();
    string stringdetails();
    int getType();
    virtual void accumulate();
    double dexecute();
    int iexecute();
};

class Function: public Variable {
public:

    OneOperation bufferoper;

    Function();
    string asstring();
    string stringdetails();
    virtual void accumulate();
    void freeMemory();
};

class SqrtFunction: public Function {
public:

    SqrtFunction();
    int getType();
    double dexecute();
    int iexecute();
};

class AvgFunction: public Function {
public:

    unsigned int count;

    double summa;

    AvgFunction();
    int getType();
    virtual void accumulate();
    double dexecute();
    int iexecute();
};

class MaxFunction: public Function {
public:

    unsigned int count;

    int icurrent;
    double dcurrent;

    MaxFunction();
    void initvars();
    virtual void accumulate();
    double dexecute();
    int iexecute();
};

class MinFunction: public Function {
public:

    unsigned int count;

    int icurrent;
    double dcurrent;

    MinFunction();
    void initvars();
    virtual void accumulate();
    double dexecute();
    int iexecute();
};

#endif /* OPERAND_H_ */
