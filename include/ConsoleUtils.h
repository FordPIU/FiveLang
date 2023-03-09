#pragma once

#include "CommonLibs.h"

namespace ConsoleUtils
{
	void printLn(string msg);
	void printLn(char msg);
	void printLn(int msg);

	void error(string out);
	void error(char out);
};