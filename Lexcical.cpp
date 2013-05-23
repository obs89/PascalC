#include "Lexcical.h"



Lexcical::Lexcical(void):fLoc("test.pcl"),errorNo(0),TokenNo(0){
	//buffer[bufSize]="";
	buffer[bufMidSentinal]= (char)23;
	buffer[bufEndSentinal] = (char)23;
}
int Lexcical::side = 1;
int Lexcical::filePtrLoc = 0;
long int Lexcical::getErrorNo() const
{
	return errorNo;
}

Lexcical::~Lexcical(void)
{
}

void Lexcical::fillBuff(char *des,char *sur,int dSt, int dEd)
{
		int ii=0, i = 0;
		for (i = dSt,ii=0; i <= dEd && sur[ii] != 16; i++, ii++)// <= to <
		{
			des[i]=sur[ii];
		}
		des[i] = '\0';
}
bool Lexcical::isKeyword(string s)
{
	string keywrd[16] = { "program", "if", "then","else", "do" ,
						  "while", "integer", "real","function",
						  "procedure","begin", "end", "not","var", "array" , "of"};
	for each (string var in keywrd)
	{
		if (s == var)
			return true;
	}
	return false;
}
void Lexcical::readbuff(char *buff, int &reset){
	fstream file;
	const int mid = 500;
	file.open(fLoc,ios::in);
	if (!file){
		cout<<"file not found"<<endl;
		exit(0);
	}
	else{
		file.seekg(0, file.end);
		int temp = file.tellg();
		unsigned int fileSize = temp - filePtrLoc;
		char *tempBuff = new char[mid];
		for (int i = 0; i < mid; i++)
		{
			tempBuff[i]= 16;
		}
		file.seekg(filePtrLoc);
		if (side == 1){
			if (fileSize >= mid){
				file.read(tempBuff,mid);
				fillBuff(buff,tempBuff,0,499);
				side = 2;
				filePtrLoc += mid;
			}
			else{
				file.read(tempBuff,fileSize);
				fillBuff(buff,tempBuff,0,fileSize-1);
				side = 2;
				filePtrLoc += mid;
			}
		}
		else if (side == 2 ){
			if (fileSize >= mid){
				file.read(tempBuff,mid);
				fillBuff(buff,tempBuff,501,1000);
				side = 1;
				filePtrLoc += mid;
				reset=0;
			}
			else{
				file.read(tempBuff,fileSize);
				fillBuff(buff,tempBuff,501,fileSize-1);
				side = 1;
				filePtrLoc += mid;
				reset=0;
			}
		}

	}
	file.close();

}
char* Lexcical::strncopy(char *str,int s, int e)
{
	char *tstr= new char[e-s];
	int ii=0;
	for (int i = s; i < e; i++, ii++)
	{
		tstr[ii] = str[i];
	}
	tstr[ii]= '\0';
	return tstr;
}
bool Lexcical::isAlltypeNONE(Tok *tt[], int num){
	
	for (int i = 0; i < num; i++)
	{
		if (tt[i]->lenght != 0)
			return false;
	}
	return true;
}
char* Lexcical::tokentype(ttype tp)
{
	char * rt = new char[8];
	switch (tp)
	{
	case ID:
		strcpy(rt,"id");
		break;
	case NUM:
		strcpy(rt,"num");
		break;
	case RELOP:
		strcpy(rt,"relop");
		break;
	case ADDOP:
		strcpy(rt,"addop");
		break;
	case MULOP:
		strcpy(rt,"mulop");
		break;
	case ASSIGNOP:
		strcpy(rt,"assignop");
		break;
	case COMT:
		strcpy(rt,"COMT");
		break;
	case DELIM:
		strcpy(rt,"DELIM");
		break;
	case PUN:
		strcpy(rt,"PUN");
		break;
	case Keyword:
		strcpy(rt,"KEYWORD");
		break;
	case NONE:
		strcpy(rt,"NONE");
		break;
	}
	return rt;
}
void Lexcical::fileTok(const Tok *t, int len){

	if (t->type != NONE	){
		fstream file;
		file.open("Tstream.txt",ios::out | ios::app );
		if(!file){
			cout<<"File could not be written"<<endl;
			exit(0);
		}
		else{
			if (t->type == ID || t->type == ADDOP || t->type == MULOP || t->type == RELOP || t->type == NUM || t->type == ASSIGNOP)
			{
				file<<tokentype(t->type)<<endl;
				//file.ignore(256,'\n');
			}
			else if ( t->type == PUN || t->type == Keyword)
			{
				file<<t->str<<endl;
				//file.ignore(256,'\n');
			}
			if (t->type == ID)
			{
				T->addTokenType(t->str,tokentype(t->type));
			}
			TokenNo++;
		}
/*
		fstream file;
		file.open("token.txt",ios::out | ios::app );
		if(!file){
			cout<<"File could not be written"<<endl;
			exit(0);
		}
		else{
			file<<setw(10)<<t->str<<setw(10)<<t->lenght<<setw(10)<<tokentype(t->type)<<endl;
			TokenNo++;
		}
		file.close();*/
	}
	else if(t->type == NONE	){
		fstream file;
		file.open("errors.txt",ios::out | ios::app );
		if(!file){
			cout<<"File could not be written"<<endl;
			exit(0);
		}
		else{
  			file<<setw(10)<<t->str<<setw(10)<<t->lenght<<setw(10)<<tokentype(t->type)<<setw(10)<<" Error announced by DFA No :: "<<len<<endl;
			errorNo++;
		}
		file.close();
		
	}
}

