#pragma once

#include "Common.h"

class Definition
{
public:
	Definition() : name(""), type(""), value("") {}
	Definition(string name, string type, string value) : name(name), type(type), value(value) {}

	string name;
	string type;
	string value;
};

class Token
{
public:
	Token(int wordNum, string tokenType,
		  string defName, string defType, string defValue)
	{
		this->tokenPosition = wordNum;
		this->tokenType = tokenType;
		this->tokenDefinition = Definition(defName, defType, defValue);
	}

	int tokenPosition;
	string tokenType;
	Definition tokenDefinition;
};