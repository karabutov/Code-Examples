#ifndef LEXICALANALYZER_H_
#define LEXICALANALYZER_H_

#include <string>
#include <cstring>
#include <stdlib.h>
#include <vector>

#include "AnalyzeException.h"
#include "Constants.h"
#include "TokenProtoype.h"
#include "StringStream.h"

using namespace std;

class LexicalAnalyzer {
public:

    vector<TokenProtoype> tokenlist;
    vector<TokenProtoype>::iterator it;
    int iteratorReady;

    int isnum; //понимает числа
    int isword; //понимает имена переменных
    int anyword; //если 1, то не ищет в таблице переменных(воспринимает все слова, как перепенные)

    char sep;

    TokenProtoype integerPrototype;
    TokenProtoype doublePrototype;
    TokenProtoype emptyPrototype;

    TokenProtoype** delimeterProtos; //какие понимает символы

    TokenProtoype** keywordProtos; //какие понимает ключевые слова

    TokenProtoype** functionProtos; //какие функции понимает

    LexicalAnalyzer();
    LexicalAnalyzer(char sp, int in, int iw, int dn, int dw, int fn);
    virtual ~LexicalAnalyzer();
    void freememory();
    void freetokens(TokenProtoype** tps, int num);
    TokenProtoype& nextToken();
    TokenProtoype& currentToken();
    void resetTokenIterator();
    int eoi();
    virtual TokenProtoype* getDelimeterTokenProto(int n);
    virtual TokenProtoype* getKeyWordTokenProto(int n);
    virtual TokenProtoype* getFunctionTokenProto(int n);
    void setColumnTokens(vector<TokenProtoype>* vn);
    TokenProtoype parseToken(StringStream &stream);
    int analyze(string &s);
    void analyze(StringStream &stream);

protected:
    int delimeterNumber;
    int keywordNumber;
    int functionNumber;
    vector<TokenProtoype>* columnTokens;
};

class SelectAnalyzer: public LexicalAnalyzer {
public:
    SelectAnalyzer() :
            LexicalAnalyzer(' ', 1, 1, 6, 0, 1) {//понимает числа, понимает слова, 6 знаков операция, 0 ключевых слов, 1 функция
        delimeterProtos[0] = new TokenProtoype("-", ONE_MINUS_INDEX, TWO_MINUS_INDEX);
        delimeterProtos[1] = new TokenProtoype("+", ONE_PLUS_INDEX, TWO_PLUS_INDEX);
        delimeterProtos[2] = new TokenProtoype("*", 0, TWO_MULTI_INDEX);
        delimeterProtos[3] = new TokenProtoype("/", 0, TWO_DIVIDE_INDEX);
        delimeterProtos[4] = new TokenProtoype("(", OBRACKET_INDEX, 0);
        delimeterProtos[5] = new TokenProtoype(")", 0, CBRACKET_INDEX);

        functionProtos[0] = new TokenProtoype("sqrt", FUNCTION_INDEX, 0);
    }
};

class ConditionAnalyzer: public LexicalAnalyzer {
public:
    ConditionAnalyzer() :
            LexicalAnalyzer(' ', 1, 1, 9, 3, 1) {
        delimeterProtos[0] = new TokenProtoype("-", ONE_MINUS_INDEX, TWO_MINUS_INDEX);
        delimeterProtos[1] = new TokenProtoype("+", ONE_PLUS_INDEX, TWO_PLUS_INDEX);
        delimeterProtos[2] = new TokenProtoype("*", 0, TWO_MULTI_INDEX);
        delimeterProtos[3] = new TokenProtoype("/", 0, TWO_DIVIDE_INDEX);
        delimeterProtos[4] = new TokenProtoype("(", OBRACKET_INDEX, 0);
        delimeterProtos[5] = new TokenProtoype(")", 0, CBRACKET_INDEX);
        delimeterProtos[6] = new TokenProtoype(">", 0, TWO_MORE_INDEX);
        delimeterProtos[7] = new TokenProtoype("<", 0, TWO_LESS_INDEX);
        delimeterProtos[8] = new TokenProtoype("=", 0, TWO_EQU_INDEX);

        keywordProtos[0] = new TokenProtoype("not", ONE_NOT_INDEX, 0);
        keywordProtos[1] = new TokenProtoype("and", 0, TWO_AND_INDEX);
        keywordProtos[2] = new TokenProtoype("or", 0, TWO_OR_INDEX);

        functionProtos[0] = new TokenProtoype("sqrt", FUNCTION_INDEX, 0);
    }
};

class AggregationAnalyzer: public LexicalAnalyzer {
public:
    AggregationAnalyzer() :
            LexicalAnalyzer(' ', 1, 1, 6, 0, 4) {
        delimeterProtos[0] = new TokenProtoype("-", ONE_MINUS_INDEX, TWO_MINUS_INDEX);
        delimeterProtos[1] = new TokenProtoype("+", ONE_PLUS_INDEX, TWO_PLUS_INDEX);
        delimeterProtos[2] = new TokenProtoype("*", 0, TWO_MULTI_INDEX);
        delimeterProtos[3] = new TokenProtoype("/", 0, TWO_DIVIDE_INDEX);
        delimeterProtos[4] = new TokenProtoype("(", OBRACKET_INDEX, 0);
        delimeterProtos[5] = new TokenProtoype(")", 0, CBRACKET_INDEX);

        functionProtos[0] = new TokenProtoype("sqrt", FUNCTION_INDEX, 0);
        functionProtos[1] = new TokenProtoype("avg", FUNCTION_INDEX, 0);
        functionProtos[2] = new TokenProtoype("max", FUNCTION_INDEX, 0);
        functionProtos[3] = new TokenProtoype("min", FUNCTION_INDEX, 0);

    }

};

class ValueAnalyzer: public LexicalAnalyzer {
public:
    ValueAnalyzer() :
            LexicalAnalyzer(' ', 1, 0, 2, 0, 0) {
        delimeterProtos[0] = new TokenProtoype("-", ONE_MINUS_INDEX, TWO_MINUS_INDEX);
        delimeterProtos[1] = new TokenProtoype("+", ONE_PLUS_INDEX, TWO_PLUS_INDEX);
    }
};
#endif /* LEXICALANALYZER_H_ */
