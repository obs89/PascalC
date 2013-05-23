#include "SymbolTable.h"


SymbolTable::SymbolTable(void)
{
}

void SymbolTable::addTokenType(string key,string type)
{
	sym[key].type = type;
}

string SymbolTable::retriveTokenType(string key)
{
	string r;
	if (sym.count(key) == 1)
		r = sym.find(key)->second.type;
	 return r;
}
void SymbolTable::updateTokenType(string key, string nVal)
{
		int t= sym.count(key);
		if (t == 1)
		{
			sym[key].type = nVal;
		}
		else
		{
			cout<<endl<<"update fail due to no key found"<<endl;
		}

}
SymbolTable::~SymbolTable(void)
{
}
