#include "StringUtils.h"

vector<string> StringUtils::splitLines(string text, char delimiter)
{
    vector<string> lines;
    string line;

    for (const char &c : text)
    {
        if (c == '\n')
        {
            lines.push_back(line);
            line = "";
        }
        else
        {
            line += c;
        }
    }

    if (!line.empty())
    {
        lines.push_back(line);
    }

    return lines;
}

string StringUtils::combineLines(vector<string> lines, char delimiter)
{
    string text = "";

    for (string &line : lines)
    {
        text += line + delimiter;
    }

    return text;
}

bool StringUtils::hasNoCharactersInString(const string &word)
{
    static const string blacklist = "!@#$%^&*()_+-={}[]\\|;:'\"<>,.?/~`";

    for (char c : word)
    {
        if (blacklist.find(c) != string::npos)
        {
            return false;
        }
    }

    return true;
}

string StringUtils::removeRangesFromStrng(string text, vector<Range> ranges)
{
    string workText = text;
    int offset = 0;

    for (const auto &range : ranges)
    {
        int start = range.i1 + offset;
        int end = range.i2 + 1 + offset;
        workText.erase(start, end - start);
        offset -= end - start;
    }

    return workText;
}