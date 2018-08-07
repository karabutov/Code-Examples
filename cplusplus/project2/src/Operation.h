#ifndef OPERATION_H_
#define OPERATION_H_

#include <string>

using namespace std;

class Operation {
public:

    int index;

    int nexts[10];

    int priority;

    int memfree;

    Operation(int ind, int p);
    virtual ~Operation();
    virtual double dexecute();
    virtual void accumulate();
    virtual int iexecute();
    virtual int bexecute();
    virtual void freeMemory();
    virtual int isfloat();
    virtual int isint();
    virtual int isboolean();
    virtual string asstring();
    virtual string stringdetails();
    virtual int getType();
    int validNext(int nextIndex);
};

#endif /* OPERATION_H_ */