void Lexcical::setT(SymbolTable *a)
{
	T = a;
}
void Lexcical::notASymbol(char ch){
	fstream file;
	file.open("errors.txt",ios::out | ios::app );
	if(!file){
		cout<<"File could not be written"<<endl;
		exit(0);
	}
	else{
  		file<<setw(10)<<ch<<setw(10)<<"  NOT A Symbol of Pascal Language"<<endl;
		errorNo++;
	}
	file.close();
}
int Lexcical::findLongStr(Tok *t[], int num){// need major fix in v0.3 
	int lng = -1;
	int rt=-1;
	for (int i = 0; i < num; i++){
		if (t[i]->lenght > lng){
			lng = t[i]->lenght;
			rt= i;
		}
	}
	return rt;
	/*vector <Tok> ttmp;
	for (int i = 0; i < num; i++){
		if (t[i]->lenght != 0){
			ttmp.push_back(*t[i]);
		}
	}*/

}
void Lexcical::lexRunner()
{
	const int num = 9;
	int len;
	Tok *tt[num];
	int bufPointer= 0;
	int bufStart = 0; 
	cout<<"File tokenization of "<<fLoc<<" has been started!!!"<<endl;
	readbuff(buffer,bufPointer);
	while (buffer[bufPointer] != '\0'){
		tt[0] = dfaPun(buffer,bufPointer);
		bufPointer = bufStart;
		tt[1] = dfaNumber(buffer,bufPointer);
		bufPointer = bufStart;
		tt[2] = dfaDelim(buffer,bufPointer);
		bufPointer = bufStart;
		tt[3] = dfaIdentifier(buffer,bufPointer);
		bufPointer = bufStart;
		tt[4] = dfaRelop(buffer,bufPointer);
		bufPointer = bufStart;
		tt[5] = dfaEqulTo(buffer,bufPointer); 
		bufPointer = bufStart;
		tt[6] = dfaAddop(buffer,bufPointer);
		bufPointer = bufStart;
		tt[7] = dfaMulop(buffer,bufPointer);
		bufPointer = bufStart;
		tt[8] = dfaComment(buffer,bufPointer);
		bufPointer = bufStart;
		
		len = findLongStr(tt,num);
		
		if (isAlltypeNONE(tt,num)){
			notASymbol(buffer[bufStart]);
			bufStart = ++bufPointer;
		}
		else{
			fileTok(tt[len],len);
			bufPointer += tt[len]->lenght;
			bufStart = bufPointer;
		}	
	}
	cout<<"****************************************"<<endl;
	cout<<"File Containing vaild Tokens stream:: Tstream.txt"<<"\tToken found ::"<<TokenNo<<endl;
	cout<<"File Containing Errors :: errors.txt"<<"\tError found ::"<<errorNo<<endl;
	cout<<"These files have been palced in working dir..."<<endl;
}
void Lexcical::takeFile()
{
	cout<<"Enter file name to parse ::";
	cin>>fLoc;
}

