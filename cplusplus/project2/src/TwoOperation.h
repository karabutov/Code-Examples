#include <string>

#ifndef TWOOPERATION_H_
#define TWOOPERATION_H_

#include "OneOperation.h"
#include "AnalyzeException.h"

class TwoOperation: public OneOperation {
public:

    Operation *oper2;

    TwoOperation(string os, int ind, int p);
    void freeMemory();
    void accumulate();
    void setOperation2(Operation *o);
    string asstring();
    string stringdetails();
    int getType();
};

class TwoPlus: public TwoOperation {
public:

    TwoPlus(int ind);
    double dexecute();
    int iexecute();
};

class TwoMinus: public TwoOperation {
public:
    TwoMinus(int ind);
    double dexecute();
    int iexecute();
};

class TwoMulti: public TwoOperation {
public:
    TwoMulti(int ind);
    double dexecute();
    int iexecute();
};

class TwoDivide: public TwoOperation {
public:
    TwoDivide(int ind);
    double dexecute();
    int iexecute();
};

class TwoMore: public TwoOperation {
public:
    TwoMore(int ind);
    int getType();
    double dexecute();
    int iexecute();
    int bexecute();
};

class TwoLess: public TwoOperation {
public:
    TwoLess(int ind);
    int getType();
    double dexecute();
    int iexecute();
    int bexecute();
};

class TwoEqu: public TwoOperation {
public:
    TwoEqu(int ind);
    int getType();
    double dexecute();
    int iexecute();
    int bexecute();
};

class TwoAnd: public TwoOperation {
public:
    TwoAnd(int ind);
    int getType();
    double dexecute();
    int iexecute();
    int bexecute();
};

class TwoOr: public TwoOperation {
public:
    TwoOr(int ind);
    int getType();
    double dexecute();
    int iexecute();
    int bexecute();
};

#endif /* TWOOPERATION_H_ */
