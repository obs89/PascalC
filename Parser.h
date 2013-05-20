#pragma once
#include <stack>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <string.h>

using namespace std;
class Parser
{
private:
	string pTable[35][30];
	stack<string> stk;
	vector<string> pTok;
	void loadTable();

public:
	Parser(void);
	void readToken();
	int runParser();
	~Parser(void);
};

