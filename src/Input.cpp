#include "Input.h"
#include "ConsoleUtils.h"
#include "FileUtils.h"
#include "StringUtils.h"

using namespace Prints;
using namespace File_Getters;
using namespace String_Combiners;
using namespace String_Splitters;
using namespace String_Checkers;
using namespace String_Removers;

Input::Input(string filePath)
{
    // Setup vars
    this->workingText = GetFileText(filePath) + "\n";

    // Call Methods for Cleaning & Adjusting
    this->RemoveCommentsFromWorking();
    this->AdjSemicolons();
    this->AdjSoLSpaces();
    // this->AdjAllSpaces();
    this->RemoveEmptyLines();
}

void Input::RemoveCommentsFromWorking()
{
    string workText = this->workingText;
    vector<Range> removalRanges;

    bool isWorking = false;
    string workType = "";
    int workStart = -1;

    // Register
    for (int i = 0; i < workText.length(); ++i)
    {
        // Char Vars
        char currentChar = workText[i];
        char nextChar = ' ';
        char prevChar = ' ';

        if (i > 0)
        {
            prevChar = workText[i - 1];
        }
        if (i < workText.length())
        {
            nextChar = workText[i + 1];
        }

        // Not Working
        if (!isWorking)
        {
            // Single Line Comment Opener
            if (currentChar == '/' && nextChar == '/')
            {
                isWorking = true;
                workType = "SLC";
                workStart = i;

                ++i;
                continue;
            }

            // Multi-Line Comment Opener
            if (currentChar == '/' && nextChar == '*')
            {
                isWorking = true;
                workType = "MLC";
                workStart = i;

                continue;
            }
        }
        else // Working
        {
            // Single Line Comment Slash Closer
            if (workType == "SLC" && (prevChar != '/' && currentChar == '/' && nextChar == '/'))
            {
                printLn(prevChar);
                removalRanges.push_back(Range(workStart, i + 1));

                isWorking = false;
                workType = "";
                workStart = -1;

                ++i;
                continue;
            }

            // Single Line Comment EOL Closer
            if (currentChar == '\n' && workType == "SLC")
            {
                removalRanges.push_back(Range(workStart, i - 1));

                isWorking = false;
                workType = "";
                workStart = -1;

                continue;
            }

            // Multi Line Comment Closer
            if (currentChar == '*' && nextChar == '/' && workType == "MLC")
            {
                removalRanges.push_back(Range(workStart, i + 1));

                isWorking = false;
                workType = "";
                workStart = -1;

                continue;
            }
        }
    }

    this->workingText = removeRangesFromString(workText, removalRanges);
}

void Input::RemoveEmptyLines()
{
    vector<string> lines = splitLines(this->workingText, '\n');
    vector<string> newLines;

    for (string &line : lines)
    {
        if (!line.empty())
        {
            newLines.push_back(line);
        }
    }

    string newText = combineLines(newLines, '\n');

    this->workingText = newText;
}

void Input::AdjSemicolons()
{
    string text = this->workingText;

    replace(text.begin(), text.end(), ';', '\n');

    this->workingText = text;
}

/// @brief SOL = Start of File
void Input::AdjSoLSpaces()
{
    vector<string> lines = splitLines(this->workingText, '\n');

    for (string &line : lines)
    {
        size_t pos = line.find_first_not_of(" ");

        if (pos != std::string::npos && pos > 0)
        {
            line = line.substr(pos);
        }
    }

    string newText = combineLines(lines, '\n');

    this->workingText = newText;
}

void Input::AdjAllSpaces()
{
    string newText = "";
    bool isInString = false;

    for (char current : this->workingText)
    {
        if (current != ' ' || isInString)
        {
            if (current == '"')
            {
                isInString = !isInString;
            }

            newText += current;
        }
    }

    this->workingText = newText;
}