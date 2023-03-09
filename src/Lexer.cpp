#include "Lexer.h"


class TextRange {
public:
	TextRange(int start, int end) : start(start), end(end) {}

	int start;
	int end;
};

class SurroudingWords {
public:
	vector<string> forward;
	vector<string> backward;
	string middle;
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

SurroudingWords getSurroundingListItems(int depth, list<string>::iterator it, list<string>& lst) {
	SurroudingWords result;

    auto prevIt = it;
    auto nextIt = it;

	result.middle = *it;

	for (int i = 0; i < depth; ++i) {
        result.forward.push_back("");
		result.backward.push_back("");
    }

	for (int i = 0; i < depth; ++i) {
		if (nextIt == lst.end()) { break; } else { ++nextIt; }
		result.forward[i] = (nextIt == lst.end()) ? "" : *nextIt;
	}

	for (int i = 0; i < depth; ++i) {
		if (prevIt == lst.begin()) { break; } else { --prevIt; }
		result.backward[i] = *prevIt;
	}

    return result;
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

	this->AdjustSpacingInStrings();

	this->ChunkifyByLine();
	this->ChunkifyByWords();
}

void Lexer::Tokenize() {
	if (!this->Lexed) { error("You did not lex yet!"); return; }

	for (auto it = this->codeWords.begin(); it != this->codeWords.end(); ++it) {
		int i = static_cast<int>(distance(this->codeWords.begin(), it));
        SurroudingWords words = getSurroundingListItems(5, it, this->codeWords);

		printLn("\nCurrent Word: " + words.middle);
		printLn("Previous Word #1: " + words.backward[0]);
		printLn("Previous Word #2: " + words.backward[1]);
		printLn("Previous Word #3: " + words.backward[2]);
		printLn("Previous Word #4: " + words.backward[3]);
		printLn("Previous Word #5: " + words.backward[4]);
		printLn("Next Word #1: " + words.forward[0]);
		printLn("Next Word #2: " + words.forward[1]);
		printLn("Next Word #3: " + words.forward[2]);
		printLn("Next Word #4: " + words.forward[3]);
		printLn("Next Word #5: " + words.forward[4]);

		//TOKEN_CLASS newToken = TOKEN_CLASS(i, "r" + to_string(i));
		//newToken.create_class();
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



void Lexer::AdjustSpacingInStrings() {
    bool inString = false;

    for (char& c : this->codeText) {
        if (c == '"') {
            inString = !inString;
        } else if (inString && c == ' ') {
            c = '_';
        }
    }
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
    string delimiters = " ,;({})\n";

    for (auto it = this->codeLines.begin(); it != this->codeLines.end(); ++it) {
        string lineText = *it;
        string token;
        size_t pos = 0;

        while (pos < lineText.length()) {
            size_t nextDelimiterPos = lineText.find_first_of(delimiters, pos);

            if (nextDelimiterPos == string::npos) {
                token = lineText.substr(pos);
                pos = lineText.length();
            } else {
                token = lineText.substr(pos, nextDelimiterPos - pos);
                pos = nextDelimiterPos + 1;
            }

            if (!token.empty()) {
                wordsList.push_back(token);
            }

			if (nextDelimiterPos != string::npos) {
                string delimiter = lineText.substr(nextDelimiterPos, 1);

				if (delimiter != "\n" && delimiter != " ") {
					wordsList.push_back(delimiter);
				}
            }
        }
    }

    this->codeWords = wordsList;
}

void Lexer::newText(string newText) {
	this->codeText = newText;
	this->codeTextLength = static_cast<int>(newText.length());
}