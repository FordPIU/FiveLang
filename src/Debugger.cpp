#include "Debugger.h"

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
memory_usage
    Paramters:
    0 - for Byte
    1 - for KB
    2 - for MB

    Nothing or Anything Else - for GB

tokens
----------------------------------------
        )");
        getline(cin, input);

        transform(input.begin(), input.end(), input.begin(), [](unsigned char c)
                  { return std::tolower(c); });

        // Splitter
        vector<string> splitCommand = splitWords(input, " ", false);
        string command = splitCommand[0];
        string arg1 = "-256";

        if (splitCommand.size() > 1)
        {
            arg1 = splitCommand[1];
        }

        // Command Handler
        if (command == "exit" || command == "quit")
        {
            printLn("\nExiting Program...");
            return 0;
        }
        else if (command == "memory_usage")
        {
            PROCESS_MEMORY_COUNTERS_EX pmc;
            GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS *)&pmc, sizeof(pmc));
            SIZE_T virtualMemUsedByMe = pmc.PrivateUsage;

            double memoryUsed;
            string unit;

            switch (stoi(arg1))
            {
            case 0: // B
                memoryUsed = static_cast<double>(virtualMemUsedByMe);
                unit = "B";
                break;
            case 1: // KB
                memoryUsed = static_cast<double>(virtualMemUsedByMe) / 1024;
                unit = "KB";
                break;
            case 2: // MB
                memoryUsed = static_cast<double>(virtualMemUsedByMe) / (1024 * 1024);
                unit = "MB";
                break;
            default: // GB
                memoryUsed = static_cast<double>(virtualMemUsedByMe) / (1024 * 1024 * 1024);
                unit = "GB";
                break;
            }

            printLn("Memory Usage: " + to_string(memoryUsed) + " " + unit);
        }
        else if (command == "tokens")
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