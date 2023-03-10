#pragma once

#include "CommonLibs.h"
#include "ConsoleUtils.h"

using namespace ConsoleUtils;

class Range
{
public:
    int i1;
    int i2;
};

namespace StringUtils
{
    // Lines
    vector<string> splitLines(string text, char delimiter);
    string combineLines(vector<string> lines, char delimiter);

    // Has
    bool hasNoCharactersInString(const string &word);

    // Get
    int getAscii(char chr);

    // Removal
    string removeRangesFromStrng(string text, vector<Range> ranges);

    // Words
    vector<string> splitWords(string text, string delimiters, bool includeDelimiter = false);
};