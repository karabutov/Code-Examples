#ifndef ONEOPERATION_H_
#define ONEOPERATION_H_

#include "stdlib.h"
#include "Constants.h"
#include "Operation.h"

class OneOperation: public Operation {
public:
    Operation *oper1;
    string operSign;

    OneOperation();
    void setOperation(Operation *o);
    void freeMemory();
    void accumulate();
    int getType();
    string asstring();
protected:
    OneOperation(string os, int ind, int p);
};

class OneMinus: public OneOperation {
public:
    OneMinus(int ind);
    string stringdetails();
    double dexecute();
    int iexecute();
};

class OnePlus: public OneOperation {
public:
    OnePlus(int ind);
    string stringdetails();
    double dexecute();
    int iexecute();
};

class Bracket: public OneOperation {
public:
    Bracket(int ind);
    string asstring();
    string stringdetails();
    double dexecute();
    int iexecute();
};

class OneNot: public OneOperation {
public:

    OneNot(int ind);
    string stringdetails();
    int getType();
    double dexecute();
    int iexecute();
    int bexecute();
};

#endif /* ONEOPERATION_H_ */
