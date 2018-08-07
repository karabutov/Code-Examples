#ifndef TOKENPROTOYPE_H_
#define TOKENPROTOYPE_H_

#include <string>

using namespace std;
//подготавливается лексическим анализатором
class TokenProtoype {
public:

    string value;//значение лексемы

    string value2;// для функции хранит значение аргументов

    char symbol;

    int position;

    int ioper1;//индекс унарной операции, используется синткасическим анализатором

    int ioper2;

    TokenProtoype();
    TokenProtoype(string s, int io1, int io2);
    virtual ~TokenProtoype();
    void setValue(string s);
    string asstring();
};

#endif /* TOKENPROTOYPE_H_ */
