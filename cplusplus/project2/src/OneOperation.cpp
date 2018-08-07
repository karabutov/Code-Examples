#include "OneOperation.h"

OneOperation::OneOperation() :
        Operation(0, 0) {
    operSign = "";
    oper1 = 0;
    // что может стоять в начале выражения
    nexts[0] = ONE_MINUS_INDEX;
    nexts[1] = ONE_PLUS_INDEX;
    nexts[2] = OBRACKET_INDEX;
    nexts[3] = INTEGER_INDEX;
    nexts[4] = DOUBLE_INDEX;
    nexts[5] = ONE_NOT_INDEX;
    nexts[6] = VARIABLE_INDEX;
    nexts[7] = FUNCTION_INDEX;
    nexts[8] = -1;
}

void OneOperation::setOperation(Operation *o) {
    oper1 = o;
}

void OneOperation::freeMemory() {
    if (oper1) {
        if (oper1->memfree) {
            oper1->freeMemory();
            free(oper1);
            oper1 = 0;
        }
    }
}

void OneOperation::accumulate() {
    oper1->accumulate();
}

int OneOperation::getType() { // 0 - double, 1 - integer, 2 - boolean
    return oper1->getType();
}

string OneOperation::asstring() {
    return operSign + (oper1 ? oper1->asstring() : "???");
}

OneOperation::OneOperation(string os, int ind, int p) :
        Operation(ind, p) {
    operSign = os;
    oper1 = 0;
    // что может стоять после унарной операции.
    // если здесь изменить количество допустимых операций,
    // то надо поправить индексы в конструкторе для скобки: Bracket
    nexts[0] = OBRACKET_INDEX;
    nexts[1] = INTEGER_INDEX;
    nexts[2] = DOUBLE_INDEX;
    nexts[3] = ONE_NOT_INDEX;
    nexts[4] = VARIABLE_INDEX;
    nexts[5] = FUNCTION_INDEX;
    nexts[6] = -1;
}

OneMinus::OneMinus(int ind) :
        OneOperation("-", ind, ONE_MINUS_PRIORITY) {
}

string OneMinus::stringdetails() {
    return "'-[" + asstring() + "]";
}

double OneMinus::dexecute() {
    return -oper1->dexecute();
}

int OneMinus::iexecute() {
    return -oper1->iexecute();
}

OnePlus::OnePlus(int ind) :
        OneOperation("+", ind, ONE_PLUS_PRIORITY) {
}

string OnePlus::stringdetails() {
    return "'+[" + asstring() + "]";
}

double OnePlus::dexecute() {
    return oper1->dexecute();
}
int OnePlus::iexecute() {
    return oper1->iexecute();
}

Bracket::Bracket(int ind) :
        OneOperation("(", ind, BRACKET_PRIORITY) {
    nexts[6] = ONE_MINUS_INDEX;
    nexts[7] = ONE_PLUS_INDEX;
    nexts[8] = -1;
}

string Bracket::asstring() {
    return "(" + (oper1 ? oper1->asstring() : "???") + ")";
}

string Bracket::stringdetails() {
    return "'([" + asstring() + "]";
}

double Bracket::dexecute() {
    return oper1->dexecute();
}
int Bracket::iexecute() {
    return oper1->iexecute();
}

OneNot::OneNot(int ind) :
        OneOperation("not ", ind, ONE_NOT_PRIORITY) {
}

string OneNot::stringdetails() {
    return "'not[" + asstring() + "]";
}

int OneNot::getType() { // 0 - double, 1 - integer, 2 - boolean
    return 2;
}

double OneNot::dexecute() {
    return not (oper1->dexecute());
}

int OneNot::iexecute() {
    return not (oper1->iexecute());
}

int OneNot::bexecute() {
    int ot = oper1->getType();
    switch (ot) {
    case 0:
        return not oper1->dexecute();
    case 1:
        return not oper1->iexecute();
    default:
        return not oper1->bexecute();
    }
}
