#ifndef ANALYZEEXCEPTION_H_
#define ANALYZEEXCEPTION_H_

#include <string>
#include <iostream>     // std::cout
#include <sstream>      // std::stringstream, std::stringbuf
#include "StringStream.h"
#include "Operation.h"
#include "TokenProtoype.h"

using namespace std;

class AnalyzeException {
public:
    string message;
    AnalyzeException(const char* text1);

    AnalyzeException(const char* text1, string& text2);

    AnalyzeException(const char* text, int n);
    AnalyzeException(const char* text, StringStream &stream);
    AnalyzeException(const char* text, TokenProtoype& token, int eoi, Operation* op);
    const char* what();
};

#endif /* ANALYZEEXCEPTION_H_ */

