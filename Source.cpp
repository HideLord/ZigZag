#include "ZigZag.h"
#include "Painter.h"

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	cout << "Length: " << endl;
	int length = 10;
	cin >> length;

	ZigZag solver(length, 6);
	Painter painter(solver);
	painter.printToSVG();
}