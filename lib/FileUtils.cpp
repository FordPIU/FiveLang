#include "FileUtils.h"
#include "ConsoleUtils.h"

string File_Getters::GetFileText(string FilePath)
{
    Prints::printLn("Loading File from " + FilePath);

    ifstream input_file(FilePath);

    if (!input_file)
    {
        Errors::error("Invalid file path!");
        return 0;
    }

    input_file.seekg(0, input_file.end);
    int length = static_cast<int>(input_file.tellg());
    input_file.seekg(0, input_file.beg);

    char *buffer = new char[length];

    input_file.read(buffer, length);

    string fileText(buffer, length);

    delete[] buffer;

    return fileText;
}

void Test()
{
    vector<string> test = {};
}