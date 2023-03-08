#include "./Headers/FileUtils.h"


string FileUtils::GetFileText(string FilePath) {
    ifstream input_file("../Example.flang");

    if (!input_file) { error("Invalid file path!"); return 0; }

    input_file.seekg(0, input_file.end);
    int length = input_file.tellg();
    input_file.seekg(0, input_file.beg);

    char* buffer = new char[length];

    input_file.read(buffer, length);

    string fileText(buffer, length);

    delete[] buffer;

    return fileText;
}