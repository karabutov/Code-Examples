#ifndef PARSER_H_
#define PARSER_H_

#include <string>
#include <vector>
#include <stdlib.h>
#include <cstring>

using namespace std;

static vector<string> parse(string s, char del) {
	vector<string> result;
	unsigned int pos = 0;
	string item;
	while ((pos = s.find(del)) != string::npos) {
		item = s.substr(0, pos);
		result.push_back(item);
		s.erase(0, pos + 1);
	}
	result.push_back(s);
	return result;
}

static void arg_mainparser(char **argv, string &sep, string &sel,
		string &filter, string &input, string &output) {

	string inter;
	for (int i = 1; i < 6; i++) {
		inter = string(argv[i]);
		if (inter.find("--sep=") != string::npos) {
			sep = string(inter.begin() + 6, inter.end());
		} else if (inter.find("--select=") != string::npos) {
			sel = string(inter.begin() + 9, inter.end());
		} else if (inter.find("--filter=") != string::npos) {
			filter = string(inter.begin() + 9, inter.end());
		} else {
			input = inter;
			inter.clear();
			i++;
			inter = string(argv[i]);
			output = inter;
		}
		inter.clear();
	}
}

static void arg_reduceparser(char **argv, string &sep, string &keys,
		string &aggrs, string &input, string &output) {
	string inter;
	for (int i = 1; i < 6; i++) {
		inter = string(argv[i]);
		string s(inter.begin() + 1, inter.begin() + 3);
		if (inter.find("--sep=") != string::npos) {
			sep = string(inter.begin() + 6, inter.end());
		} else if (inter.find("--keys=") != string::npos) {
			keys = string(inter.begin() + 7, inter.end());
		} else if (inter.find("--aggrs=") != string::npos) {
			aggrs = string(inter.begin() + 8, inter.end());
		} else {
			input = inter;
			inter.clear();
			i++;
			inter = string(argv[i]);
			output = inter;
		}
		inter.clear();
	}
}

#endif /* PARSER_H_ */

