#pragma once

#include "CommonLibs.h"

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

    // Removal
    string removeRangesFromStrng(string text, vector<Range> ranges);
};