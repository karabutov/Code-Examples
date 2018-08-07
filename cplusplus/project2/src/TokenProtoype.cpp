#include "TokenProtoype.h"
//подготавливается лексическим анализатором
TokenProtoype::TokenProtoype() {
    value = "";
    symbol = 0;
    position = 0;
    ioper1 = 0;
    ioper2 = 0;
}

TokenProtoype::TokenProtoype(string s, int io1, int io2) {
    value = s;
    symbol = s.length() == 0 ? 0 : s.at(0);
    position = 0;
    ioper1 = io1;
    ioper2 = io2;
}

TokenProtoype::~TokenProtoype() {
}

void TokenProtoype::setValue(string s) {
    value = s;
    symbol = s.at(0);
}

string TokenProtoype::asstring() {
    return value;
}
