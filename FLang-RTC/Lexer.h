#pragma once

#include <unordered_set>
#include "Utils.h"

using namespace Utils;

class Lexer {
public:
	Lexer(string rawFileText);

	list<string> GetCurrentFileText();

	void ChunkifyByLine();
	void RemoveComments();

private:
	string fileText;
	int fileTextLength;

	list<string> updatedFileText;
};