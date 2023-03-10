#pragma once

#include "CommonLibs.h"
#include "Utils.h"
#include "Tokens.h"
#include "Input.h"

using namespace Utils;

class Lexer
{
public:
	Lexer(Input fileInput);

	vector<TOKEN *> getTokens() { return this->tokens; };

private:
	string fileText;
	int fileTextLength = 0;
	bool Lexed = false;

	string codeText;
	int codeTextLength = 0;
	list<string> codeLines;
	list<string> codeWords;

	vector<TOKEN *> tokens = {};
};