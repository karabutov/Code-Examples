#ifndef SYNTAXAANLYZER_H_
#define SYNTAXAANLYZER_H_

#include <string>
#include <vector>
#include <iostream>     // std::cout

#include "AnalyzeException.h"
#include "VariableTable.h"
#include "Operand.h"
#include "TwoOperation.h"
#include "TokenProtoype.h"

using namespace std;

class SyntaxAnalyzer {
public:

    LexicalAnalyzer* lexic;
    VariableTable* variableTable;
    OneOperation root;

    SyntaxAnalyzer(LexicalAnalyzer* lex, VariableTable* vt);
    Operation* analyse();
    void analyse(int isbracket, OneOperation *parent);
    Operation* analyseOperation(OneOperation *parent);
    TokenProtoype& nextToken(int operNumber, OneOperation *parent);

private:
    Operation* getOpertion(TokenProtoype& token, int n);
};

#endif
