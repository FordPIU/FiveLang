#include "ConsoleUtils.h"

void Prints::printLn(string msg)
{
    cout << msg << endl;
}

void Prints::printLn(char msg)
{
    cout << string(1, msg) << endl;
}

void Prints::printLn(int msg)
{
    cout << to_string(msg) << endl;
}

void Prints::printVc(string header, vector<string> list)
{
    printLn('\n');
    printLn(header);

    int i = 0;

    for (string str : list)
    {
        i++;
        printLn(to_string(i) + ": " + str);
    }

    printLn('\n');
}

void Errors::error(string out)
{
    cerr << out << endl;
    throw runtime_error(out);
}

void Errors::error(char out)
{
    cerr << out << endl;
    throw runtime_error(string(1, out));
}