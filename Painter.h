#pragma once
#include "SVG_element.h"
#include "ZigZag.h"

using namespace SVG;
using namespace std;

class Painter{
public:
	Painter(ZigZag &Z);
	void printToSVG();
private:
	void create(vector<string> words);
	string splitAndClean(string expl);
	void writeClues(vector<string>, dictionary& );
	void putLetters(int i, string& word, SVG_element& );
	void createVerticalLines(int, int, SVG_element& );
	void createHorizontalLines(int, int, SVG_element& );
private:
	SVG_element root, left, right;
	const double squareSize = 10;
	const double borderSize = 1;
};

