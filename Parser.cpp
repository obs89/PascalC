#include "Parser.h"


Parser::Parser(void)
{
	stk.push("$");
	stk.push("Program");
	loadTable();
	loadNonTearminals();
	loadTerminals();
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
		int row=0, col =0;
		file>>row;
		file>>col;
		for(int x = 0 ; x < row; x++)// 36
		{
			for(int y = 0 ; y < col ; y++) // 30
			{
				file>>pTable[x][y];
			}
		}
	}
	file.close();
}
void Parser::loadTerminals()
{
	fstream file;
	string tem;
	file.open("terminals.txt",ios::in);
	if (!file)
	{
		std::cout<<"file not found"<<endl;
		exit(0);
	}
	else
	{
		while(!file.eof())
		{
			file>>tem;
			terminals.push_back(tem);
		}
	}
	file.close();
}

void Parser::loadNonTearminals()
{
	fstream file;
	string tem;
	file.open("nonteminals.txt",ios::in);
	if (!file)
	{
		std::cout<<"file not found"<<endl;
		exit(0);
	}
	else
	{
		while(!file.eof())
		{
			file>>tem;
			nonTreminals.push_back(tem);
		}
	}
	file.close();
}

int Parser::findindex(vector<string> &a, string str)
{
	int r=-1;
	for (int i = 0; i < a.size() ; i++)
	{
		if (str == a[i])
		{
			r = i;
			break;
		}
	}
	return r;
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
			x = findindex(this->nonTreminals,stackTop);
			y = findindex(this->terminals,strTemp);
			if (x == -1 || y == -1)
				return -1;// error
			string s;
		/*	if (x == 18 && y == 1) //sp case
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
			{*/
				s  = pTable[x][y];// pick enter of the table
		//	}
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
