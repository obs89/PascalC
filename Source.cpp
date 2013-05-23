#include "Lexcical.h"
#include "Parser.h"
#include "SymbolTable.h"
#include <conio.h>
int main ()
{
	Lexcical test;
	SymbolTable t;
	test.setT(&t);
	test.lexRunner();
	if (test.getErrorNo() > 0 )
	{
		cout<<endl<<"there are error(s) in your code, if u still want to run Parser press 1 ::";
		char a = _getche();
		if (a == '1')
		{
			cout<<endl<<"Parser is running....";
			Parser p;
			p.readToken();
		}
	}
	else
	{
		cout<<endl<<"Parser is running....";
		Parser p;
		p.readToken();
	}
	system("pause");
	return 0;
}



