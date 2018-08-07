#include "CsvDataReader.h"

using namespace std;
CsvDataReader::CsvDataReader(char s) {
    sep = s;
    headerLexic.isword = 1;
    headerLexic.anyword = 1;
    headerLexic.sep = sep;
    valueLexic.sep = sep;
}

string& CsvDataReader::nextLine() {
    getline(ifile, buffer);
    return buffer;
}

int CsvDataReader::eof() {
    return ifile.eof();
}

int CsvDataReader::init(string& fn) {
    ifile.open(fn.c_str());
    if (!ifile.is_open()) {
        cout << "Unable to open file: " << fn;
        return 0;
    }
    return 1;
}

int CsvDataReader::parseColumns(vector<TokenProtoype> &infields) {
    if (eof()) {
        return 0;
    }
    if (!headerLexic.analyze(nextLine())) {
        return 0;
    }
    infields = headerLexic.tokenlist;
    return 1;
}

int CsvDataReader::parseValues(vector<TokenProtoype> &infields) {
    if (eof()) {
        return 0;
    }
    if (!valueLexic.analyze(nextLine())) {
        return 0;
    }
    infields = valueLexic.tokenlist;
    return 1;
}

void CsvDataReader::close() {
    headerLexic.freememory();
    valueLexic.freememory();
    if (ifile.is_open()) {
        ifile.close();
    }
}

CsvDataReader::~CsvDataReader() {
    close();
}
