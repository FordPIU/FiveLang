#include "Lexer.h"


class TextRange {
public:
	TextRange(int start, int end) : start(start), end(end) {}

	int start;
	int end;
};

class TOKEN_CLASS : public Token {
public:
	TOKEN_CLASS(int wordNum, string className) : Token(wordNum), className(className) {}

	void output_class() override { printLn("Class Name: " + this->className); }

	string GetClassName() { return this->className; }

private:
	string className;
};



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

bool hasNoCharactersInString(const string& word) {
    static const string blacklist = "!@#$%^&*()_+-={}[]\\|;:'\"<>,.?/~`";

    for (char c : word) {
        if (blacklist.find(c) != string::npos) {
            return false;
        }
    }

    return true;
}



Lexer::Lexer(string rawFileText) {
	// Init the values
	this->fileText = "";
	this->fileTextLength = 0;

	// Empty check
	if (rawFileText.empty()) { error("Invalid File Text!"); return; }

	// Actually set
	this->fileText = rawFileText;
	this->fileTextLength = static_cast<int>(rawFileText.length());
}



void Lexer::Lex() {
	this->codeText = this->fileText;
	this->codeTextLength = this->fileTextLength;
	this->Lexed = true;

	this->RemoveSLComments();
	this->RemoveMLComments();
	this->RemoveSoLSpaces();

	this->ChunkifyByLine();
	this->ChunkifyByWords();
}

void Lexer::Tokenize() {
	if (!this->Lexed) { error("You did not lex yet!"); return; }

	for (auto it = this->codeWords.begin(); it != this->codeWords.end(); ++it) {
		int i = static_cast<int>(distance(this->codeWords.begin(), it));
        string currentWord = *it;
		string nextWord = "";
		
		auto nextIt = next(it);
		if (nextIt != this->codeWords.end()) {
			nextWord = *nextIt;
		}

		if (currentWord == "class") {
			if (!nextWord.empty() && hasNoCharactersInString(nextWord)) {
				this->tokens.push_back(new TOKEN_CLASS(i, nextWord));

				++it;
			} else {
				error("Class Name is Invalid, at Word #" + to_string(i+1) + "\nInvalid Word is: " + nextWord);
				return;
			}
		}
	}
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
	}

	string newText = removeRangesFromText(ranges, this->codeText);

	this->newText(newText);
}

void Lexer::RemoveMLComments() {
	list<TextRange> ranges;
	bool workingInComment = false;
	int commentStart = 0;

	for (int i = 0; i < this->codeTextLength; ++i) {
        char currentChar = this->codeText[i];
        char nextChar;

        if (i == this->codeTextLength - 1) {
            nextChar = ' ';
        } else {
            nextChar = this->codeText[i + 1];
        }

        if (!workingInComment && currentChar == '/' && nextChar == '*') {
            workingInComment = true;
            commentStart = i;

            ++i;
        } else if (workingInComment && currentChar == '*' && nextChar == '/') {
			ranges.push_back(TextRange(commentStart, i + 2));

            workingInComment = false;
			commentStart = 0;

            ++i;
        }
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
		char nextChar = this->codeText[i + 1];
		
		if (currentChar == ' ' && (i == 0 || this->codeText[i - 1] == '\n')) {
			start = i;
		}
		else if (start != -1 && nextChar != '\n' && currentChar != ' ') {
			ranges.push_back(TextRange(start, i));
			start = -1;
		}
	}

	if (this->codeText[this->codeTextLength - 2] == ' ') {
		int i = this->codeTextLength - 2;
		while (i >= 0 && this->codeText[i] == ' ') {
			ranges.push_back(TextRange(i, i + 1));
			--i;
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

void Lexer::ChunkifyByWords() {
	list<string> wordsList;

	for (auto it = this->codeLines.begin(); it != this->codeLines.end(); ++it) {
		string lineText = *it;
		string delimiter = " ";
		size_t pos = 0;
		string token;

		while ((pos = lineText.find(delimiter)) != string::npos) {
			token = lineText.substr(0, pos);

			if (!token.empty()) {
				wordsList.push_back(token);
			}

			lineText.erase(0, pos + delimiter.length());
		}

		if (!lineText.empty()) {
			wordsList.push_back(lineText);
		}
    }

	this->codeWords = wordsList;
}

void Lexer::newText(string newText) {
	this->codeText = newText;
	this->codeTextLength = static_cast<int>(newText.length());
}