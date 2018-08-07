// reading a text file
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Parser.h"
#include "CsvDataReader.h"
#include "MapExec.h"

using namespace std;

int main(int argc, char* argv[]) {
    string seps, select, sfilter, ifname, ofname;
//--sep=" " --select="sqrt(age) as normalized_age, (score1+score2+score3)/3 as mean_score, group" --filter="group>204 and not age=20+1" input.csv output.csv
    arg_mainparser(argv, seps, select, sfilter, ifname, ofname);
    cout << "sep : " << seps << endl << "select : " << select << endl << "sfilter : " << sfilter << endl << "ifname : " << ifname << endl << "ofname : " << ofname << endl;
    cout << "-----------------" << endl;


    // взять первый символ из строки как разделитель
    char sep = seps[0];

    // читает данные из входного csv файла с разделителем sep
    CsvDataReader reader(sep);
    if (!reader.init(ifname)) {
        return 0;
    }

    VariableTable variableTable(&reader);

    // переменные на основе имен колонок из файла данных
    // считать названия колонок в файле данных и создать массив полей
    // id age group task score1 score2 score3
    if (!variableTable.initInputFields()) {
        variableTable.freememory();
        reader.close();
        return 0;
    }

    SelectAnalyzer lexic;//парсинг выражения select
    MapExec mapVariables(sep, &lexic, &variableTable);
    if (!mapVariables.initOutputFile(ofname)
            || !mapVariables.initOutputVariables(select) //обработка выражения проекции
            || !mapVariables.initFilter(sfilter)) { //обработка выражения проекции
        mapVariables.freememory();
        variableTable.freememory();
        reader.close();
        return 0;
    }

    // установить значения полей из входного файла
    while (variableTable.setValues() && //считывание и установка полей в массив fields
            // вывести в файл результаты
            mapVariables.output() //проверка фильтра, рассчет проекционных операций, запись в файл
            ) {
    }

    mapVariables.freememory();
    variableTable.freememory();
    reader.close();
    cout << "   --- That's all!!!\n";
    return 0;
}
