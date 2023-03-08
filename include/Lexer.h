#pragma once

#include <unordered_set>
#include <cctype>
#include "Utils.h"

using namespace Utils;


class Token {
public:
	Token(int wordNum) : wordNum(wordNum) {}

	int GetWordNumber() { return this->wordNum; }

	virtual void output_class() { printLn("Class contains no data to output"); }

private:
	int wordNum;
};

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

	void ChunkifyByLine();
	void ChunkifyByWords();

	void newText(string newText);
};