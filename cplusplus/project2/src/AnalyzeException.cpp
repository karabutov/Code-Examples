#include "AnalyzeException.h"

using namespace std;

AnalyzeException::AnalyzeException(const char* text1) {
    std::stringstream sstm;
    sstm << "Application ERROR. " << text1;
    message = sstm.str();
}

AnalyzeException::AnalyzeException(const char* text1, string& text2) {
    std::stringstream sstm;
    sstm << "Application ERROR. " << text1 << text2;
    message = sstm.str();
}

AnalyzeException::AnalyzeException(const char* text, int n) {
    std::stringstream sstm;
    sstm << "Application ERROR. " << text << n;
    message = sstm.str();
}
const char* AnalyzeException::what() {
    return message.c_str();
}


AnalyzeException::AnalyzeException(const char* text, StringStream &stream) {
    stringstream sstm;
    sstm << "Lexic ERROR. " << text;
    if (stream.eos()) {
        sstm << ". End of string.";
    } else {
        sstm << ". Position: " << stream.position() << ". Current symbol: '" << stream.current() << "'";
    }
    message = sstm.str();
}

AnalyzeException::AnalyzeException(const char* text, TokenProtoype& token, int eoi, Operation* op) {
    std::stringstream sstm;
    sstm << "Syntax ERROR. " << text;
    if (eoi) {
        sstm << ". End of statement.";
    } else {
        sstm << ". Token: " << token.value << ". Position: " << token.position << ".";
    }
    if (op) {
        sstm << " Statement: " + op->asstring();
    }
    message = sstm.str();
}
