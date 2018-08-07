#include "MapExec.h"

using namespace std;


MapExec::MapExec(char c, LexicalAnalyzer* selL, VariableTable* vt) {
    selectLexic = selL;
    variableTable = vt;
    variables = 0;
    numvariables = 0;
    filter = 0;
    sep = c;
    columnNameLexic.isword = 1;
    columnNameLexic.anyword = 1;
    columnNameLexic.sep = sep;
}

int MapExec::initOutputFile(string& ofname) {
    ofile.open(ofname.c_str(), ios_base::trunc);
    if (!ofile.is_open()) {
        cout << "Unable to open file: " << ofile;
        return 0;
    }
    return 1;
}

int MapExec::parseSelect(string& str) { //лексический анализ select выражения, результат - вектор лексем
    vector<string> sels = parse(str, ',');
    vector<string>::iterator itsels;
    int num = 1;
    int fres = 1;
    try {
        for (itsels = sels.begin(); itsels < sels.end(); itsels++) {
            string sl = *itsels;
            string varname;
            string varoper;
            unsigned int aspos = sl.find(" as ");
            if (aspos == string::npos) {
            	// нет ' as ' поэтому только поле из файла данных
            	// имя переменной из select. Такая же должна быть в DB колонках
                varname = sl;
                varoper = "";
            } else {
            	// имя переменной из select с as
                varname = sl.substr(aspos + 4);
                varoper = sl.substr(0, aspos);
            }
            if (!columnNameLexic.analyze(varname)) {
                fres = 0;
                break;
            }
            if (columnNameLexic.tokenlist.size() != 1) {
                cout << "Illegal name structure. Name " << varname << ". Column: " << num << endl;
                fres = 0;
                break;
            }

            TokenProtoype tp = columnNameLexic.tokenlist.front();
            tp.value2 = varoper;
            tp.ioper1 = VARIABLE_INDEX;
            columnNameTokens.push_back(tp);
            num++;
        }
    } catch (AnalyzeException& s) {
        cout << "\n Select parsing. Column: " << num << "." << s.what() << endl;
        fres = 0;
    }
    return fres;
}

int MapExec::initOutputVariables(string& str) { //на основе select делает набор колонок
    if (!parseSelect(str)) {
        return 0;
    }
    numvariables = columnNameTokens.size();
    variables = new Variable*[numvariables];
    for (int ns = 0; ns < numvariables; ++ns) {
        variables[ns] = 0;
    }
    vector<TokenProtoype>::iterator tokenit;
    int num = 0;
    int fres = 1;
    // анализаторы для значений колонок
    try {
        selectLexic->setColumnTokens(&variableTable->columnTokens);
        SyntaxAnalyzer projectionSyntax(selectLexic, variableTable);
        int num = 0;
        for (tokenit = columnNameTokens.begin(); tokenit < columnNameTokens.end(); tokenit++) {
            TokenProtoype tp = *tokenit;
            Variable* v = new Variable();
            Field* f = variableTable->getField(tp.value);
            if (tp.value2.length() > 0) {
                if (f) {
                	// такого столбца не должно быть во входном файле данных
                    string mes = "Such field is already in input fields: " + tp.value;
                    throw AnalyzeException(mes.c_str());
                }
                if (selectLexic->analyze(tp.value2)) {
                    Operation* operation = projectionSyntax.analyse();
                    if (operation) {
                        v->oper = operation;
                    } else {
                        return 0;
                    }
                } else {
                    return 0;
                }
            } else {
                if (!f) {
                    string mes = "No input field for output field: " + tp.value;
                    throw AnalyzeException(mes.c_str(), 0);
                }
                v->oper = f;
            }
            v->name = tp.value;
            variables[num] = v;
            if (num > 0) {
                ofile << sep;
            }
            ofile << tp.value;
            num++;
        }
        ofile << endl;
    } catch (AnalyzeException& s) {
        cout << "\n Output columnSelect parsing. Column: " << num << "." << s.what() << endl;
        fres = 0;
    }
    return fres;
}

int MapExec::initFilter(string sfilter) {
    try {
        if (sfilter.length() > 0) {
            ConditionAnalyzer conditionLexic;
            try {
                conditionLexic.setColumnTokens(&variableTable->columnTokens);
                SyntaxAnalyzer conditionSyntax(&conditionLexic, variableTable);
                if (conditionLexic.analyze(sfilter)) {
                    filter = conditionSyntax.analyse();
                    if (!filter) {
                        return 0;
                    }
                } else {
                    return 0;
                }
            } catch (exception e) {
                cout << "ERROR: " << e.what() << endl;
            }
            conditionLexic.freememory();
        }
        return 1;
    } catch (AnalyzeException& s) {
        cout << "\n Condition parsing" << s.what() << endl;
    }
    return 0;
}

int MapExec::checkFilter() {
    return filter ? filter->bexecute() : 1;
}

