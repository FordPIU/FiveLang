#include "FileUtils.h"


string FileUtils::GetFileText(string FilePath) {
    printLn("Loading File from " + FilePath);

    ifstream input_file(FilePath);

    if (!input_file) { error("Invalid file path!"); return 0; }

    input_file.seekg(0, input_file.end);
    int length = static_cast<int>(input_file.tellg());
    input_file.seekg(0, input_file.beg);

    char* buffer = new char[length];

    input_file.read(buffer, length);

    string fileText(buffer, length);

    delete[] buffer;

    return fileText;
}