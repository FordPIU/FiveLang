#pragma once

#include "Common.h"

class Range
{
public:
    int i1;
    int i2;
};

namespace String_Splitters
{
    vector<string> splitWords(string text, string delimiters, bool includeDelimiter);
    vector<string> splitLines(string text, char delimiter);
}

namespace String_Combiners
{
    string combineLines(vector<string> lines, char delimiter);
}

namespace String_Checkers
{
    bool checkHasNoCharacterInString(const string &word);
}

namespace String_Removers
{
    string removeRangesFromString(string text, vector<Range> ranges);
}

namespace String_Getters
{
    int getAscii(char chr);
}