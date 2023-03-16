#include "StringUtils.h"

// Splitters
vector<string> String_Splitters::splitWords(string text, string delimiters, bool includeDelimiter)
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
        if (String_Getters::getAscii(word[0]) != 10 && word[0] != ' ')
        {
            returnList.push_back(word);
        }
    }

    return returnList;
}

vector<string> String_Splitters::splitLines(string text, char delimiter)
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

// Combiners
string String_Combiners::combineLines(vector<string> lines, char delimiter)
{
    string text = "";

    for (string &line : lines)
    {
        text += line + delimiter;
    }

    return text;
}

// Checkers
bool String_Checkers::checkHasNoCharacterInString(const string &word)
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

// Getters
int String_Getters::getAscii(char chr)
{
    return int(chr);
}

// Removers
string String_Removers::removeRangesFromString(string text, vector<Range> ranges)
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

// Converters
string String_Converters::convertLowercase(string tolowercase)
{
    string retString = "";

    for (char c : tolowercase)
    {
        retString += tolower(c);
    }

    return retString;
}

string String_Converters::convertUppercase(string tolowercase)
{
    string retString = "";

    for (char c : tolowercase)
    {
        retString += toupper(c);
    }

    return retString;
}