#include "StringStream.h"
// поток символов на основе строки
StringStream::StringStream(string &s) {
    str = s;
    pos = -1;
    len = str.length();
    sep = ' ';
}

StringStream::StringStream(string &s, char sp) {
    str = s;
    pos = -1;
    len = str.length();
    sep = sp;
}

char StringStream::current() {
    return eos() ? 0 : str.at(pos);
}

int StringStream::position() {
    return pos;
}

string StringStream::asstring() {
    std::stringstream sstm;
    sstm << "stream[" << pos << "]=";
    if (eos()) {
        sstm << "(eos)";
    } else {
        sstm << "'" << str.at(pos) << "'";
    }
    return sstm.str();
}

int StringStream::checkNext(char symbol) {
    if (symbol == current()) {
        return 1;
    }
    int p = pos;
    next();
    if (symbol == current()) {
        return 1;
    }
    pos = p;
    return 0;
}

char StringStream::notempty() {
    char c = current();
    if (c == ' ' || c == sep) {
        c = next();
    }
    return c;
}

char StringStream::next() {
    while (++pos < len && (str.at(pos) == ' ' || str.at(pos) == sep)) {
    }
    if (pos >= len) {
        return 0;
    }
    return str.at(pos);
}

int StringStream::eos() {
    if (pos < len) {
        return 0;
    }
    return 1;
}

int StringStream::checkToken(string s) {
    if (eos()) {
        return 0;
    }
    unsigned int mpos = pos;
    char c = current();
    if (c == ' ' || c == sep) {
        c = next();
        if (c == 0) {
            pos = mpos;
            return 0;
        }
    }
    unsigned int sn = 0;
    while (!eos() && s.at(sn) == current()) {
        sn++;
        pos++;
        if (sn >= s.length()) {
            return pos;
        }
    }
    pos = mpos;
    return 0;
}

PrototypeInfo StringStream::currentNumber() {
    char c = 0;
    int frac = 0;
    int p1 = pos;
    pos++;
    while (pos < len) {
        c = str.at(pos);
        if (c == '.') {
            frac = 1;
        } else if (c < '0' || c > '9') {
            break;
        }
        pos++;
    }
    string ps;
    if (pos < len) {
        ps = str.substr(p1, pos - p1);
    } else {
        ps = str.substr(p1);
    }
    PrototypeInfo result = {ps, frac};
    return result;
}

PrototypeInfo StringStream::currentWord() {
    char c = 0;
    int frac = 0;
    int p1 = pos;
    pos++;
    while (pos < len) {
        c = str.at(pos);
        if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_' || (c >= '0' && c <= '9'))) {
            break;
        }
        pos++;
        continue;
    }
    string ps;
    if (pos < len) {
        ps = str.substr(p1, pos - p1);
    } else {
        ps = str.substr(p1);
    }
    PrototypeInfo result = {ps, frac};
    return result;
}
