#ifndef VARIABLETABLE_H_
#define VARIABLETABLE_H_

#include <string>
#include <vector>
#include "TokenProtoype.h"
#include "CsvDataReader.h"
#include "Operand.h"

using namespace std;

class VariableTable {
public:

    Field** fields;
    int numfields;
    CsvDataReader* reader;
    vector<TokenProtoype> columnTokens;

    VariableTable(CsvDataReader* r);
    int initInputFields();
    int setValues();
    Field* getField(string name);
    void setFieldValue(int ns, string value);
    virtual ~VariableTable();
    void freememory();
};

#endif /* VARIABLETABLE_H_ */