Tok* Lexcical::dfaAddop(char *input, int &i){
	char dfa[9][9] ={   "01234000",
						"77717717",
						"77727727",
						"71234737",
						"77777577",
						"77767767",
						"77767767",
						"77777777",
					};

	int x=0,y=0;// start state
	int countLenght=0;// counter
	string tmp;
	while (true){	
		if(input[i]=='+'){
			y=1;
			x=dfa[x][y]-48;
			countLenght++;
			tmp += input[i];
		}
		else if(input[i]=='-'){
			y=2;
			x=dfa[x][y]-48;
			countLenght++;
			tmp += input[i];
		}
		else if(input[i]=='o'){
			y=4;
			x=dfa[x][y]-48;
			countLenght++;
			tmp += input[i];
		}
		else if(input[i]=='r'){
			y=5;
			x=dfa[x][y]-48;
			countLenght++;
			tmp += input[i];
		}
		else if(input[i]==23){
			readbuff(input,i);
		}
		else{
			break;
		}
		i++;
	}
	Tok *t = new Tok;
	if(x==1 || x==2  || x==5  ){
		t->type= ADDOP;
		t->lenght=countLenght;
		t->str = tmp;
		return t;
	}
	else{
		t->type= NONE;
		t->str = tmp;
		if ( countLenght ==  1 && !( tmp.compare("+") == 0 || tmp.compare("-") == 0) )
			t->lenght=0;
		else
			t->lenght=countLenght;
		
		return t;
	}
}

Tok* Lexcical::dfaDelim(char *input, int &i) {
	char dfa[3][3]={"01",
					"11"};
	char start_state = '0';
	char accept_state = '1';
	char temp = '0',temp2 = '0';
	int x=0,y=0;// start state
	char current_state = start_state - 48;
	int countLenght=0;
	string tmp;
	while (true)
	{
		if(input[i]==' ' || input[i]=='\n' || input[i]=='\t'){
			y=1;
			x=dfa[x][y]-48;
			countLenght++;
			tmp += input[i];
		}
		else if(input[i]==23){
			readbuff(input,i);
		}
		else{
			
			break;
		}
		i++;
	}
	Tok *t = new Tok;
	if(x==1){
		t->type= DELIM;
		t->lenght=countLenght;
		t->str = tmp;
		return t;
	}
	else{
		t->type= NONE;
		t->lenght=countLenght;
		t->str = tmp;
		return t;
	}
}

Tok* Lexcical::dfaIdentifier(char *input, int &i){
	char dfa[3][3] ={	"12",
						"11",
						"22"
					};

	char start_state = '0';
	char accept_state = '1';
	char temp = '0',temp2 = '0';
	int x=0,y=0;// start state
	char current_state = start_state - 48;
	int countLenght=0;
	string tmp;
	while (true){
		temp= input[i];
		if ((temp >= 'A' && temp <= 'Z') || (temp >= 'a' && temp <= 'z') ){
			y = 0;
			x = dfa[x][y]- 48;
			countLenght++;
			tmp += temp;
		}
		else if (temp >= '0' && temp <= '9'){
			y = 1;
			x = dfa[x][y] - 48;
			countLenght++;
			tmp += temp;
		}
		else if(input[i]==23){
			readbuff(input,i);
		}
		else{
			break;
		}
		i++;
	}
	Tok *t = new Tok;
	if (x == 1 ){
		if (isKeyword(tmp)){
			t->type = Keyword;
			t->lenght=countLenght;
			t->str = tmp;
		}
		else if ( tmp == "or" || tmp == "div" || tmp == "and" || tmp == "mod" ){
		/* these keywords will be reconized by relop or addop 
			:: these strings are not reconized as  keywords but as relop and addop
		*/
			t->type= NONE;
			t->lenght=0;
			t->str = tmp;
		}
		else{
			t->type= ID;
			t->lenght=countLenght;
			t->str = tmp;
		}
		return t;
	}
	else{
		t->type= NONE;
		t->lenght=countLenght;
		t->str = tmp;
		return t;
	}
}

Tok* Lexcical::dfaEqulTo(char *input,int &i){
	char dfa[4][3] ={	"13",
						"32",
						"33",
						"33"
					};
	char start_state = '0';
	char accept_state = '1';
	char temp = '0',temp2 = '0';
	int x=0,y=0;// start state
	char current_state = start_state - 48;
	int countLenght=0;
	string tmp;
	while (true){
		temp= input[i];
		if (temp == ':'){
			y = 0;
			x = dfa[x][y]- 48;
			countLenght++;
			tmp += temp;
		}
		else if (temp == '='){
			y = 1;
			x = dfa[x][y] - 48;
			countLenght++;
			tmp += temp;
		}
		else if(input[i]==23){
			readbuff(input,i);
		}
		else{
			break;
		}
		i++;
	}
	Tok *t = new Tok;
	if (x == 2 ){
		t->type=ASSIGNOP;
		t->lenght=countLenght;
		t->str = tmp;
		return t;
	}
	else{
		t->type= NONE;
		t->lenght=countLenght;
		t->str = tmp;
		return t;
	}
}

