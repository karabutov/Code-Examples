#include "Operation.h"

    Operation::Operation(int ind, int p) {
        index = ind;
        priority = p;
        memfree = 1;
    }

    Operation::~Operation() {
        freeMemory();
    }

    double Operation::dexecute() {
        return 0;
    }

    void Operation::accumulate() {

    }

    int Operation::iexecute() {
        return 0;
    }

    int Operation::bexecute() {
        return isfloat() ? dexecute() : iexecute();
    }

    void Operation::freeMemory() {
    }

    int Operation::isfloat() {
        return getType() == 0 ? 1 : 0;
    }

    int Operation::isint() {
        return getType() == 1 ? 1 : 0;
    }

    int Operation::isboolean() {
        return getType() == 2 ? 1 : 0;
    }

    string Operation::asstring() {
        return "???";
    }

    string Operation::stringdetails() {
        return "???";
    }

    int Operation::getType() {        // 0 - double, 1 - integer, 2 - boolean
        return 1;
    }

    int Operation::validNext(int nextIndex) {
        int ns = 0;
        while (nexts[ns] >= 0) {
            if (nexts[ns] == nextIndex) {
                return 1;
            }
            ns++;
        }
        return 0;
    }
