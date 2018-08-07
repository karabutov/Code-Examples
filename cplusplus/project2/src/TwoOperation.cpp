#include "TwoOperation.h"

TwoOperation::TwoOperation(string os, int ind, int p) :
        OneOperation(os, ind, p) {
    oper2 = 0;
    // что идет после двух операндных операций
    // если здесь изменить количество допустимых операций,
    // то надо поправить индексы в конструкторах
    // операций сравнения ><= и логических not and or
    nexts[0] = OBRACKET_INDEX;
    nexts[1] = INTEGER_INDEX;
    nexts[2] = DOUBLE_INDEX;
    nexts[3] = VARIABLE_INDEX;
    nexts[4] = FUNCTION_INDEX;
    nexts[5] = -1;
}

void TwoOperation::freeMemory() {
    if (oper1) {
        if (oper1->memfree) {
            oper1->freeMemory();
            free(oper1);
            oper1 = 0;
        }
        if (oper2) {
            if (oper2->memfree) {
                oper2->freeMemory();
                free(oper2);
                oper2 = 0;
            }
        }
    }
}

void TwoOperation::accumulate() {
    oper1->accumulate();
    oper2->accumulate();
}

void TwoOperation::setOperation2(Operation *o) {
    oper2 = o;
}

string TwoOperation::asstring() {
    return (oper1 ? oper1->asstring() : "???") + operSign + (oper2 ? oper2->asstring() : "???");
}

string TwoOperation::stringdetails() {
    return "\"" + operSign + "[" + asstring() + "]";
}

int TwoOperation::getType() { // 0 - double, 1 - integer, 2 - boolean
    return oper1->getType() == 2 || oper2->getType() == 2 ? 2 : oper1->getType() == 0 || oper2->getType() == 0 ? 0 : 1;
}

TwoPlus::TwoPlus(int ind) :
        TwoOperation("+", ind, TWO_PLUS_PRIORITY) {
}

double TwoPlus::dexecute() {
    return oper1->dexecute() + oper2->dexecute();
}

int TwoPlus::iexecute() {
    return oper1->iexecute() + oper2->iexecute();
}

TwoMinus::TwoMinus(int ind) :
        TwoOperation("-", ind, TWO_MINUS_PRIORITY) {
}

double TwoMinus::dexecute() {
    return oper1->dexecute() - oper2->dexecute();
}

int TwoMinus::iexecute() {
    return oper1->iexecute() - oper2->iexecute();
}

TwoMulti::TwoMulti(int ind) :
        TwoOperation("*", ind, TWO_MULTI_PRIORITY) {
}

double TwoMulti::dexecute() {
    return oper1->dexecute() * oper2->dexecute();
}

int TwoMulti::iexecute() {
    return oper1->iexecute() * oper2->iexecute();
}

TwoDivide::TwoDivide(int ind) :
        TwoOperation("/", ind, TWO_DIVIDE_PRIORITY) {
}

double TwoDivide::dexecute() {
    double d = oper2->dexecute();
    if (d == 0) {
        throw AnalyzeException("Division by 0!!!");
    }
    return oper1->dexecute() / d;
}

int TwoDivide::iexecute() {
    int d = oper2->iexecute();
    if (d == 0) {
        throw AnalyzeException("Division by 0!!!");
    }
    return oper1->iexecute() / d;
}
TwoMore::TwoMore(int ind) :
        TwoOperation(">", ind, TWO_MORE_PRIORITY) {
    nexts[5] = ONE_NOT_INDEX;
    nexts[6] = ONE_MINUS_INDEX;
    nexts[7] = ONE_PLUS_INDEX;
    nexts[8] = -1;
}

int TwoMore::getType() { // 0 - double, 1 - integer, 2 - boolean
    return 2;
}

double TwoMore::dexecute() {
    return oper1->dexecute() > oper2->dexecute();
}

int TwoMore::iexecute() {
    return oper1->iexecute() > oper2->iexecute();
}

int TwoMore::bexecute() {
    int ot = TwoOperation::getType();
    switch (ot) {
    case 0:
        return dexecute();
    case 1:
        return iexecute();
    default:
        return oper1->bexecute() > oper2->bexecute();
    }
}

TwoLess::TwoLess(int ind) :
        TwoOperation("<", ind, TWO_LESS_PRIORITY) {
    nexts[5] = ONE_NOT_INDEX;
    nexts[6] = ONE_MINUS_INDEX;
    nexts[7] = ONE_PLUS_INDEX;
    nexts[8] = -1;
}

int TwoLess::getType() { // 0 - double, 1 - integer, 2 - boolean
    return 2;
}

double TwoLess::dexecute() {
    return oper1->dexecute() < oper2->dexecute();
}

int TwoLess::iexecute() {
    return oper1->iexecute() < oper2->iexecute();
}

int TwoLess::bexecute() {
    int ot = TwoOperation::getType();
    switch (ot) {
    case 0:
        return dexecute();
    case 1:
        return iexecute();
    default:
        return oper1->bexecute() < oper2->bexecute();
    }
}

TwoEqu::TwoEqu(int ind) :
        TwoOperation("=", ind, TWO_EQU_PRIORITY) {
    nexts[5] = ONE_NOT_INDEX;
    nexts[6] = ONE_MINUS_INDEX;
    nexts[7] = ONE_PLUS_INDEX;
    nexts[8] = -1;
}

int TwoEqu::getType() { // 0 - double, 1 - integer, 2 - boolean
    return 2;
}

double TwoEqu::dexecute() {
    return oper1->dexecute() == oper2->dexecute();
}

int TwoEqu::iexecute() {
    return oper1->iexecute() == oper2->iexecute();
}

int TwoEqu::bexecute() {
    int ot = TwoOperation::getType();
    switch (ot) {
    case 0:
        return dexecute();
    case 1:
        return iexecute();
    default:
        return oper1->bexecute() == oper2->bexecute();
    }
}
TwoAnd::TwoAnd(int ind) :
        TwoOperation(" and ", ind, TWO_AND_PRIORITY) {
    nexts[5] = ONE_NOT_INDEX;
    nexts[6] = ONE_MINUS_INDEX;
    nexts[7] = ONE_PLUS_INDEX;
    nexts[8] = -1;
}

int TwoAnd::getType() { // 0 - double, 1 - integer, 2 - boolean
    return 2;
}

double TwoAnd::dexecute() {
    return oper1->dexecute() && oper2->dexecute();
}

int TwoAnd::iexecute() {
    return oper1->iexecute() && oper2->iexecute();
}

int TwoAnd::bexecute() {
    int ot = TwoOperation::getType();
    switch (ot) {
    case 0:
        return dexecute();
    case 1:
        return iexecute();
    default:
        return oper1->bexecute() && oper2->bexecute();
    }
}
TwoOr::TwoOr(int ind) :
        TwoOperation(" or ", ind, TWO_OR_PRIORITY) {
    nexts[5] = ONE_NOT_INDEX;
    nexts[6] = ONE_MINUS_INDEX;
    nexts[7] = ONE_PLUS_INDEX;
    nexts[8] = -1;
}

int TwoOr::getType() { // 0 - double, 1 - integer, 2 - boolean
    return 2;
}

double TwoOr::dexecute() {
    return oper1->dexecute() || oper2->dexecute();
}

int TwoOr::iexecute() {
    return oper1->iexecute() || oper2->iexecute();
}

int TwoOr::bexecute() {
    int ot = TwoOperation::getType();
    switch (ot) {
    case 0:
        return dexecute();
    case 1:
        return iexecute();
    default:
        return oper1->bexecute() || oper2->bexecute();
    }
}
