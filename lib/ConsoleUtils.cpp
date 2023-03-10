#include "ConsoleUtils.h"

void ConsoleUtils::printLn(string msg)
{
	cout << msg << endl;
}

void ConsoleUtils::printLn(char msg)
{
	cout << string(1, msg) << endl;
}

void ConsoleUtils::printLn(int msg)
{
	cout << to_string(msg) << endl;
}

void ConsoleUtils::printVc(string header, vector<string> list)
{
	printLn('\n');
	printLn(header);

	int i = 0;

	for (string str : list)
	{
		i++;
		printLn(to_string(i) + ": " + str);
	}

	printLn('\n');
}

void ConsoleUtils::error(string out)
{
	cerr << out << endl;
	throw runtime_error(out);
}

void ConsoleUtils::error(char out)
{
	cerr << out << endl;
	throw runtime_error(string(1, out));
}