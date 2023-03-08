#include "ConsoleUtils.h"


void ConsoleUtils::printLn(string msg) {
	cout << endl << msg << endl;
}

void ConsoleUtils::printLn(char msg) {
	cout << endl << msg << endl;
}

void ConsoleUtils::printLn(int msg) {
	cout << endl << to_string(msg) << endl;
}

void ConsoleUtils::error(string out) {
	cerr << out;
}

void ConsoleUtils::error(char out) {
	cerr << out;
}