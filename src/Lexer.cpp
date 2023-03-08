#include "Lexer.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>


class TextRange {
public:
	TextRange(int start, int end) : start(start), end(end) {}

	int start;
	int end;
};



void visualizeCode(int prevPos, int currPos, string codeText, bool isHighlighted)
{
	if (true) { return; }

	int method = 1;

	if (method == 0) {
		system("cls");

		for (int i = 0; i < codeText.size(); ++i) {
			if (i == prevPos || i == currPos) {
				if (isHighlighted) {
					cout << "\033[97;43m" << codeText[i] << "\033[0m"; // white on yellow for comment
				}
				else {
					cout << "\033[97;41m" << codeText[i] << "\033[0m"; // white on red for code
				}
			}
			else {
				cout << codeText[i];
			}
		}

		cout << endl;
	}
	else {
		HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

		COORD topLeft = { 0, 0 };
		SetConsoleCursorPosition(console, topLeft);

		for (int i = 0; i < codeText.size(); ++i) {
			if (i == prevPos || i == currPos) {
				if (isHighlighted) {
					std::cout << "\033[33m" << codeText[i] << "\033[0m"; // yellow for comment
				}
				else {
					std::cout << "\033[31m" << codeText[i] << "\033[0m"; // red for code
				}
			}
			else {
				std::cout << codeText[i];
			}
		}

		std::cout << std::endl;
	}
}

string removeRangesFromText(list<TextRange> ranges, string codeText) {
	string workingText = codeText;
	int removalOffset = 0;

	for (const auto& rangePos : ranges) {
		int start = rangePos.start - removalOffset;
		int end = rangePos.end - removalOffset;

		workingText.erase(start, end - start);

		removalOffset += end - start;
	}

	return workingText;
}



Lexer::Lexer(string rawFileText) {
	// Init the values
	this->fileText = "";
	this->fileTextLength = 0;

	// Empty check
	if (rawFileText.empty()) { error("Invalid File Text!"); return; }

	// Actually set
	this->fileText = rawFileText;
	this->fileTextLength = rawFileText.length();
}



void Lexer::Lex() {
	this->codeText = this->fileText;
	this->codeTextLength = this->fileTextLength;

	this->RemoveSLComments();
	system("cls");
	this->RemoveSoLSpaces();

	this->ChunkifyByLine();
	//this->ChunkifyByBody();
}



void Lexer::RemoveSLComments() {
	list<TextRange> ranges;
	bool workingInComment = false;
	int commentStart = 0;

	for (int i = 0; i < this->codeTextLength; ++i) {
		char currentChar = this->codeText[i];
		char prevChar;

		if (i == 0) {
			prevChar = ' ';
		}
		else {
			prevChar = this->codeText[i - 1];
		}

		if (workingInComment == false) {
			if (currentChar == '/' && prevChar == '/') {
				workingInComment = true;
				commentStart = i - 1;
			}
		}
		else {
			if (i == (this->codeTextLength - 1) || (currentChar == '/' && prevChar == '/') || currentChar == '\n') {
				int e = i;

				if (currentChar == '/') { e += 1; }

				ranges.push_back(TextRange(commentStart, e));

				workingInComment = false;
				commentStart = 0;
			}
		}

		visualizeCode(i, i - 1, this->codeText, workingInComment);
	}

	string newText = removeRangesFromText(ranges, this->codeText);

	this->newText(newText);
}

void Lexer::RemoveSoLSpaces() {
	list<TextRange> ranges;
	bool foundSpace = false;
	bool newLine = true;
	int start = -1;

	for (int i = 0; i < (this->codeTextLength - 1); ++i) {
		char currentChar = this->codeText[i];

		if (foundSpace == false && currentChar == ' ' && newLine == true) {
			start = i;
			foundSpace = true;
			newLine = false;
		}
		else if (foundSpace == true && currentChar != ' ') {
			ranges.push_back(TextRange(start, i));
			foundSpace = false;
		}

		if (currentChar == '\n') { newLine = true; }

		if (start != -1) {
			visualizeCode(start, i, this->codeText, foundSpace);
		}
	}

	string newText = removeRangesFromText(ranges, this->codeText);

	this->newText(newText);
}



void Lexer::ChunkifyByLine() {
	list<string> lineList;
	string workingLine = "";
	bool workingLineFoundChar = false;

	for (int i = 0; i < this->codeTextLength; ++i) {
		char currentChar = this->codeText[i];

		if (currentChar == ';' || currentChar == '\n' || i == this->codeTextLength) {
			if (!workingLine.empty()) {
				lineList.push_back(workingLine);
			}

			workingLine = "";
			workingLineFoundChar = false;
		}
		else {
			if (currentChar == ' ' && workingLineFoundChar == false) {
				continue;
			}
			else {
				workingLineFoundChar = true;
			}

			workingLine += currentChar;
		}
	}

	this->codeLines = lineList;
}

void Lexer::ChunkifyByBody() {
	list<string> newCodeBodys;


}



void Lexer::newText(string newText) {
	this->codeText = newText;
	this->codeTextLength = newText.length();
}

