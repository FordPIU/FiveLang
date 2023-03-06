#pragma once


#include <iostream>
#include <string>

using namespace std;

namespace ConsoleUtils {
	template<typename... Args>
	void printLn(Args&&... args) {
		(cout << ... << args) << endl;
	}

	void error(string out);
	void error(char out);
};