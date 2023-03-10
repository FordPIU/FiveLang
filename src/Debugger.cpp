#include <unordered_set>
#include <chrono>
#include <cctype>
#include <Windows.h>

#include "Utils.h"
#include "Lexer.h"
#include "Input.h"

using namespace Utils;
using namespace chrono;

int main()
{
    // Start Timer
    auto start_time = high_resolution_clock::now();

    // Set Window Size
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);
    MoveWindow(console, r.left, r.top, 2400, 1200, TRUE);

    // Lexer Test
    printLn("Starting Lexer Test!");

    Input fIn = Input("D:/Github/FiveLang/Examples/example.flang");
    Lexer fLex = Lexer(fIn);

    auto end_time = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end_time - start_time).count();

    printLn("Finished Lexer Test! -- Took " + to_string(duration) + "ms to complete");

    string input;

    while (true)
    {
        printLn(R"(
----------------------------------------
    Please enter your next command...

           Available Commands:
exit
quit
list
----------------------------------------
        )");
        getline(cin, input);

        transform(input.begin(), input.end(), input.begin(), [](unsigned char c)
                  { return std::tolower(c); });

        if (input == "exit" || input == "quit")
        {
            printLn("\nExiting Program...");
            return 0;
        }
        else if (input == "list")
        {
            vector<TOKEN *> token_list = fLex.getTokens();
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