Tok* Lexcical::dfaRelop(char *input, int &i){
char dfa[9][9] ={   "01230000",
					"17744747",
					"25766567",
					"37777777",
					"47777777",
					"57777777",
					"67777777",
					"77777777"};
	char start_state = '0';
	char accept_state = '1';
	char temp = '0',temp2 = '0';
	int x=0,y=0;// start state
	char current_state = start_state - 48;
	int countLenght=0;
	string tmp;
	while (true){
		if(input[i]=='>'){
			y=1;
			x=dfa[x][y]-48;
			countLenght++;
			tmp += input[i];
		}
		else if(input[i]=='<'){
			y=2;
			x=dfa[x][y]-48;
			countLenght++;
			tmp += input[i];
		}
		else if(input[i]=='='){
			y=3;
			x=dfa[x][y]-48;
			countLenght++;
			tmp += input[i];
		}
		else if(input[i]==23){
			readbuff(input,i);
		}
		else{
			//y=0;
			//x=dfa[x][y]-48;
			break;
		}
		i++;
	}
	Tok *t = new Tok;
	if(x==1 || x==2 || x==3 || x==4 || x==5 || x==6){
		t->type= RELOP;
		t->lenght=countLenght;
		t->str = tmp;
		return t;
	}
	else {
		t->type= NONE;
		t->lenght=countLenght;
		t->str = tmp;
		return t;
	}
}

Tok* Lexcical::dfaNumber(char *input,int &i){
	 char dfa[9][9]={"71717717",
					 "71214717",//digit
					 "73737737",//dot
					 "73734737",// digit
					 "76767567",//E
					 "76767767",// (+/-)
					 "76767767",//digit
					 "7777777"};// any thing else
	char start_state = '0';
	char accept_state = '1';
	char temp = '0',temp2 = '0';
	int x=0,y=0;// start state
	char current_state = start_state - 48;
	int countLenght=0;
	string tmp;
	while (true){
		if(input[i]>='0' && input[i]<='9'){
		y=1;
		x=dfa[x][y]-48;
		countLenght++;
		tmp += input[i];
		}
		else if(input[i]=='.'){
			y=2;
			x=dfa[x][y]-48;
			countLenght++;
			tmp += input[i];
		}
		else if(input[i]=='e'){
			y=4;
			x=dfa[x][y]-48;
			countLenght++;
			tmp += input[i];
		}
		else if(input[i]=='+' || input[i]=='-'){
			y=5;
			x=dfa[x][y]-48;
			countLenght++;
			tmp += input[i];
		}
		else if(input[i]==23){
				readbuff(input,i);
		}
		else{		
			break;
		}
		i++;
	}
	Tok *t = new Tok;
	if (x == 1 || x==3 || x==6 ){

		t->type= NUM;
		t->lenght=countLenght;
		t->str = tmp;
		return t;
	}
	else{		
		t->type= NONE;
		t->str = tmp;
		if ( countLenght ==  1 &&  tmp.compare(".") == 0 )// to skip dot symbol if it come along
			t->lenght=0;
		else if (countLenght ==  1 &&  tmp.compare("e") == 0 ) // skip simple e
			t->lenght=0;
		else
			t->lenght=countLenght;
		return t;
	}
 }

