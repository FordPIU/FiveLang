#pragma once

#include "Utils.h"

using namespace Utils;


class Token {
public:
	Token(int wordNum) : wordNum(wordNum) {}

	int GetWordNumber() { return this->wordNum; }

	virtual void output_class() { printLn("Class contains no data to output"); }

private:
	int wordNum;
};

class TOKEN_CLASS : public Token {
public:
	TOKEN_CLASS(int wordNum, string defName) : Token(wordNum), defName(defName) {}

	void output_class() override { printLn(this->GetTypeName() + " Name: " + this->defName); }

    string GetTypeName() { return "Class"; }
	string GetClassName() { return this->defName; }

private:
	string defName;
};

class TOKEN_THREAD : public Token {
public:
	TOKEN_THREAD(int wordNum, string defName) : Token(wordNum), defName(defName) {}

	void output_class() override { printLn(this->GetTypeName() + " Name: " + this->defName); }

    string GetTypeName() { return "Thread"; }
	string GetClassName() { return this->defName; }

private:
	string defName;
};