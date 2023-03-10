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

int StringUtils::getAscii(char chr)
{
    return int(chr);
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

vector<string> StringUtils::splitWords(string text, string delimiters, bool includeDelimiter)
{
    vector<string> wordsList;
    string workingText = "";
    bool isInQuotes = false;

    for (char current : text)
    {
        if (current == '"' && !isInQuotes)
        {
            isInQuotes = true;
            workingText += current;
        }
        else if (current == '"' && isInQuotes)
        {
            isInQuotes = false;
            workingText += current;
        }
        else if (delimiters.find(current) != string::npos && !isInQuotes)
        {
            if (!workingText.empty())
            {
                wordsList.push_back(workingText);
                workingText = "";
            }

            if (includeDelimiter)
            {
                wordsList.push_back(string(1, current));
            }
        }
        else
        {
            workingText += current;
        }
    }

    if (!workingText.empty())
    {
        wordsList.push_back(workingText);
    }

    // Trimming
    vector<string> returnList;
    for (string word : wordsList)
    {
        if (getAscii(word[0]) != 10)
        {
            returnList.push_back(word);
        }
    }

    return returnList;
}