#ifndef STRINGSTREAM_H_
#define STRINGSTREAM_H_

#include <string>
#include <iostream>     // std::cout
#include <sstream>      // std::stringstream, std::stringbuf
#include <stdlib.h>
#include "Constants.h"

using namespace std;


class StringStream {
public:

    char sep;

	StringStream(string &s);
    StringStream(string &s, char sp);
	char current();
	int position();
	string asstring();
	int checkNext(char symbol);
    char notempty();
	char next();
	int eos();
	int checkToken(string s);
	PrototypeInfo currentNumber();
	PrototypeInfo currentWord();
private:

	int pos;
	string str;
	int len;
};

#endif /* STRINGSTREAM_H_ */
