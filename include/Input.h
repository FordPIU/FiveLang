#pragma once

#include "Common.h"
#include <algorithm>

class Input
{
public:
    Input(string filePath);

    string GetWorkingText() { return this->workingText; }

private:
    string workingText = "";

    void RemoveCommentsFromWorking();
    void RemoveEmptyLines();
    void AdjSemicolons();
    void AdjSoLSpaces();
    void AdjAllSpaces();
};