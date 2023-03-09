#include <unordered_set>
#include <chrono>
#include <cctype>
#include <Windows.h>

#include "Utils.h"
#include "Lexer.h"
#include "Input.h"

using namespace Utils;
using namespace chrono;

void temp()
{
    Input input = Input("D:/Github/FiveLang/Examples/example.flang");
    printLn(input.GetWorkingText());
    while (true)
    {
    };
}

int main()
{
    temp();

    // Start Timer
    auto start_time = high_resolution_clock::now();

    // Set Window Size
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);
    MoveWindow(console, r.left, r.top, 2400, 1200, TRUE);

    // Lexer Test
    printLn("Starting Lexer Test!");

    string fileText = GetFileText("D:/Github/FiveLang/Examples/example.flang");
    Lexer lexer = Lexer(fileText);

    lexer.Lex();
    lexer.Tokenize();

    list<string> lines = lexer.GetCodeWords();
    auto end_time = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end_time - start_time).count();

    printLn("Finished Lexer Test! -- Took " + to_string(duration) + "ms to complete");

    string input;

    while (true)
    {
        printLn("\n---------------------\nEnter a new command:\nexit - Close the program.\nquit - Close the program.\n\nword_list - List of all words in lexer.\nline_list - List of all lines in lexer.\ntoken_list - List of all tokens in lexer.\n---------------------");
        getline(cin, input);

        transform(input.begin(), input.end(), input.begin(), [](unsigned char c)
                  { return std::tolower(c); });

        if (input == "exit" || input == "quit")
        {
            printLn("\nExiting Program...");
            return 0;
        }
        else if (input == "word_list")
        {
            list<string> word_list = lexer.GetCodeWords();
            for (auto it = word_list.begin(); it != word_list.end(); ++it)
            {
                printLn(*it);
            }
        }
        else if (input == "line_list")
        {
            list<string> line_list = lexer.GetCodeLines();
            for (auto it = line_list.begin(); it != line_list.end(); ++it)
            {
                printLn(*it);
            }
        }
        else if (input == "token_list")
        {
            list<TOKEN *> token_list = lexer.GetTokens();
            int i = 0;

            for (auto token : token_list)
            {
                i++;
                printLn("\nToken #: " + to_string(i));
                token->output_class();
            }
        }
        else
        {
            printLn("\nYou entered a unknown");
        }
    }

    printLn("\nExiting Program...");
}