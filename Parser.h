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
	string pTable[36][30];
	stack<string> stk;
	vector<string> pTok;
	vector<string> terminals;
	vector<string> nonTreminals;
	void loadTable();
	void loadTerminals();
	void loadNonTearminals();

public:
	Parser(void);
	void readToken();
	int findindex(vector<string> &, string);
	int runParser();
	~Parser(void);
};

