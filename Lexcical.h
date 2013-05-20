#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <vector>
#include <iterator>


using namespace std; // not a good way


enum ttype
{
	ID = 0,
	NUM = 1,
	RELOP = 2,
	ADDOP = 3,
	MULOP = 4,
	ASSIGNOP = 5,
	COMT = 6,
	DELIM = 7,
	PUN = 8,
	Keyword = 9,
	NONE = 10
};
struct Tok
{
	ttype type;
	string str;
	int lenght;
};
const int bufSize= 1003;
const int bufMidSentinal = 500;
const int bufEndSentinal = 1001;

class Lexcical
{
private:
	char buffer[bufSize];
	static int side; //init to 1
	static int filePtrLoc;// init to 0
	string fLoc;// file location
	int errorNo;
	int TokenNo;
public:
	Lexcical(void);
	~Lexcical(void);
	// helper Methods
	void fillBuff(char*,char*,int,int);
	bool isKeyword(string);
	void readbuff(char*,int&);
	bool isAlltypeNONE(Tok *tt[],int);
	char* strncopy(char*,int,int);
	char* tokentype(ttype);
	void fileTok(const Tok*,int);
	void notASymbol(char);
	int findLongStr(Tok *t[],int);
	void lexRunner();
	void takeFile();// not used
	// helper methods
	//DFA Methods
	Tok* dfaAddop(char*,int&);
	Tok* dfaDelim(char*, int&);
	Tok* dfaIdentifier(char*,int&);
	Tok* dfaEqulTo(char*,int&);
	Tok* dfaRelop(char*,int&);
	Tok* dfaNumber(char*,int&);
	Tok* dfaMulop(char*,int&);
	Tok* dfaPun(char*, int&);
	Tok* dfaComment(char*,int&);
	//DFA MEthods
	// getter
	long int getErrorNo() const;
};

