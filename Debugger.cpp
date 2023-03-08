#include <unordered_set>

#include "UtilsMaster.h"
#include "Lexer.h"

using namespace Utils;

// C++ Main //
int main()
{
    string fileText = GetFileText(".Examples/example.clang") + '\n';

    Lexer lexer = Lexer(fileText);

    lexer.Lex();

    list<string> lines = lexer.GetCodeLines();

    for (auto it = lines.begin(); it != lines.end(); ++it) {
        printLn(*it);
    }
}