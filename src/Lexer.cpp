#include "Lexer.h"
#include "Defaults.h"
#include "ConsoleUtils.h"
#include "StringUtils.h"

using namespace Defaults;
using namespace Errors;
using namespace String_Splitters;
using namespace String_Checkers;

class SurroudingWords
{
public:
	SurroudingWords(int depth, vector<string>::iterator it, vector<string> &lst)
	{
		auto prevIt = it;
		auto nextIt = it;

		this->middle = *it;

		for (int i = 0; i < depth; ++i)
		{
			this->forward.push_back("");
			this->backward.push_back("");
		}

		for (int i = 0; i < depth; ++i)
		{
			if (nextIt == lst.end())
			{
				break;
			}
			else
			{
				++nextIt;
			}
			this->forward[i] = (nextIt == lst.end()) ? "" : *nextIt;
		}

		for (int i = 0; i < depth; ++i)
		{
			if (prevIt == lst.begin())
			{
				break;
			}
			else
			{
				--prevIt;
			}
			this->backward[i] = *prevIt;
		}
	}

	vector<string> forward;
	vector<string> backward;
	string middle;
};

Lexer::Lexer(Input fileInput)
{
	string inputText = fileInput.GetWorkingText();
	vector<string> words = splitWords(inputText, "\n{()}[]+=-,<.> ", true);
	int skip = 0;

	for (auto it = words.begin(); it != words.end(); ++it)
	{
		if (skip > 0)
		{
			skip--;
			continue;
		}

		int i = static_cast<int>(distance(words.begin(), it));
		SurroudingWords surrounding = SurroudingWords(5, it, words);
		string current = surrounding.middle;
		vector<string> next = surrounding.forward;
		vector<string> prev = surrounding.backward;

		// Class
		if (current == "class")
		{
			// Validate
			if (checkHasNoCharacterInString(next[0]) && next[1] == "{")
			{
				tokens.push_back(new Token(i, "CLASS", next[0], DEF_NO_TYPE, DEF_NO_VALUE));

				skip += 2;
				continue;
			}
		}

		// Thread
		else if (current == "thread")
		{
			// Validate
			if (checkHasNoCharacterInString(next[0]) && next[1] == "(")
			{
				tokens.push_back(new Token(i, "THREAD", next[0], DEF_NO_TYPE, DEF_NO_VALUE));

				skip += 2;
				continue;
			}
		}

		// Function
		else if (current == "function")
		{
			// Validate
			if (checkHasNoCharacterInString(next[0]) && next[1] == "(")
			{
				tokens.push_back(new Token(i, "FUNCTION", next[0], DEF_NO_TYPE, DEF_NO_VALUE));

				skip += 2;
				continue;
			}
			else if (next[0] == "{" && next[2] == "}" && checkHasNoCharacterInString(next[3]) && next[4] == "(")
			{
				tokens.push_back(new Token(i, "FUNCTION", next[3], next[1], DEF_NO_VALUE));

				skip += 5;
				continue;
			}
		}

		// Variable
		/*else if (current == "var")
		{
			// Validate
			if (!checkHasNoCharacterInString(next[0]))
			{
				error("Invalid Variable Declaration @ Word #" + to_string(i));
			}

			string defName = next[0];
			string defValue = Defaults::DEF_NO_VALUE;
			string defType = Defaults::DEF_NO_TYPE;

			if (next[1] == "=")
			{
				defValue = next[2];

				skip += 2;
			}
			else if (next[1] == "{" && next[3] == "}")
			{
				defType = next[2];

				if (next[4] == "=")
				{
					defValue = next[5];

					skip += 2;
				}

				skip += 3;
			}

			skip += 2;
			continue;
		}*/
	}
}