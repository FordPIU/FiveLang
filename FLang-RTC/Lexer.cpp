#include "Lexer.h"


class TextRange {
public:
	TextRange(int start, int end) : start(start), end(end) {}

	int start;
	int end;
};


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

list<string> Lexer::GetCurrentFileText() {
	return this->updatedFileText;
}

void Lexer::ChunkifyByLine() {
	list<string> lineList;
	string workingLine = "";
	bool workingLineFoundChar = false;

	for (int i = 0; i < this->fileTextLength; ++i) {
		char currentChar = this->fileText[i];

		if (currentChar == ';' || currentChar == '\n' || i == this->fileTextLength) {
			lineList.push_back(workingLine);

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

	this->updatedFileText = lineList;
}

/// <summary>
/// You must ChunkifyByLine first!
/// </summary>
void Lexer::RemoveComments() {
	list<string> newFileText;

	for (auto it = this->updatedFileText.begin(); it != this->updatedFileText.end(); ++it) {
		string lineText = *it;
		list<TextRange> ranges;

		bool workingInComment = false;
		int commentStart = 0;


		for (int i = 0; i < lineText.length(); ++i) {
			char currentChar = lineText[i];
			char prevChar;

			if (i == 0) {
				prevChar = ' ';
			}
			else {
				prevChar = lineText[i - 1];
			}

			if (workingInComment == false) {
				if (currentChar == '/' && prevChar == '/') {
					workingInComment = true;
					commentStart = i-1;
				}
			}
			else {
				if (i == (lineText.length() - 1) || (currentChar == '/' && prevChar == '/')) {
					ranges.push_back(TextRange(commentStart, i+1));

					workingInComment = false;
					commentStart = 0;
				}
			}
		}

		int removalOffset = 0;

		for (const auto& rangePos : ranges) {
			int start = rangePos.start - removalOffset;
			int end = rangePos.end + 1 - removalOffset;

			lineText.erase(start, end - start);

			removalOffset += end - start;
		}

		newFileText.push_back(lineText);
	}

	this->updatedFileText = newFileText;
}