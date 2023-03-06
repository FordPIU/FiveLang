#include <unordered_set>
#include "Utils.h"

using namespace Utils;

/*
Start
|
v
Read next character
|
v
While there are characters left to process:
|
v
Skip whitespace
|
v
Check if character is a special symbol or keyword
|
v
If yes, add corresponding token to list and move to next character
|
v
If no, check if character is part of identifier or literal
|
v
If part of identifier or literal, continue reading until non-identifier/non-literal character is found
|
v
Add corresponding token to list and move to next character
|
v
End while loop
|
v
Add EOF token to list
|
v
Return token list
|
End
*/

struct Token {
    string type;
    string text;
    int charNum;
};

// Lexer //
class Lexer {
public:
    Lexer(string rawFileText) {
        this->rawFileText = rawFileText;
    }

    list<Token> Tokenize() {
        list<Token> tokenList;

        if (this->rawFileText.empty()) {
            error("Invalid file text!");
            return tokenList;
        }

        for (int i = 0; i < this->rawFileText.length(); ++i) {
            char currentChar = this->rawFileText[i];

            // Whitespace check
            if (currentChar == ' ') { continue; }

            // Single Character Operators
            switch (currentChar) {
            case '.':
                Token token;
                token.type = "OPERATOR_THIS";
                token.charNum = i;

                bool found = false;
                string text;
                tie(found, text) = findVariable(this->rawFileText, i);

                if (!found) { continue; }

                token.text = "."+text;

                tokenList.push_back(token);
                break;
            }
        }

        return tokenList;
    }

private:
    string rawFileText;
    int charPtrPos = 0;

    pair<bool, string> findVariable(const string& input, int startingPosition = 0) {
        bool found = false;
        string result;
        size_t pos = startingPosition;
        while (pos < input.length()) {
            // Check for variable name starting with a dot
            if (input[pos] == '.' && pos + 1 < input.length() && isalpha(input[pos + 1])) {
                size_t name_start = pos + 1;
                ++pos;
                while (pos < input.length() && (isalnum(input[pos]) || input[pos] == '_')) {
                    ++pos;
                }
                if (pos < input.length() && (input[pos] == ' ' || input[pos] == '\n' || input[pos] == '=')) {
                    result = input.substr(name_start, pos - name_start);
                    found = true;
                }
            }
            // Check for value after equal sign
            else if (found && input[pos] == '=') {
                size_t value_start = pos + 1;
                ++pos;
                while (pos < input.length() && input[pos] != '\n') {
                    ++pos;
                }
                string value = input.substr(value_start, pos - value_start);
                // Trim leading and trailing whitespace from value
                value.erase(0, value.find_first_not_of(" \t\n\r\f\v"));
                value.erase(value.find_last_not_of(" \t\n\r\f\v") + 1);
                result += " = " + value;
                break;
            }
            else {
                ++pos;
            }
        }
        return make_pair(found, result);
    }
};


// C++ Main //
int main()
{
    string fileText = GetFileText("../Example.clang");
    // Lexer Tokenization
    Lexer lexe = Lexer(fileText);
    list<Token> tokens = lexe.Tokenize();

    for (auto token : tokens) {
        printLn("Token Type:", token.type);
        printLn("Text:", token.text);
        printLn("Char #:", token.charNum);
    }
}