Tok* Lexcical::dfaMulop(char *input, int &i){
	char ch='a';
	char start_state = '0';
	char accept_state = '1';
	char temp = '0',temp2 = '0';
	int x=0,y=0;// start state
	char current_state = start_state - 48;
	int countLenght=0;
	string tmp;
	char dfa[13][13]={"abcdelllcjcl",
					  "blllllllllll",
					  "lllllfllllll",
					  "lllllllhllll",
					  "llllllllljll",
					  "llllllglllll",
					  "llllllllllll",
					  "llllllllilll",
					  "llllllllllll",
					  "llllllllllkl",
					  "llllllllllll",
					  "llllllllllll",	  
					};	 
	while(true){
		if(input[i]=='*' || input[i]=='/'){
			y=1;
			x=dfa[x][y]-97;
			countLenght++;
			tmp += input[i];
		}
		else if(input[i]=='d'){
			if(x==7){
				y=8;
			}
			else if(x==9){
				y=10;
			}
			else{
				y=2;
			}
			x=dfa[x][y]-97;
			countLenght++;
			tmp += input[i];
		}
		else if(input[i]=='i'){
			y=5;
			x=dfa[x][y]-97;			
			countLenght++;
			tmp += input[i];
		}
		else if(input[i]=='v'){
			y=6;
			x=dfa[x][y]-97;				
			countLenght++;
			tmp += input[i];
		}
		else if(input[i]=='m'){
			y=3;
			x=dfa[x][y]-97;				
			countLenght++;
			tmp += input[i];
		}
		else if(input[i]=='o'){
			y=7;
			x=dfa[x][y]-97;		
			countLenght++;
			tmp += input[i];
		}
		else if(input[i]=='a'){
			y=4;
			x=dfa[x][y]-97;	
			countLenght++;
			tmp += input[i];
		}
		else if(input[i]=='n'){
			y=9;
			x=dfa[x][y]-97;			
			countLenght++;
			tmp += input[i];
		}
		//else if(input[i]=='/0')
		//{
				
	//	break;
//	}
		else if(input[i]==23){
			readbuff(input,i);
		}
		else{
			break;
		}
		i++;
	}
	Tok *t = new Tok;
	if(x==8 || x==1 || x==6 ||x==10){
		t->type= MULOP;
		t->lenght=countLenght;
		t->str = tmp;
		return t;
	}
	else {
		t->type= NONE;
		t->str = tmp;
		if ( countLenght ==  1 && !( tmp.compare("*") == 0 || tmp.compare("/") == 0) )
			t->lenght=0;
		else
			t->lenght=countLenght;
		return t;
	}
}

Tok* Lexcical::dfaPun(char *input, int &i){

	char dfa[3][3] ={	"12",
						"22",
						"22"
					};
	char start_state = '0';
	char accept_state = '1';
	//char temp = '0',temp2 = '0';
	int x=0,y=0;// start state
	char current_state = start_state - 48;
	int countLenght=0;
	string tmp;
//	while (true){
		if (input[i] == ',' || input[i] == ';' || input[i] == '(' || input[i] == ')' || input[i] == ':' || input[i] == '.' || input[i] == '[' || input[i] == ']' ){// [ ] ..
			y = 0;
			x = dfa[x][y]- 48;
			countLenght++;
			tmp += input[i];
		}
		if (input[i] == '.' && input[i+1] == '.')
		{
			y = 0;
			x = 1;
			countLenght++;
			tmp += input[i];
			i++;// i couldnt bare it...
		}
//		else{
	//		break;
	//	}
		i++;
//	}
	Tok *t = new Tok;
	if (x == 1 ){
		
		t->type= PUN;
		t->lenght=countLenght;
		t->str = tmp;
		return t;
	}
	else{
		
		t->type= NONE;
		t->lenght=countLenght;
		t->str = tmp;
		return t;
	}
}

Tok* Lexcical::dfaComment(char *input, int &i){
	char dfa[3][4]={"122",
					"211",
					"222",
					};
	char start_state = '0';
	char accept_state = '1';
	char temp = '0',temp2 = '0';
	int x=0,y=0;// start state
	char current_state = start_state - 48;
	int countLenght=0;
	bool ck = false;
	string tmp;
	while (true){				
		if(input[i]=='{')
		{
			y=0;		
			x=dfa[x][y]-48;
			countLenght++;
			tmp += input[i];
			ck = true;
		}
		else if(input[i]=='}'){
			y=1;
			x=dfa[x][y]-48;	
			countLenght++;
			tmp += input[i];
			break;	
		}
		else if (input[i]=='\0'){
			x = 2; // this means reached file end so it does not matter
			break;
		}
		else if(input[i]!='{' && ck){
			y=1;
			x=dfa[x][y]-48;	
			countLenght++;
			tmp += input[i];
		}
		else if (input[i] == 23){
			readbuff(input,i);
		}
		else{
			break;
		}
		i++;
	}
	Tok *t = new Tok;
	if (x == 1 ){

		t->type= COMT;
		t->lenght=countLenght;
		t->str =tmp;
		return t;
	}
	else
	{

		t->type= NONE;
		t->lenght=countLenght;
		t->str = tmp;
		return t;
	}

}// need correction