int MapExec::output() {
    if (checkFilter()) {
    	// условие выполняется
        for (int ns = 0; ns < numvariables; ++ns) {
            if (ns > 0) {
                ofile << sep;
            }
            Variable* f = variables[ns];
            //            cout << "output: " << f->asstring() << endl;
            try {
                if (f->isfloat()) {
                    ofile << f->dexecute();
                } else {
                    ofile << f->iexecute();
                }
            } catch (AnalyzeException& e) {
                cout << "ERROR. Calculation of output field " << f->asstring() << ". " << e.what() << endl;
                return 0;
            }
        }
        ofile << endl;
    }
    return 1;
}

MapExec::~MapExec() {
    freememory();
}

void MapExec::freememory() {
    if (variables) {
        for (int ns = 0; ns < numvariables; ++ns) {
            if (variables[ns]) {
                variables[ns]->freeMemory();
                delete variables[ns];
                variables[ns] = 0;
            }
        }
        delete variables;
        variables = 0;
    }
    if (filter) {
        filter->freeMemory();
        delete filter;
        filter = 0;
    }
    if (selectLexic) {
        selectLexic->freememory();
        selectLexic = 0;
    }
    if (ofile.is_open()) {
        ofile.flush();
        ofile.close();
    }
}
ReduceExec::ReduceExec(char c, LexicalAnalyzer* selL, VariableTable* vt) :
        MapExec(c, selL, vt) {
    keys = 0;
    keyvalues = 0;
    numkeys = 0;
}

int ReduceExec::initKeyVariables(string& s) {
    LexicalAnalyzer keyLexic;
    keyLexic.setColumnTokens(&variableTable->columnTokens);
    keyLexic.isword = 1;
    keyLexic.sep = ',';
    if (!keyLexic.analyze(s)) {
        keyLexic.freememory();
        return 0;
    }
    vector<TokenProtoype> columnTokens = keyLexic.tokenlist;
    numkeys = columnTokens.size();
    keys = new Field*[numkeys];
    keyvalues = new Field*[numkeys];
    for (int ns = 0; ns < numkeys; ++ns) {
        keys[ns] = 0;
        keyvalues[ns] = 0;
    }
    vector<TokenProtoype>::iterator tokenit;
    int num = 0;
    int fres = 1;
    // анализаторы для значений колонок
    try {
        int num = 0;
        for (tokenit = columnTokens.begin(); tokenit < columnTokens.end(); tokenit++) {
            TokenProtoype tp = *tokenit;
            Field* f = variableTable->getField(tp.value);
            f->aggrkey = 1;
            keys[num] = f;
            keyvalues[num] = new Field();
            if (num > 0) {
                ofile << sep;
            }
            ofile << tp.value;
            num++;
        }
        ofile << sep;
    } catch (AnalyzeException& s) {
        cout << "\n Output columnSelect parsing. Column: " << num << "." << s.what() << endl;
        fres = 0;
    }
    keyLexic.freememory();
    return fres;
}

int ReduceExec::output(int pos) {
    if (pos == FIRST_LINE) {
        compareKeys(1);
    }
    if (pos != LAST_LINE && (pos == FIRST_LINE || compareKeys(0))) {
        if (!accumulate()) {
            return 0;
        }
    } else {
        for (int ns = 0; ns < numkeys; ++ns) {
            if (ns > 0) {
                ofile << sep;
            }
            ofile << keyvalues[ns]->getSValue();
        }
        for (int ns = 0; ns < numvariables; ++ns) {
            Variable* f = variables[ns];
            //            cout << "output: " << f->asstring() << endl;
            ofile << sep;
            try {
                if (f->isfloat()) {
                    ofile << f->dexecute();
                } else {
                    ofile << f->iexecute();
                }
            } catch (AnalyzeException& e) {
                cout << "ERROR. Calculation of output field " << f->asstring() << ". " << e.what() << endl;
                return 0;
            }
        }
        ofile << endl;
        compareKeys(1);
        if (!accumulate()) {
            return 0;
        }
    }
    return 1;
}

int ReduceExec::accumulate() {
    for (int ns = 0; ns < numvariables; ++ns) {
        Variable* f = variables[ns];
        try {
            f->accumulate();
        } catch (AnalyzeException& e) {
            cout << "ERROR. Calculation of output field " << f->asstring() << ". " << e.what() << endl;
            return 0;
        }
    }
    return 1;
}

int ReduceExec::compareKeys(int move) {
    int result = 1;
    for (int ns = 0; ns < numkeys; ++ns) {
        Field* fm = keyvalues[ns];
        Field* fk = keys[ns];
        if (fm->isfloat() || fk->isfloat()) {
            if (fm->dexecute() != fk->dexecute()) {
                if (move) {
                    fm->setSValue(fk->getSValue());
                    result = 0;
                } else {
                    return 0;
                }
            }
        } else {
            if (fm->iexecute() != fk->iexecute()) {
                if (move) {
                    fm->setSValue(fk->getSValue());
                    result = 0;
                } else {
                    return 0;
                }
            }
        }
    }
    return result;
}

void ReduceExec::freememory() {
    if (keys) {
        delete keys;
        keys = 0;
    }
    if (keyvalues) {
        for (int ns = 0; ns < numkeys; ++ns) {
            if (keyvalues[ns]) {
                delete keyvalues[ns];
                keyvalues[ns] = 0;
            }
        }
        delete keyvalues;
        keyvalues = 0;
    }
    MapExec::freememory();
}
