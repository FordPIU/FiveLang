#pragma once

#include <unordered_set>
#include "Utils.h"

using namespace Utils;


class Lexer {
public:
	Lexer(string rawFileText);

	void Lex();

	string GetCodeText() { return this->codeText; }
	list<string> GetCodeLines() { return this->codeLines; }
	list<string> GetCodeBodys() { return this->codeBodys; }

private:
	string fileText;
	int fileTextLength = 0;

	string codeText;
	int codeTextLength = 0;
	list<string> codeLines;
	list<string> codeBodys;

	void RemoveSLComments();
	void RemoveSoLSpaces();

	void ChunkifyByLine();
	void ChunkifyByBody();

	void newText(string newText);
}; //////