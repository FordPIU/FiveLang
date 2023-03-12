#pragma once

#include "Common.h"

namespace Prints
{
    void printLn(string msg);
    void printLn(char msg);
    void printLn(int msg);

    void printVc(string header, vector<string> list);
}

namespace Errors
{
    void error(string out);
    void error(char out);
}