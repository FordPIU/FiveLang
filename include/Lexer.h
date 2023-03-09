#pragma once

#include <unordered_set>
#include <cctype>
#include <vector>
#include "Utils.h"
#include "Tokens.h"

using namespace Utils;


class Lexer {
public:
	Lexer(string rawFileText);

	void Lex();
	void Tokenize();

	string GetCodeText() { return this->codeText; }
	list<string> GetCodeLines() { return this->codeLines; }
	list<string> GetCodeWords() { return this->codeWords; }
	list<Token*> GetTokens() { return this->tokens; }

private:
	string fileText;
	int fileTextLength = 0;
	bool Lexed = false;

	string codeText;
	int codeTextLength = 0;
	list<string> codeLines;
	list<string> codeWords;
	
	list<Token*> tokens = {};

	void RemoveSLComments();
	void RemoveMLComments();
	void RemoveSoLSpaces();

	void AdjustSpacingInStrings();

	void ChunkifyByLine();
	void ChunkifyByWords();

	void newText(string newText);
};