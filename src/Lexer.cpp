#include "Lexer.h"

class SurroudingWords
{
public:
	vector<string> forward;
	vector<string> backward;
	string middle;

	void Get(int depth, list<string>::iterator it, list<string> &lst)
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
};

Lexer::Lexer(string rawFileText)
{
	// Init the values
	this->fileText = "";
	this->fileTextLength = 0;

	// Empty check
	if (rawFileText.empty())
	{
		error("Invalid File Text!");
		return;
	}

	// Actually set
	this->fileText = rawFileText;
	this->fileTextLength = static_cast<int>(rawFileText.length());
}

void Lexer::Lex()
{
	this->codeText = this->fileText;
	this->codeTextLength = this->fileTextLength;
	this->Lexed = true;

	this->ChunkifyByLine();
	this->ChunkifyByWords();
}

void Lexer::Tokenize()
{
	if (!this->Lexed)
	{
		error("You did not lex yet!");
		return;
	}

	for (auto it = this->codeWords.begin(); it != this->codeWords.end(); ++it)
	{
		int i = static_cast<int>(distance(this->codeWords.begin(), it));
		SurroudingWords surrounding = SurroudingWords();
		surrounding.Get(5, it, this->codeWords);

		printLn("\nCurrent Word: " + surrounding.middle);
		printLn("Previous Word #1: " + surrounding.backward[0]);
		printLn("Previous Word #2: " + surrounding.backward[1]);
		printLn("Previous Word #3: " + surrounding.backward[2]);
		printLn("Previous Word #4: " + surrounding.backward[3]);
		printLn("Previous Word #5: " + surrounding.backward[4]);
		printLn("Next Word #1: " + surrounding.forward[0]);
		printLn("Next Word #2: " + surrounding.forward[1]);
		printLn("Next Word #3: " + surrounding.forward[2]);
		printLn("Next Word #4: " + surrounding.forward[3]);
		printLn("Next Word #5: " + surrounding.forward[4]);

		// TOKEN_CLASS newToken = TOKEN_CLASS(i, "r" + to_string(i));
		// newToken.create_class();
	}
}

void Lexer::ChunkifyByLine()
{
	list<string> lineList;
	string workingLine = "";
	bool workingLineFoundChar = false;

	for (int i = 0; i < this->codeTextLength; ++i)
	{
		char currentChar = this->codeText[i];

		if (currentChar == ';' || currentChar == '\n' || i == this->codeTextLength)
		{
			if (!workingLine.empty())
			{
				lineList.push_back(workingLine);
			}

			workingLine = "";
			workingLineFoundChar = false;
		}
		else
		{
			if (currentChar == ' ' && workingLineFoundChar == false)
			{
				continue;
			}
			else
			{
				workingLineFoundChar = true;
			}

			workingLine += currentChar;
		}
	}

	this->codeLines = lineList;
}

void Lexer::ChunkifyByWords()
{
	list<string> wordsList;
	string delimiters = " ,;({})\n";

	for (auto it = this->codeLines.begin(); it != this->codeLines.end(); ++it)
	{
		string lineText = *it;
		string token;
		size_t pos = 0;

		while (pos < lineText.length())
		{
			size_t nextDelimiterPos = lineText.find_first_of(delimiters, pos);

			if (nextDelimiterPos == string::npos)
			{
				token = lineText.substr(pos);
				pos = lineText.length();
			}
			else
			{
				token = lineText.substr(pos, nextDelimiterPos - pos);
				pos = nextDelimiterPos + 1;
			}

			if (!token.empty())
			{
				wordsList.push_back(token);
			}

			if (nextDelimiterPos != string::npos)
			{
				string delimiter = lineText.substr(nextDelimiterPos, 1);

				if (delimiter != "\n" && delimiter != " ")
				{
					wordsList.push_back(delimiter);
				}
			}
		}
	}

	this->codeWords = wordsList;
}

void Lexer::newText(string newText)
{
	this->codeText = newText;
	this->codeTextLength = static_cast<int>(newText.length());
}