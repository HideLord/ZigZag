#include "ZigZag.h"
#include <cassert>

void ZigZag::solve(){
	srand((int)time(0));
	while (true) {
		generate();
		cout << "Save[y/s],Another[n/e]" << endl;
		string ans;
		cin >> ans;
		if (ans.find('y') != string::npos || ans.find('s') != string::npos) break;
	}
}

void ZigZag::generate(){
	used.assign(allWords.size(), false);
	puzzleWords.assign(LEN, "");
	random_shuffle(allWords.begin(), allWords.end());
	fill(0);
}

void ZigZag::print(){
	cout << puzzleWords[0] << '\n';
	for (int i = 1; i < LEN - 1; i += 2)cout << puzzleWords[i] << " " << puzzleWords[i + 1] << '\n';
	cout << setw(13) << puzzleWords[LEN - 1] << endl;
}

bool ZigZag::fill(int i){
	if (i == LEN) {
		print();
		return true;
	}
	for (int j = 0; j < (int)allWords.size(); j++) {
		if (used[j])continue;
		if (!isValid(i, allWords[j]))continue;
		used[j] = true;
		puzzleWords[i] = allWords[j];
		if (fill(i + 1))return true;
		used[j] = false;
	}
	return false;
}

bool ZigZag::isValid(int i, string& s){
	if (i & 1) // left going
		return check14(i - 1, s) && check23(i - 3, s);
	else	   // right going
		return check05(i - 1, s);
}

bool ZigZag::check05(int i, string& s){
	if(i < 0)return true;
	assert((int)puzzleWords.size() > i);
	return puzzleWords[i][0] == s[0] && puzzleWords[i][5] == s[5];
}

bool ZigZag::check14(int i, string& s){
	if (i < 0)return true;
	assert((int)puzzleWords.size() > i);
	return puzzleWords[i][1] == s[1] && puzzleWords[i][4] == s[4];
}

bool ZigZag::check23(int i, string& s){
	if (i < 0)return true;
	assert((int)puzzleWords.size() > i);
	return puzzleWords[i][2] == s[2] && puzzleWords[i][3] == s[3];
}
