#include "Painter.h"

Painter::Painter(ZigZag& Z){
	create(Z.puzzleWords);
	writeClues(Z.puzzleWords, Z.dict);
}

#include <sstream>

void Painter::printToSVG(){
	stringstream buffer;
	buffer << root << endl;
	wstring ws = SVG::SVG_element::to_wide(buffer.str());
	FILE* outFile = fopen("Z:\\Aprn\\aab.svg", "w+,ccs=UTF-8");
	fwrite(ws.c_str(), ws.size() * sizeof(wchar_t), 1, outFile);
	fclose(outFile);
	system("inkscape \"Z:\\Aprn\\aab.svg\" -E \"Z:\\Aprn\\aab.eps\" --export-text-to-path --export-ignore-filters --export-ps-level=2");
}

void Painter::create(vector<string> words){
	int wordLen = (int)words[0].length();
	root = GetRoot((wordLen * (squareSize + borderSize) + squareSize)*2 + squareSize,
		((int)words.size()>>1) * (squareSize + borderSize) + squareSize);
	right = left = SVG_element("g");
	right["transform"] = "translate(" + to_string(wordLen * (squareSize + borderSize) + squareSize) + ", 0)";

	createVerticalLines(wordLen, (int)words.size() >> 1, right);
	createHorizontalLines(wordLen, (int)words.size() >> 1, right);

	createVerticalLines(wordLen, (int)words.size() >> 1, left);
	createHorizontalLines(wordLen, (int)words.size() >> 1, left);

	for (int i = 0; i < (int)words.size(); i++) 
		putLetters(i>>1, words[i], (i&1?right:left));

	root.add_copy(left);
	root.add_copy(right);
}

string Painter::splitAndClean(string expl){
	vector<string> S;
	int delimiter;
	expl += "!!! ";
	while ((delimiter = expl.find("!!!")) != string::npos) {
		S.push_back(expl.substr(0, delimiter));
		if (isspace(S.back().back()))
			S.back().pop_back();
		expl = expl.substr(delimiter + 4);
	}
	for (auto& s : S) {
		vector<int> slashInd;
		for (int i = 0; i < (int)s.size(); i++)if(s[i]=='/')slashInd.push_back(i);
		if (slashInd.size() >= 2u) {
			if (slashInd[1] + 1 < s.size())s = s.substr(0, slashInd[0]) + s.substr(slashInd[1] + 1);
			else s = s.substr(0, slashInd[0]);
			if (!s.empty() && isspace(s.back()))s.pop_back();
		}
	}
	return S[0];
}

void Painter::writeClues(vector<string> words, dictionary &dict){
	ofstream fout("Z:/cross/zig.txt");
	fout << "ÍÀÄßÑÍÎ-ÍÀËßÂÎ: ";
	for (int i = 0, j = 1; i < (int)words.size(); i+=2) {
		string expl = splitAndClean(dict.explanationDict[words[i]]);
		fout << j++ << ". " << expl << ". ";
	}
	fout << endl << "ÍÀËßÂÎ-ÍÀÄßÑÍÎ: ";
	for (int i = 1, j = 2; i < (int)words.size(); i += 2) {
		string expl = splitAndClean(dict.explanationDict[words[i]]);
		fout << j++ << ". " << expl << ". ";
	}
	fout.close();
}

void Painter::putLetters(int i, string& word, SVG_element &root){
	for (int j = 0; j < (int)word.size(); j++) {
		double x = borderSize * ((long long)j + 1) + squareSize * j + squareSize / 2.0; // first border + number of squares before this + middle of current square
		double y = borderSize * ((long long)i + 1) + squareSize * i + squareSize * 0.8; // start at the 4th fifth of the square

		auto letter = GetText(x, y, word.substr(j, 1));
		letter["font-weight"] = "bold";
		letter["font-size"] = to_string(squareSize / 1.4);
		letter["font-family"] = "Arial";
		root.add_copy(letter);
	}
}

void Painter::createVerticalLines(int wordLen, int numWords, SVG_element& root){
	for (int i = 0; i <= wordLen; i++) {
		SVG_element line("line");
		line["x1"] = to_string(borderSize / 2.0 + (squareSize + borderSize) * i);
		line["y1"] = to_string(borderSize / 2.0);
		line["x2"] = to_string(borderSize / 2.0 + (squareSize + borderSize) * i);
		line["y2"] = to_string((squareSize + borderSize) * numWords + borderSize);

		line["style"] = "stroke:rgb(0,0,0);stroke-width:" + to_string(i == 0 || i == wordLen ? borderSize : borderSize * 0.7);
		root.add_copy(line);
	}
}

void Painter::createHorizontalLines(int wordLen, int numWords, SVG_element& root){
	for (int i = 0; i <= numWords; i++) {
		SVG_element line("line");
		line["y1"] = to_string(borderSize / 2.0 + (squareSize + borderSize) * i);
		line["x1"] = to_string(0);
		line["y2"] = to_string(borderSize / 2.0 + (squareSize + borderSize) * i);
		line["x2"] = to_string((squareSize + borderSize) * wordLen + borderSize);

		line["style"] = "stroke:rgb(0,0,0);stroke-width:" + to_string(i == 0 || i == numWords ? borderSize : borderSize * 0.7);	
		root.add_copy(line);
	}
}
