#pragma once


#include <iostream>
#include <string>

using namespace std;


namespace ConsoleUtils {
	void printLn(string msg) { cout << msg << endl; }

	void error(string out);
	void error(char out);
};