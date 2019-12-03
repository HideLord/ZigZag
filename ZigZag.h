#pragma once
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <numeric>
#include <vector>
#include <string>
#include <set>
#include <map>

#include "dictionary.h"

using namespace std;

class ZigZag{
public:
	vector<string> puzzleWords;
	dictionary dict;
	ZigZag(int len, int wordlen) : LEN(len<<1), WORDLEN(wordlen){
		dict.loadDict();
		for (auto s : dict.allWords)
			if (s.length() == WORDLEN)
				allWords.push_back(s);
		solve();
	}
private:
	const int LEN, WORDLEN;
	vector<char> used;
	vector<string> allWords;
private:
	void solve();
	void generate();
	void print();

	bool fill(int i);

	bool isValid(int i, string& s);
	bool check05(int i, string& s);
	bool check14(int i, string& s);
	bool check23(int i, string& s);
};

