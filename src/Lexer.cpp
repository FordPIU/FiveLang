#include "Lexer.h"


class TextRange {
public:
	TextRange(int start, int end) : start(start), end(end) {}

	int start;
	int end;
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

vector<string> getSurroundingListItems(int depth, list<string>::iterator it, list<string>& lst) {
	vector<string> result;

    auto prevIt = it;
    auto nextIt = it;

    // Advance prevIt and nextIt n times
    for (int i = 0; i < depth; i++) {
        if (prevIt != lst.begin()) {
            --prevIt;
        }
        if (nextIt != lst.end()) {
            ++nextIt;
        }
    }

    // Add the previous n words to the result
    while (prevIt != it) {
        result.push_back(*prevIt);
        ++prevIt;
    }

    // Add the current word to the result
    result.push_back(*it);

    // Add the next n words to the result
    while (nextIt != lst.end() && (nextIt != it || result.size() < 2*depth+1)) {
        result.push_back(*nextIt);
        ++nextIt;
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
		int i 					= static_cast<int>(distance(this->codeWords.begin(), it));
        vector<string> words 	= getSurroundingListItems(5, it, this->codeWords);
		string previous5Word 	= words[0];
		string previous4Word 	= words[1];
		string previous3Word 	= words[2];
		string previous2Word 	= words[3];
		string previous1Word 	= words[4];
		string currentWord 		= words[5];
		string next1Word 		= words[6];
		string next2Word 		= words[7];
		string next3Word 		= words[8];
		string next4Word 		= words[9];
		string next5Word 		= words[10];

		if (currentWord == "\n") { continue; }

		if (currentWord == "class") {
			if (!next1Word.empty() && hasNoCharactersInString(next1Word)) {
				this->tokens.push_back(new TOKEN_CLASS(i, next1Word));

				++it;
				continue;
			} else {
				error("Class Name is Invalid, at Word #" + to_string(i+1) + "\nInvalid Word is: " + next1Word);
				return;
			}
		} else if (currentWord == "thread") {
			if (!next1Word.empty() && hasNoCharactersInString(next1Word)) {
				this->tokens.push_back(new TOKEN_THREAD(i, next1Word));

				++it;
				continue;
			} else {
				error("Thread Name is Invalid, at Word #" + to_string(i+1) + "\nInvalid Word is: " + next1Word);
				return;
			}
		} else if (currentWord == "function") {
			if (!next1Word.empty()) {
				if (hasNoCharactersInString(next1Word)) {
					this->tokens.push_back(new TOKEN_FUNCTION(i, "none", next1Word));
				} else if (next1Word == "{" && next3Word == "}" && hasNoCharactersInString(next2Word)) {
					this->tokens.push_back(new TOKEN_FUNCTION(i, next2Word, next4Word));

					++it;
					++it;
					++it;
				} else {
					error("Function Name is Invalid, at Word #" + to_string(i+1) + "\nInvalid Word is: " + next1Word);
					return;
				}

				++it;
				continue;
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