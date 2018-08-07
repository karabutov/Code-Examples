#ifndef MAPEXEC_H_
#define MAPEXEC_H_

#include <iostream>
#include <fstream>
#include <exception>
#include <string>
#include <stdlib.h>
#include <cstring>
#include <vector>
#include "SyntaxAnalyzer.h"
#include "Parser.h"

using namespace std;

class MapExec {
public:

    VariableTable* variableTable;
    Variable** variables;
    int numvariables;
    Operation* filter;
    vector<TokenProtoype> columnNameTokens;
    LexicalAnalyzer columnNameLexic;
    LexicalAnalyzer* selectLexic;
    char sep;
    ofstream ofile;

    MapExec(char c, LexicalAnalyzer* selL, VariableTable* vt);
    int initOutputFile(string& ofname);
    int parseSelect(string& str);
    int initOutputVariables(string& str);
    int initFilter(string sfilter);
    int checkFilter();
    int output();
    virtual ~MapExec();
    virtual void freememory();
};

class ReduceExec: public MapExec {
public:


    const static int FIRST_LINE = 1;
    const static int MIDDLE_LINE = 2;
    const static int LAST_LINE = 3;

    Field** keys;
    Field** keyvalues;
    int numkeys;

    ReduceExec(char c, LexicalAnalyzer* selL, VariableTable* vt);
    int initKeyVariables(string& s);

    int output(int pos);
    int accumulate();
    int compareKeys(int move);
    void freememory();

};

#endif /* MAPEXEC_H_ */
