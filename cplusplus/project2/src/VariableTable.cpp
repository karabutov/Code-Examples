#include "VariableTable.h"

VariableTable::VariableTable(CsvDataReader* r) {
    reader = r;
    fields = 0;
    numfields = 0;
}

int VariableTable::initInputFields() {
    if (!reader->parseColumns(columnTokens)) {
        return 0;
    }
    numfields = columnTokens.size();
    fields = new Field*[numfields];
    vector<TokenProtoype>::iterator tokenit;
    int num = 0;
    for (tokenit = columnTokens.begin(); tokenit < columnTokens.end(); tokenit++) {
        TokenProtoype tp = *tokenit;
        Field* f = new Field();
        f->name = tp.value;
        fields[num] = f;
        num++;
    }
    return 1;
}

int VariableTable::setValues() {
    if (reader->eof()) {
        return 0;
    }
    vector<TokenProtoype> columnTokens;
    if (!reader->parseValues(columnTokens)) {
        return 0;
    }
    vector<TokenProtoype>::iterator tokenit;
    int num = 0;
    for (tokenit = columnTokens.begin(); tokenit < columnTokens.end(); tokenit++) {
        TokenProtoype tp = *tokenit;
        if (tp.ioper1 == ONE_MINUS_INDEX || tp.ioper1 == ONE_PLUS_INDEX) {
            string sign = tp.value;
            tokenit++;
            tp = *tokenit;
            tp.value = sign + tp.value;
        }
        if (num >= numfields) {
            cout << "\n ERROR. DB row data parsing. Too many columns in data file. Column: " << (num + 1) << "." << tp.value << endl;
            return 0;
        }
        setFieldValue(num, tp.value);
        num++;
    }
    return 1;
}

Field* VariableTable::getField(string name) {
    for (int ns = 0; ns < numfields; ++ns) {
        if (0 == fields[ns]->name.compare(name)) {
            return fields[ns];
        }
    }
    return 0;
}

void VariableTable::setFieldValue(int ns, string value) {
    fields[ns]->setSValue(value);
}

VariableTable::~VariableTable() {
    freememory();
}

void VariableTable::freememory() {
    if (fields) {
        for (int ns = 0; ns < numfields; ++ns) {
            if (fields[ns]) {
                delete fields[ns];
                fields[ns] = 0;
            }
        }
        delete fields;
        fields = 0;
    }
}
