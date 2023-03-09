#pragma once

#include "Utils.h"

using namespace Utils;


class TOKEN {
public:
	TOKEN(int wordNum) : wordNum(wordNum) {}

	int GetWordNumber() { return this->wordNum; }

	virtual void output_class() { printLn("Class contains no data to output"); }
	virtual void create_class() { error("Invalid Class Creator Method"); }

private:
	int wordNum;
};

class TOKEN_CLASS : public TOKEN {
public:
	TOKEN_CLASS(int wordNum, string defName) : TOKEN(wordNum), defName(defName) {}

	void output_class() override { printLn(this->GetTypeName() + " Name: " + this->defName); }

    string GetTypeName() { return "Class"; }
	string GetClassName() { return this->defName; }

private:
	string defName;
};

class TOKEN_THREAD : public TOKEN {
public:
	TOKEN_THREAD(int wordNum, string defName) : TOKEN(wordNum), defName(defName) {}

	void output_class() override { printLn(this->GetTypeName() + " Name: " + this->defName); }

    string GetTypeName() { return "Thread"; }
	string GetClassName() { return this->defName; }

private:
	string defName;
};

class TOKEN_FUNCTION : public TOKEN {
public:
	TOKEN_FUNCTION(int wordNum, string defHardType, string defName) : TOKEN(wordNum), defHardType(defHardType), defName(defName) {}

	void output_class() override { printLn(this->GetTypeName() + " Name: " + this->defName + "\nHard Type: " + this->defHardType); }

    string GetTypeName() { return "Function"; }
	string GetClassName() { return this->defName; }

private:
	string defName;
	string defHardType;
};

class TOKEN_VARIABLE : public TOKEN {
public:
	TOKEN_VARIABLE(int wordNum, string defHardType, string defName, string defValue) : TOKEN(wordNum), defHardType(defHardType), defName(defName), defValue(defValue) {}

	void output_class() override { printLn(this->GetTypeName() + " Name: " + this->defName + "\nHard Type: " + this->defHardType + "\nValue: " + this->defValue); }

    string GetTypeName() { return "Variable"; }
	string GetClassName() { return this->defName; }

private:
	string defName;
	string defHardType;
	string defValue;
};