#include "Parser.h"


Parser::Parser(void)
{
	stk.push("$");
	stk.push("Program");
	loadTable();
}

void Parser::loadTable()
{
	fstream file;
	file.open("parse.txt",ios::in);
	if (!file)
	{
		std::cout<<"file not found"<<endl;
		exit(0);
	}
	else
	{
		for(int x = 0 ; x < 35; x++)
		{
			for(int y = 0 ; y < 30 ; y++)
			{
				file>>pTable[x][y];
			}
		}
	}
	file.close();
}

void Parser::readToken(){
	fstream file;
	string tem;
	file.open("Tstream.txt",ios::in);
	if(!file){
		cout<<"File could not be written"<<endl;
		exit(0);
	}
	else{
		while (!file.eof())
		{
			file>>tem;
			pTok.push_back(tem);
		}
		pTok.pop_back();
		pTok.push_back("$");
	}
	int test= runParser();
	if (test == -1)
	{
		cout<<endl<<"Error :: ur program could not be parsed"<<endl;
	}
	else if (test == 0)
	{
		cout<<endl<<"Progaram Parsed!"<<endl;
	}

}

int Parser::runParser()
{
	//const int i= 0;
	while(true)
	{
		string strTemp = pTok.front();
		string stackTop = stk.top();
		if (strTemp == "$" && stackTop == "$")// empty stack
		{
				return 0; // parsed
		}
		else if (strTemp == stackTop)// terminal matched
		{
			pTok.erase(pTok.begin());
			stk.pop();
		}
		else
		{
			int x= -1, y = -1;
			string terminals[30]={"program", "id", "var", "integer", "real" ,"array","function"
								 ,"procedure","begin", "while", "if", "else", "num" ,"not", "relop"
								 , "addop","mulop", "end", "assignop", "do", "then", "[", "]", "+"
								 , "-","(",")", ":" ,",",";" };
			int n=0;
			while(n<30){
				if(strTemp == terminals[n]){
					y=n;
					break;
				}
				n++;
			}

			string non_terminals[35]={"Program","identifier_list","IDL'","declarations","D'","type","standard_type",
									  "subprogram_declarations","SPD'","subprogram_declaration","subprogram_head",
									  "arguments","parameter_list","PL'","compound_statement","optional_statements",
									  "statement_list","SL'","statement","ST'","variable","V'","procedure_statement","PS'",
									  "expression_list","EL'","expression","EX'","simple_expression","SE'","term","T'","factor"
									  ,"F'","sign"};
			int i=0;
			while(i<36){
				if(stackTop==non_terminals[i]){
					x=i;
					break;
				}
				i++;
			}
			if (x == -1 || y == -1)
				return -1;// error
			string s;
			if (x == 18 && y == 1) //sp case
			{
				string tstr = pTable[x][y];
				char tt[150];
				int q;
				for ( q = 0 ; q < tstr.length(); q++)
						tt[q]=tstr[q];
				tt[q]= '\0';
				if (pTok[1]== "assignop")
				{
					s = strtok(tt,"|");
				}
				else
				{
					strtok(tt,"|");
					s = strtok(NULL,"|");
				}

			}
			else
			{
				s  = pTable[x][y];// pick enter of the table
			}
			if (s == "^")
				return -1;// error or empty entry
			else if (s == "!")
				stk.pop();
			else{
				
				char tt[150];
				int q;
				for ( q = 0 ; q < s.length(); q++)
						tt[q]=s[q];
				tt[q]= '\0';
				vector<string> temp;
				char * c = new char[60];
				string str1 = strtok(tt,"@");
				temp.push_back(str1);
				while(true){
					c = strtok(NULL,"@");
					if (c == NULL)
							break;
					str1 = c;
					temp.push_back(str1);
				}
				stk.pop();
				for (int it = temp.size()-1; it >= 0 ; it--)
					stk.push(temp[it]);
			}
		
		}
	}
	return -1;// exit due to unnkown reason
}

Parser::~Parser(void)
{
}
