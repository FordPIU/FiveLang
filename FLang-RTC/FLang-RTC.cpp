#include <unordered_set>
#include "Utils.h"
#include "Lexer.h"

using namespace Utils;

// C++ Main //
int main()
{
    string fileText = GetFileText("../Example.clang") + '\n';

    Lexer lexer = Lexer(fileText);

    lexer.Lex();

    list<string> lines = lexer.GetCodeLines();

    for (auto it = lines.begin(); it != lines.end(); ++it) {
        printLn(*it);
    }
}

// Added this comment just to test github actions