#pragma once
#include<string>
#include<map>
#include <iostream>
#include <iterator>

using namespace std;
struct content{
	string type;
};

class SymbolTable
{
private:
	map<string,content> sym;
public:
	SymbolTable(void);
	void addTokenType(string, string);
	string retriveTokenType(string);
	void updateTokenType(string, string);
	~SymbolTable(void);
};

