#include <unordered_set>
#include <Windows.h>

#include "Utils.h"
#include "Lexer.h"

using namespace Utils;

int main()
{

    // Set Window Size
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);
    MoveWindow(console, r.left, r.top, 2400, 1200, TRUE);

    // Lexer Test
    printLn("Starting Lexer Test!");

    string fileText = GetFileText("D:/Github/FiveLang/Examples/example.flang") + '\n';

    Lexer lexer = Lexer(fileText);

    lexer.Lex();

    list<string> lines = lexer.GetCodeWords();

    for (auto it = lines.begin(); it != lines.end(); ++it) {
        printLn(*it);
    }

    printLn("Finished Lexer Test!");

    // Linger to keep window open
    while(true){}
}