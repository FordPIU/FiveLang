#pragma once

#include "CommonLibs.h"

namespace ConsoleUtils
{
	void printLn(string msg);
	void printLn(char msg);
	void printLn(int msg);

	void printVc(string header, vector<string> list);

	void error(string out);
	void error(char out);
};