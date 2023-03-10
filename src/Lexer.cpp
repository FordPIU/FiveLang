#include "Lexer.h"

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
	vector<string> words = splitWords(inputText, "\n{()}[]+=-,<.>", true);

	for (auto it = words.begin(); it != words.end(); ++it)
	{
		int i = static_cast<int>(distance(words.begin(), it));
		SurroudingWords surrounding = SurroudingWords(5, it, words);
		printLn("Current: " + surrounding.middle);
		printVc("Next 5", surrounding.forward);
		printVc("Prev 5", surrounding.backward);
	}
}