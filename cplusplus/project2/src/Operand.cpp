#include "Operand.h"
Operand::Operand(int ind, int t) :
        Operation(ind, NUMBER_PRIORITY) {
    optype = t;
    // что может идти после операнда
    // это: числа, переменные
    nexts[0] = TWO_MINUS_INDEX;
    nexts[1] = TWO_PLUS_INDEX;
    nexts[2] = TWO_MULTI_INDEX;
    nexts[3] = TWO_DIVIDE_INDEX;
    nexts[4] = CBRACKET_INDEX;
    nexts[5] = -1;
}

int Operand::getType() { // 0 - double, 1 - integer, 2 - boolean
    return optype;
}

IntegerOperand::IntegerOperand(int ind) :
        Operand(ind, 1) {
    value = 0;
}

string IntegerOperand::asstring() {
    std::stringstream sstm;
    sstm << value;
    return sstm.str();
}

string IntegerOperand::stringdetails() {
    return "i[" + asstring() + "]";
}

void IntegerOperand::parse(string& s) {
    value = atoi(s.c_str());
}

double IntegerOperand::dexecute() {
    return value;
}
int IntegerOperand::iexecute() {
    return value;
}

DoubleOperand::DoubleOperand(int ind) :
        Operand(ind, 0) {
    value = 0;
}
string DoubleOperand::asstring() {
    std::stringstream sstm;
    sstm << value;
    return sstm.str();
}

string DoubleOperand::stringdetails() {
    return "d[" + asstring() + "]";
}

void DoubleOperand::parse(string& s) {
    value = atof(s.c_str());
}

double DoubleOperand::dexecute() {
    return value;
}

int DoubleOperand::iexecute() {
    return value;
}

Field::Field() :
        Operand(FIELD_INDEX, 0) {
    readyvalue = 0;
    ivalue = 0;
    dvalue = 0;
    memfree = 0;
    aggrkey = 0;
}

string Field::asstring() {
    std::stringstream sstm;
    sstm << "in:" << name << "'" << svalue << "'";
    return sstm.str();
}

string Field::stringdetails() {
    return "f[" + asstring() + "]";
}

void Field::setSValue(string s) {
    svalue = s;
    readyvalue = 0;
    if (svalue.find('.') == string::npos) {
        optype = 1;
    } else {
        optype = 0;
    }
}

string Field::getSValue() {
    return svalue;
}

void Field::parse(string& s) {
    if (optype) {
        ivalue = atoi(s.c_str());
        dvalue = ivalue;
    } else {
        dvalue = atof(s.c_str());
        ivalue = dvalue;
    }
    readyvalue = 1;
}

double Field::dexecute() {
    if (!readyvalue) {
        parse(svalue);
    }
    return dvalue;
}
int Field::iexecute() {
    if (!readyvalue) {
        parse(svalue);
    }
    return ivalue;
}

Variable::Variable() :
        Operand(VARIABLE_INDEX, 0) {
    oper = 0;
}

void Variable::freeMemory() {
    if (oper) {
        if (oper->memfree) {
            oper->freeMemory();
            free(oper);
            oper = 0;
        }
    }
}

string Variable::asstring() {
    std::stringstream sstm;
    sstm << "v:" << name << "=" << (oper ? oper->asstring() : "???");
    return sstm.str();
}

string Variable::stringdetails() {
    return "v[" + asstring() + "]";
}

int Variable::getType() { // 0 - double, 1 - integer, 2 - boolean
    return oper->getType();
}

void Variable::accumulate() {
    oper->accumulate();
}

double Variable::dexecute() {
    return oper->dexecute();
}

int Variable::iexecute() {
    return oper->iexecute();
}

Function::Function() :
        Variable() {
}

string Function::asstring() {
    std::stringstream sstm;
    sstm << "f:" << name << "(" << (oper ? oper->asstring() : "???");
    return sstm.str();
}

string Function::stringdetails() {
    return "f([" + asstring() + "]";
}

void Function::accumulate() {
    oper->accumulate();
}

void Function::freeMemory() {
    bufferoper.freeMemory();
    Variable::freeMemory();
}

SqrtFunction::SqrtFunction() :
        Function() {
    name = "sqrt";
}

int SqrtFunction::getType() {
    return 0;
}

double SqrtFunction::dexecute() {
    return sqrt(oper->dexecute());
}

int SqrtFunction::iexecute() {
    return dexecute();
}

AvgFunction::AvgFunction() :
        Function() {
    name = "avg";
    count = 0;
    summa = 0;
}

int AvgFunction::getType() {
    return 0;
}

void AvgFunction::accumulate() {
    count++;
    summa += oper->dexecute();
}

double AvgFunction::dexecute() {
    double d = summa / count;
    count = 0;
    summa = 0;
    return d;
}

int AvgFunction::iexecute() {
    return dexecute();
}

MaxFunction::MaxFunction() :
        Function() {
    name = "min";
    initvars();
}

void MaxFunction::initvars() {
    count = 0;
    icurrent = 0;
    dcurrent = 0;
}

void MaxFunction::accumulate() {
    if (count == 0) {
        dcurrent = oper->dexecute();
        icurrent = oper->iexecute();
    } else {
        double d = oper->dexecute();
        if (d > dcurrent) {
            dcurrent = d;
        }
        int n = oper->iexecute();
        if (n > icurrent) {
            icurrent = n;
        }
    }
    count++;
}

double MaxFunction::dexecute() {
    double res = dcurrent;
    initvars();
    return res;
}

int MaxFunction::iexecute() {
    int res = icurrent;
    initvars();
    return res;
}

MinFunction::MinFunction() :
        Function() {
    name = "min";
    initvars();
}

void MinFunction::initvars() {
    count = 0;
    icurrent = 0;
    dcurrent = 0;
}

void MinFunction::accumulate() {
    if (count == 0) {
        dcurrent = oper->dexecute();
        icurrent = oper->iexecute();
    } else {
        double d = oper->dexecute();
        if (d < dcurrent) {
            dcurrent = d;
        }
        int n = oper->iexecute();
        if (n < icurrent) {
            icurrent = n;
        }
    }
    count++;
}

double MinFunction::dexecute() {
    double res = dcurrent;
    initvars();
    return res;
}

int MinFunction::iexecute() {
    int res = icurrent;
    initvars();
    return res;
}
