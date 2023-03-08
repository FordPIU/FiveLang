#pragma once

#include <unordered_set>
#include "Utils.h"

using namespace Utils;


class TextRange {
public:
	TextRange(int start, int end) : start(start), end(end) {}

	int start;
	int end;
};

class TextBody {
public:
	TextBody(int start, int end, string codeText) {
		this->start = start;
		this->end = end;
		this->bodyText = codeText.substr(start, end);
		this->subBodies = {};
	}

	int start = 0;
	int end = 0;

	string bodyText = "";
	list<TextBody> subBodies = {};
};


class Lexer {
public:
	Lexer(string rawFileText);

	void Lex();

	string GetCodeText() { return this->codeText; }
	list<string> GetCodeLines() { return this->codeLines; }
	list<TextBody> GetCodeBodies() { return this->codeBodies; }

private:
	string fileText;
	int fileTextLength = 0;

	string codeText;
	int codeTextLength = 0;
	list<string> codeLines;
	list<TextBody> codeBodies;

	void RemoveSLComments();
	void RemoveMLComments();
	void RemoveSoLSpaces();

	void ChunkifyByLine();

	void newText(string newText);
};