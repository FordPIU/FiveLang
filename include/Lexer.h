#pragma once

#include <map>

#include "Common.h"
#include "Tokens.h"
#include "Input.h"

class Lexer
{
public:
	Lexer(Input fileInput);

	vector<Token *> getTokens() { return this->tokens; };

private:
	string fileText;
	int fileTextLength = 0;
	bool Lexed = false;

	string codeText;
	int codeTextLength = 0;
	vector<string> codeLines;
	vector<string> codeWords;

	vector<Token *> tokens = {};
};