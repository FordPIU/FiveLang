#pragma once


#include <iostream>
#include <string>

using namespace std;


namespace ConsoleUtils {
	void printLn(string msg) { cout << msg << endl; }
	void printLn(char msg) { cout << msg << endl; }
	void printLn(int msg) { cout << msg << endl; }

	void error(string out);
	void error(char out);
};