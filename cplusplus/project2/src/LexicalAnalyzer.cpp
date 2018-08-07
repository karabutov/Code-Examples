#include "LexicalAnalyzer.h"

LexicalAnalyzer::LexicalAnalyzer() {
    isnum = 0;
    isword = 0;
    anyword = 0;
    sep = ' ';
    delimeterNumber = 0;
    delimeterProtos = 0;
    keywordNumber = 0;
    keywordProtos = 0;
    functionNumber = 0;
    functionProtos = 0;
    columnTokens = 0;
    iteratorReady = 0;
}

LexicalAnalyzer::LexicalAnalyzer(char sp, int in, int iw, int dn, int dw, int fn) {
    sep = sp;
    isnum = in;
    isword = iw;
    anyword = 0;
    delimeterNumber = dn;
    if (delimeterNumber == 0) {
        delimeterProtos = 0;
    } else {
        delimeterProtos = new TokenProtoype*[delimeterNumber];
    }
    keywordNumber = dw;
    if (keywordNumber == 0) {
        keywordProtos = 0;
    } else {
        keywordProtos = new TokenProtoype*[keywordNumber];
    }
    functionNumber = fn;
    if (functionNumber == 0) {
        functionProtos = 0;
    } else {
        functionProtos = new TokenProtoype*[functionNumber];
    }
    columnTokens = 0;
    iteratorReady = 0;
    integerPrototype = TokenProtoype("", INTEGER_INDEX, 0);
    doublePrototype = TokenProtoype("", DOUBLE_INDEX, 0);
}

LexicalAnalyzer::~LexicalAnalyzer() {
    freememory();
}

void LexicalAnalyzer::freememory() {
    if (delimeterProtos) {
        freetokens(delimeterProtos, delimeterNumber);
        delete delimeterProtos;
        delimeterProtos = 0;
    }
    if (keywordProtos) {
        freetokens(keywordProtos, keywordNumber);
        delete keywordProtos;
        keywordProtos = 0;
    }
    if (functionProtos) {
        freetokens(functionProtos, functionNumber);
        delete functionProtos;
        functionProtos = 0;
    }
}

void LexicalAnalyzer::freetokens(TokenProtoype** tps, int num) {
    for (int ns = 0; ns < num; ns++) {
        if (tps[ns]) {
            delete tps[ns];
            tps[ns] = 0;
        }
    }
}

TokenProtoype& LexicalAnalyzer::nextToken() {
    if (iteratorReady) {
        it++;
    } else {
        it = tokenlist.begin();
        iteratorReady = 1;
    }
    return it == tokenlist.end() ? emptyPrototype : *it;
}

TokenProtoype& LexicalAnalyzer::currentToken() {
    return *it;
}

void LexicalAnalyzer::resetTokenIterator() {
    iteratorReady = 0;
}

int LexicalAnalyzer::eoi() {
    return it == tokenlist.end();
}

TokenProtoype* LexicalAnalyzer::getDelimeterTokenProto(int n) {
    return delimeterProtos[n];
}

TokenProtoype* LexicalAnalyzer::getKeyWordTokenProto(int n) {
    return keywordProtos[n];
}

TokenProtoype* LexicalAnalyzer::getFunctionTokenProto(int n) {
    return functionProtos[n];
}

void LexicalAnalyzer::setColumnTokens(vector<TokenProtoype>* vn) {
    columnTokens = vn;
}

TokenProtoype LexicalAnalyzer::parseToken(StringStream &stream) { //формирование массива, проверка типа
    char c = stream.notempty();
    int position = stream.position();
    // Если число
    if (isnum && ((c >= '0' && c <= '9') || c == '.')) {
        PrototypeInfo info = stream.currentNumber();
        TokenProtoype tp = integerPrototype;
        if (info.fraction) {
            tp = doublePrototype;
        }
        tp.value = info.value;
        tp.position = position;
        return tp;
    }

    // Если ключевое слово
    if (isword && ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_')) {
        PrototypeInfo info = stream.currentWord();
        for (int ns = 0; ns < keywordNumber; ns++) {
            TokenProtoype* tp = getKeyWordTokenProto(ns);
            if (0 == strcasecmp(tp->value.c_str(), info.value.c_str())) {
                TokenProtoype result = *tp;
                result.position = position;
                return result;
            }
        }
        // Если переменная
        if (columnTokens) {
            vector<TokenProtoype>::iterator it;
            for (it = columnTokens->begin(); it < columnTokens->end(); it++) {
                TokenProtoype tp = *it;
                if (0 == tp.value.compare(info.value)) {
                    tp.position = position;
                    return tp;
                }
            }
        }

        // Если функция
        for (int ns = 0; ns < functionNumber; ns++) {
            TokenProtoype* tp = getFunctionTokenProto(ns);
            if (0 == strcasecmp(tp->value.c_str(), info.value.c_str())) {
                if (stream.checkNext('(')) {
                    stream.next();
                    TokenProtoype result = *tp;
                    result.position = position;
                    return result;
                } else {
                    break;
                }
            }
        }
        // Если любое слово
        if (anyword) {
            TokenProtoype result(info.value, VARIABLE_INDEX, 0);
            result.position = position;
            return result;
        }
        string mes = "Illegal word: " + info.value;
        throw AnalyzeException(mes.c_str(), stream);
    }

    for (int ns = 0; ns < delimeterNumber; ns++) {
        TokenProtoype* tp = getDelimeterTokenProto(ns);
        if (tp->symbol == stream.current()) {
            c = stream.next();
            TokenProtoype result = *tp;
            result.position = position;
            return result;
        }
    }
    //
    throw AnalyzeException("Illegal symbol", stream);
}

/*int LexicalAnalyzer::analyze(string &s) {
    StringStream stream(s, sep);
    int result = 1;
    try {
        analyze(stream);
    } catch (AnalyzeException& s) {
        cout << '\n' << s.what() << endl;
        result = 0;
    }
    return result;
}
*/
void LexicalAnalyzer::analyze(StringStream &stream) {
    tokenlist.clear();
    resetTokenIterator();
    stream.next();
    while (!stream.eos()) {
        TokenProtoype tp = parseToken(stream);
        tokenlist.push_back(tp);
    }
}
