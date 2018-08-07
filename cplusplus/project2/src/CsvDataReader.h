#ifndef CSVDATAREADER_H_
#define CSVDATAREADER_H_
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "LexicalAnalyzer.h"
using namespace std;
class CsvDataReader {
public:
    ifstream ifile;
    string buffer;
    char sep;
    LexicalAnalyzer headerLexic;
    ValueAnalyzer valueLexic;

    CsvDataReader(char s);
    string& nextLine();
    int eof();
    int init(string& fn);
    int parseColumns(vector<TokenProtoype> &infields);
    int parseValues(vector<TokenProtoype> &infields);
    void close();
    virtual ~CsvDataReader();
};
#endif /* CSVDATAREADER_H_ */
