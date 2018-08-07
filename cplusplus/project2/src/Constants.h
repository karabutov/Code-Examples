#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include <string>

// priority of operation
const static int ONE_MINUS_PRIORITY = 60;
const static int ONE_PLUS_PRIORITY = 60;
const static int BRACKET_PRIORITY = 60;
const static int ONE_NOT_PRIORITY = 25;
const static int TWO_MINUS_PRIORITY = 40;
const static int TWO_PLUS_PRIORITY = 40;
const static int TWO_MULTI_PRIORITY = 50;
const static int TWO_DIVIDE_PRIORITY = 50;
const static int TWO_MORE_PRIORITY = 30;
const static int TWO_LESS_PRIORITY = 30;
const static int TWO_EQU_PRIORITY = 30;
const static int TWO_AND_PRIORITY = 20;
const static int TWO_OR_PRIORITY = 15;
const static int NUMBER_PRIORITY = 70;
const static int CBRACKET_PRIORITY = 9999999;
const static int END_OF_STRING_PRIORITY = 9999999;

const static int ONE_MINUS_INDEX = 1;
const static int ONE_PLUS_INDEX = 2;
const static int OBRACKET_INDEX = 3;
const static int TWO_MINUS_INDEX = 4;
const static int TWO_PLUS_INDEX = 5;
const static int TWO_MULTI_INDEX = 6;
const static int TWO_DIVIDE_INDEX = 7;
const static int TWO_MORE_INDEX = 8;
const static int TWO_EQU_INDEX = 9;
const static int TWO_LESS_INDEX = 10;
const static int TWO_AND_INDEX = 11;
const static int TWO_OR_INDEX = 12;
const static int ONE_NOT_INDEX = 13;
const static int INTEGER_INDEX = 1000;
const static int DOUBLE_INDEX = 1010;
const static int FIELD_INDEX = 1020;
const static int VARIABLE_INDEX = 1030;
const static int CBRACKET_INDEX = 3000;
const static int FUNCTION_INDEX = 4000;

struct PrototypeInfo {
    std::string value;
    int fraction;
};

#endif /* CONSTANTS_H_ */
