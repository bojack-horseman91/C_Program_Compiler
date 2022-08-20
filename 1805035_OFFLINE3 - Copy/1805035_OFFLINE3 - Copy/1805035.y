%{
#include <bits/stdc++.h>
// #include<iostream>
// #include<cstdlib>
// #include<cstring>
// #include<cmath>
#include "SymbolInfo.h"
#include "SymbolTable.h"
// #define YYSTYPE SymbolInfo*

using namespace std;

int yyparse(void);
int yylex(void);
extern FILE *yyin;
extern int line_count;
extern int error_count;
SymbolTable *table;
string space=" ";
FILE *fp,*fp1,*fp2,*fp3;
ofstream logfile2("log.txt");
ofstream errorfile("error.txt");
ofstream asmCode("code.txt");
ofstream asmData("data.txt");
vector< pair<string,string> > temporaryParameterList ;
int currentOffset=2,temporaryOffset=2;
vector<SymbolInfo*>declared_varList;
vector<SymbolInfo*>My_parameter_list;
int numberOfPushes=0,temporaryPush=0;
void yyerror(char *s)
{
	errorfile<<"Error at line e"<<line_count<<" :"<<s<<endl<<endl;
	logfile2<<"Error at line e"<<line_count<<" :"<<s<<endl<<endl;
	error_count++;

}

void printMSG(string nameOfPart){
	logfile2<<"\nLine "<<line_count<<nameOfPart<<endl<<endl;
}
void printMSG(string nameOfPart,string nameOfToken){
	logfile2<<"\nLine "<<line_count<<": "<<nameOfPart<<endl<<endl<<nameOfToken<<endl<<endl;
}
bool conversionError(string a ,string b){
	if(a=="CONST_FLOAT"&&b!="CONST_FLOAT")
		return true;
	else if(a=="VOID"||b=="VOID")
		return true;
	return false;
}
void printError(string nameOfPart,string nameOfToken){
	errorfile<<"Error at line "<<line_count<<": "<<nameOfPart<<space<<nameOfToken<<endl<<endl;
	logfile2<<"Error at line "<<line_count<<": "<<nameOfPart<<space<<nameOfToken<<endl<<endl;
	error_count++;	
}
void checkParameterUniquenessForFunDefinition(){
	if(temporaryParameterList.size()!=0){
		for(int i=0;i<temporaryParameterList.size();i++){
			string name = temporaryParameterList[i].first;
			string type = temporaryParameterList[i].second;

			SymbolInfo *currentSymbol = new SymbolInfo();
			currentSymbol->setName(name);
			logfile2<<i<<"----"<<name<<" "<<type<<endl;
			currentSymbol->setType("ID");
			currentSymbol->typeOfVar = type;
			currentSymbol->offset=(i+1)*2;
			
			if(name==""){
				errorfile<<"Error at line "<<line_count-1<<" :"<<i+1<<"th parameter's name not given in function definition  "<<currentSymbol->getName()<<" in parameter"<<endl<<endl;
				logfile2<<"Error at line "<<line_count-1<<" :"<<i+1<<"th parameter's name not given in function definition of var"<<currentSymbol->getName()<<" in parameter"<<endl<<endl;
				error_count++;
			}
			else if(!table->Insert(currentSymbol)){
				errorfile<<"Error at line "<<line_count-1<<" :"<<"Multiple declaration of "<<currentSymbol->getName()<<" in parameter"<<endl<<endl;
				logfile2<<"Error at line "<<line_count-1<<" :"<<"Multiple declaration of "<<currentSymbol->getName()<<" in parameter"<<endl<<endl;
				error_count++;
				
			}
			

		
	}
	
	}
	
	temporaryParameterList.clear();
}
void parameterUniquenessCheckforDeclaration(){
	table->EnterScope();
	
	if(temporaryParameterList.size()!=0){
		for(int i=0;i<temporaryParameterList.size();i++){
			string name = temporaryParameterList[i].first;
			string type = temporaryParameterList[i].second;

			SymbolInfo *currentSymbol = new SymbolInfo();
			currentSymbol->setName(name);
			currentSymbol->setType("ID");
			currentSymbol->typeOfVar = type;
			if(name!=""&&!table->Insert(currentSymbol)){
				errorfile<<"Error at line "<<line_count-1<<" :"<<"Multiple declaration of "<<currentSymbol->getName()<<" in parameter"<<endl<<endl;
				logfile2<<"Error at line "<<line_count-1<<" :"<<"Multiple declaration of "<<currentSymbol->getName()<<" in parameter"<<endl<<endl;
				error_count++;
				
			}
		}
	}
	temporaryParameterList.clear();
	table->ExitScope();
}
int label_count = 0;
int temp_count = 0;
string newLabel()
{
	string label = "L";
	stringstream ss;
	ss<<label_count;
	label += ss.str();
	label_count++;
	return label;
}
//function for generating new temporary varible for assembly code
// string newTemp()
// {
// 	string temp = "t";
// 	stringstream ss;
// 	ss<<temp_count;
// 	temp += ss.str();
// 	temp_count++;
// 	var_list.push_back("\t"+temp+"\tdw\t?");
// 	return temp;
// }
string endMSG="";
string output_procedure ="\nPRINT_FUNC PROC\
						\n\tPUSH AX\
						\n\tPUSH BX\
						\n\tPUSH CX\
						\n\tPUSH DX\
						\n\n\tOR AX, AX\
						\n\tJGE END_IF1\
						\n\tPUSH AX\
						\n\tMOV DL,'-'\
						\n\tMOV AH, 2\
						\n\tINT 21H\
						\n\tPOP AX\
						\n\tNEG AX\
						\n\nEND_IF1:\
						\n\tXOR CX, CX\
						\n\tMOV BX, 10D\
						\n\nREPEAT1:\
						\n\tXOR DX, DX\
						\n\tDIV BX\
						\n\tPUSH DX\
						\n\tINC CX\
						\n\n\tOR AX, AX\
						\n\tJNE REPEAT1\
						\n\n\tMOV AH, 2\
						\n\nPRINT_LOOP:\
						\n\tPOP DX\
						\n\tOR DL, 30H\
						\n\tINT 21H\
						\n\tLOOP PRINT_LOOP\
						\n\tMOV AH, 2\
						\n\tMOV DL, 10\
						\n\tINT 21H\
						\n\n\tMOV DL, 13\
						\n\tINT 21H\
						\n\n\tPOP DX\
						\n\tPOP CX\
						\n\tPOP BX\
						\n\tPOP AX\
						\n\tRET\
						\nPRINT_FUNC ENDP\n\n";

		string MyPush="MY_PUSH PROC\n\
						\n\tPUSH SI\
						\n\tPUSH BX\
						\n\tPUSH CX\
						\n\tPUSH DX\
						\n\n\tLEA SI,MY_STACK\n\
						\tADD SI,MY_STACKOFFSET\n\
						\tMOV BX,MY_STACKINPUT\n\
						\tMOV [SI],BX\n\
						\tADD MY_STACKOFFSET,2\n\
						\n\n\tPOP DX\
						\n\tPOP CX\
						\n\tPOP BX\
						\n\tPOP SI\
						\n\tRET\
						\nMY_PUSH ENDP\n";
		string MyPop="MY_POP PROC\n\
						\n\tPUSH SI\
						\n\tPUSH BX\
						\n\tPUSH CX\
						\n\tPUSH DX\
						\n\tSUB MY_STACKOFFSET,2\n\
						\n\n\tLEA SI,MY_STACK\n\
						\tADD SI,MY_STACKOFFSET\n\
						\tMOV BX,[SI]\n\
						\tMOV MY_STACKOUTPUT,BX\n\
						\n\n\tPOP DX\
						\n\tPOP CX\
						\n\tPOP BX\
						\n\tPOP SI\
						\n\tRET\
						\nMY_POP ENDP\n";
		string DelayFunc="DELAY PROC\n\
						\n\tPUSH AX\
						\n\tPUSH BX\
						\n\tPUSH CX\
						\n\tPUSH DX\
						\nMOV BX,5\
						\nDELAY_LOOP:\
						\nMOV     CX, 0FH\
						\nMOV     DX, 4240H\
						\nMOV     AH, 86H\
						\nINT     15H\
						\nDEC BX\
						\nCMP BX,0\
						\nJNE DELAY_LOOP\
						\n\n\tPOP DX\
						\n\tPOP CX\
						\n\tPOP BX\
						\n\tPOP AX\
						\n\tRET\
						\nDELAY ENDP";
string whileLabel,whileEnd,conditionEnd,elseLabel,forLoopStart,ENDLOOP,IncLabel,LoopLabel;
stack<string>conditionStack;
%}
%union {double double_val; int integer_val;char char_val ; SymbolInfo* symbol_val;}
%token<symbol_val> IF ELSE FOR DO NOT FLOAT INT VOID CHAR DOUBLE WHILE RETURN CONTINUE LPAREN RPAREN LCURL RCURL COMMA SEMICOLON LTHIRD RTHIRD PRINTLN
%token<symbol_val>CONST_INT
%token<symbol_val>CONST_FLOAT
%token<char_val> CONST_CHAR 
%token<symbol_val>ID   INCOP DECOP ADDOP MULOP RELOP LOGICOP ASSIGNOP
%type<symbol_val> var_declaration unit program start func_declaration func_definition compound_statement parameter_list variable factor unary_expression 
%type<symbol_val> term simple_expression rel_expression  declaration_list logic_expression expression expression_statement statement statements argument_list arguments
%type<symbol_val>type_specifier  CONDITIONAL_STATEMENT

%left ADDOP
%right MULOP NOT
%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE
%token Unrecognized

%%

start : {
		asmData<<".MODEL BIG\n.STACK 400H"<<endl;
		asmCode<<".CODE"<<endl;
		asmCode<<output_procedure<<endl<<MyPush<<endl<<MyPop<<endl<<DelayFunc<<endl;
		asmData<<".DATA"<<endl;
		asmData<<"FUNC_RETURN_VALUE DW ?\nTEMPORARY_VALUE DW ?\nt0 DW ?\nt1 DW ?\
				\nMY_STACK DW 15 dup(?)\nMY_STACKOFFSET DW 0\nMY_STACKINPUT DW ?\
				\nMY_STACKOUTPUT DW ?\nT3 DW ?"<<endl;
}program
	{
		asmCode<<"END MAIN"<<endl;
		cout<<"start"<<endl;
		logfile2<<"Line "<<line_count-1<<": start : program"<<endl;
		//write your code in this block in all the similar blocks below
		fstream f1,f2,f3; 
 		 string str1,str2; //str1 for fetching string line from file 1 and str2 for fetching string from file2
  
			f1.open("data.txt",ios::in);//opening file in reading mode
			f2.open("code.txt",ios::in);
			f3.open("asmCode.asm",ios::out);//opening file in writing mode

			while(getline(f1, str1)){ //read lines from file object and put it into string and push back to file 3.
					f3<<str1; // inserting the fetched string inside file3
					f3<<endl;
				}

			while(getline(f2, str2)){ //Same step for file 2 to file 3 fetching
					f3<<str2;
					f3<<endl;
				}
			
			f1.close();
			f2.close();
			f3.close();
	}|Unrecognized{
		printError("Unrecognized Character","");
	}|error{
		yyerror;
		yyerrok;
		yyclearin;
	}
	;

program :program unit{
		$$ = new SymbolInfo($1->getName()+"\n"+$2->getName(),"");
		logfile2<<"\nLine  "<<line_count<<": program : program unit"<<endl<<endl<<$$->getName()<<endl<<endl;
		}
		| unit{
		$$ = $1;
		logfile2<<"\nLine  "<<line_count<<": program : unit"<<endl<<endl<<$$->getName()<<endl<<endl;
	}
	;
	
unit : var_declaration{		
			$$ = $1;
			logfile2<<"\nLine  "<<line_count<<": unit : var_declaration"<<endl<<endl<<$$->getName()<<endl<<endl;
		}| func_declaration {		
			$$ = $1;
			logfile2<<"\nLine  "<<line_count<<": unit : func_declaration"<<endl<<endl<<$$->getName()<<endl<<endl;
		 }
     | func_definition {
     		$$ = $1;
			logfile2<<"\nLine  "<<line_count<<": unit : func_definition"<<endl<<endl<<$$->getName()<<endl<<endl;
     	}
		
	;
 
 func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON{
	/* ************************************************************************ */
	/*	 				Implement the below characteristics						*/
	/*   We need to check some properties of function declaration in this step:  */
	/*           	1. Check return type is same                            */
	/*      		2. Check number of parameter is same                       */
	/*         	    3. Check parameter sequence is same                       */
	/*       	    4. No void Parameters are declared                        */
	/*              5.Check for paraemter uniqness                            */
	/* ************************************************************************ */

	
	SymbolInfo*	currentSymbol = table->LookUp($2->getName());			
	//IF IT IS NOT IN THE TABLE 
	if(currentSymbol==NULL){
		
		// THIS VARIABLE IS USED TO CHECK IF IT IS A VOID
		bool isVoid = false;
		// NOW WE CHECK IF NO VOID PARAMETERS ARE DECLARED
		for(int i=0;i<temporaryParameterList.size();i++){
			if(temporaryParameterList[i].second=="VOID"){
				isVoid = true; 
				break;
			}
		}
		currentSymbol = new SymbolInfo($2->getName(),$2->getType());
		currentSymbol->typeOfID = "FUNCTION";
		currentSymbol->returnTypeOfFunction = $1->getType();
		currentSymbol->isFunction = true;
		currentSymbol->isFunctionDeclared = true;

		if(isVoid){
			printError("Parameter cannot be void" ,currentSymbol->getName());
			currentSymbol->isFunction = false;
		}
		for(int i=0;i<temporaryParameterList.size();i++){
			currentSymbol->functionParameterList.push_back(make_pair(temporaryParameterList[i].first, temporaryParameterList[i].second));
		}
		parameterUniquenessCheckforDeclaration();
		temporaryParameterList.clear();
		table->Insert(currentSymbol);
		logfile2<<currentSymbol->functionParameterList.size()<<endl;
	
	}
	else{
		// Checking return type
		if(currentSymbol->returnTypeOfFunction != $1->getType()){
			printError( "Return Type Mismatch of function declaration",currentSymbol->getName() );
		}

		// Checking parameter
		if(currentSymbol->functionParameterList.size()!=temporaryParameterList.size()){
			printError(" Total number of arguments mismatch in function",currentSymbol->getName() );
			temporaryParameterList.clear();
		}
		// Checking parameter sequence
		else{
			for(int i=0;i<temporaryParameterList.size();i++){
				if(temporaryParameterList[i].second != currentSymbol->functionParameterList[i].second){
					printError("Argument Type Mismatch with previous function declaration",currentSymbol->getName() );
					
				}
			}
			parameterUniquenessCheckforDeclaration();
			temporaryParameterList.clear();
		}

	}
	
	$$ =new SymbolInfo($1->getName()+space+$2->getName()+"("+$4->getName()+");","func_declaration");
	printMSG(" func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON",$$->getName());

		}
		
		| type_specifier ID LPAREN RPAREN SEMICOLON{
				$$=new SymbolInfo($1->getName()+space+$2->getName()+"();","func_declaration");
				printMSG(" func_declaration : type_specifier ID LPAREN RPAREN SEMICOLON",$$->getName());
				SymbolInfo* currentSymbol = table->LookUp($2->getName());
				if(currentSymbol != NULL){
						if(currentSymbol->returnTypeOfFunction != $1->getType()){
							printError("Return Type Mismatch of function declaration", $2->getName());
							
						}
						if(currentSymbol->functionParameterList.size()!=0){
							printError("Total number of arguments mismatch in function", $2->getName());
							temporaryParameterList.clear();
						} 
					}
					else{
						currentSymbol = new SymbolInfo();
						currentSymbol->typeOfID = "FUNCTION";
						currentSymbol->returnTypeOfFunction = $1->getType();
						currentSymbol->isFunction = true;
						currentSymbol->isFunctionDeclared = true;
						currentSymbol->setName($2->getName());
						currentSymbol->setType($2->getType());

						for(int i=0;i<temporaryParameterList.size();i++){
							currentSymbol->functionParameterList.push_back(make_pair(temporaryParameterList[i].first, temporaryParameterList[i].second));
						}
						temporaryParameterList.clear();
						table->Insert(currentSymbol);
						logfile2<<currentSymbol->functionParameterList.size()<<endl;
					}
					
			};
	 
func_definition :type_specifier ID LPAREN parameter_list  error RPAREN compound_statement{
		yyerror;
		yyerrok;
		yyclearin;	
		temporaryParameterList=$4->functionParameterList;
		cout<<"************************************************e"<<$2->getName()<<endl;
		for(int i=0;i<$4->functionParameterList.size();i++)
			cout<<$4->functionParameterList[i].first<<$4->functionParameterList[i].second<<endl;
		cout<<"************************************************"<<endl;
		SymbolInfo *currentSymbol = table->LookUp($2->getName());
		SymbolInfo *newSymbol = new SymbolInfo();
		bool flag = true;
		// IF IT DOESNT EXIST THEN PUT IT IN THE TABLE
		if(currentSymbol==NULL){
			bool checkVoid = false;
			//CHECK FOR VOID PARAMETERS
			for(int i=0;i<$4->functionParameterList.size();i++){
				if($4->functionParameterList[i].second == "VOID"){
					checkVoid = true;
				}
			}

			// make a new object to insert into Symbol Table
			newSymbol->typeOfID = "FUNCTION";
			newSymbol->returnTypeOfFunction = $1->getType();
			newSymbol->isFunction = true;
			newSymbol->isFunctionDefined = true;
			newSymbol->setName($2->getName());
			newSymbol->setType($2->getType());

			if(checkVoid){
				printError("Parameter cannot be void" ,currentSymbol->getName());
				newSymbol->isFunction = false;
			}

			for(int i=0;i<$4->functionParameterList.size();i++){
				newSymbol->functionParameterList.push_back(make_pair(temporaryParameterList[i].first, temporaryParameterList[i].second));
				
			}
			

			/*if(return_type_solver!=$1->getType())
			{
				numberOfErrors++;
				fprintf(errors,"Error at Line %d : return type error \n\n",numberOfLines);
				return_type_solver="";
				newSymbol->isFunction=false;
			}*/
			table->Insert(newSymbol);
			//temporaryParameterList.clear();
		}
		// NOW IF IT ALREADY EXISTS IN GLOBAL SCOPE
		else{
			// FUNCTION ALREADY EXISTS ERROR!!!!
			if(currentSymbol->isFunctionDefined){
				printError("Multiple definition of function" ,currentSymbol->getName());
				temporaryParameterList.clear();
			}else if(currentSymbol->isFunctionDeclared){
				/* 
				**************************************************
				
						THREE CASES TO BE HANDLED:
							1. Return type check 
							2. Check number of parameters and
							3. Check for sequence of parameters 
				*****************************************************
				*/
				currentSymbol->isFunctionDefined = true;
				string actualReturnType = $1->getType();
				string declaredReturnType = currentSymbol->returnTypeOfFunction;
				int declaredParamSize = currentSymbol->functionParameterList.size();
				int definedParamSize = temporaryParameterList.size();
				
				// Case 1: Return type Check
				if(actualReturnType != declaredReturnType){
					printError("Return type mismatch" ,currentSymbol->getName());
					flag = false;
				}
				// Case 2: Check for size of paramter list
				else if(definedParamSize != declaredParamSize){
					printError("Total number of arguments mismatch in function" ,currentSymbol->getName());
					
					temporaryParameterList.clear();
					flag = false;
				}
				// Case 3: Check for sequence of parameter list 
				else{
					for(int i = 0;i<temporaryParameterList.size();i++){
						if(temporaryParameterList[i].second != currentSymbol->functionParameterList[i].second){
							printError("Argument Type Mismatch with function declaration" ,currentSymbol->getName());
							
							// flag=false;
							break;
						}
						
					}
					// temporaryParameterList.clear();
					
				}
				
			}
			else{
				printError("Multiple definition of function" ,currentSymbol->getName());
				
			}
		}
		

		$$=new SymbolInfo($1->getName()+space+$2->getName()+space+"( "+$4->getName()+space+")"+$7->getName(),"");
		printMSG("func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement",$$->getName());
		temporaryParameterList.clear();
		

 }|
	
type_specifier ID LPAREN parameter_list  RPAREN
	{	
		temporaryParameterList=$4->functionParameterList;
		cout<<"************************************************p"<<$2->getName()<<endl;
		for(int i=0;i<$4->functionParameterList.size();i++)
			cout<<$4->functionParameterList[i].first<<endl;
		cout<<"************************************************"<<endl;
		SymbolInfo *currentSymbol = table->LookUp($2->getName());
		SymbolInfo *newSymbol = new SymbolInfo();
		bool flag = true;
		// IF IT DOESNT EXIST THEN PUT IT IN THE TABLE
		if(currentSymbol==NULL){
			bool checkVoid = false;
			//CHECK FOR VOID PARAMETERS
			for(int i=0;i<$4->functionParameterList.size();i++){
				if($4->functionParameterList[i].second == "VOID"){
					checkVoid = true;
				}
			}

			// make a new object to insert into Symbol Table
			newSymbol->typeOfID = "FUNCTION";
			newSymbol->returnTypeOfFunction = $1->getType();
			newSymbol->isFunction = true;
			newSymbol->isFunctionDefined = true;
			newSymbol->setName($2->getName());
			newSymbol->setType($2->getType());

			if(checkVoid){
				printError("Parameter cannot be void" ,currentSymbol->getName());
				newSymbol->isFunction = false;
			}

			for(int i=0;i<$4->functionParameterList.size();i++){
				newSymbol->functionParameterList.push_back(make_pair(temporaryParameterList[i].first, temporaryParameterList[i].second));
				
			}
			

			/*if(return_type_solver!=$1->getType())
			{
				numberOfErrors++;
				fprintf(errors,"Error at Line %d : return type error \n\n",numberOfLines);
				return_type_solver="";
				newSymbol->isFunction=false;
			}*/
			table->Insert(newSymbol);
			//temporaryParameterList.clear();
			currentSymbol=newSymbol;
		}
		// NOW IF IT ALREADY EXISTS IN GLOBAL SCOPE
		else{
			// FUNCTION ALREADY EXISTS ERROR!!!!
			if(currentSymbol->isFunctionDefined){
				printError("Multiple definition of function" ,currentSymbol->getName());
				temporaryParameterList.clear();
			}else if(currentSymbol->isFunctionDeclared){
				/* 
				**************************************************
				
						THREE CASES TO BE HANDLED:
							1. Return type check 
							2. Check number of parameters and
							3. Check for sequence of parameters 
				*****************************************************
				*/
				currentSymbol->isFunctionDefined = true;
				string actualReturnType = $1->getType();
				string declaredReturnType = currentSymbol->returnTypeOfFunction;
				int declaredParamSize = currentSymbol->functionParameterList.size();
				int definedParamSize = temporaryParameterList.size();
				
				// Case 1: Return type Check
				if(actualReturnType != declaredReturnType){
					printError("Return type mismatch" ,currentSymbol->getName());
					flag = false;
				}
				// Case 2: Check for size of paramter list
				else if(definedParamSize != declaredParamSize){
					printError("Total number of arguments mismatch in function" ,currentSymbol->getName());
					
					temporaryParameterList.clear();
					flag = false;
				}
				// Case 3: Check for sequence of parameter list 
				else{
					for(int i = 0;i<temporaryParameterList.size();i++){
						if(temporaryParameterList[i].second != currentSymbol->functionParameterList[i].second){
							printError("Argument Type Mismatch with function declaration" ,currentSymbol->getName());
							
							// flag=false;
							break;
						}
						
					}
					// temporaryParameterList.clear();
					
				}
				
			}
			else{
				printError("Multiple definition of function" ,currentSymbol->getName());
				
			}
		}

		/* ******************* */
	/*      ICG Code       */
	/* ******************* */
	if($2->getName() == "main")
		asmCode<< "MAIN PROC\n\tMOV AX, @DATA\n\tMOV DS, AX\n";
	else
		asmCode<< $2->getName()<<" PROC"<<endl;
	temporaryOffset=currentOffset;
	currentOffset=2;
	temporaryPush=numberOfPushes;
	numberOfPushes=0;
	asmCode<<"PUSH AX\nPUSH BX\nPUSH CX\nPUSH DX\nPUSH SI\nPUSH DI\nPUSH t0\nPUSH t1\nPUSH TEMPORARY_VALUE\n";
	asmCode<<"MOV BX,SP"<<endl;
	for(int i=0;i<temporaryParameterList.size();i++){
		/****************************ICG CODE ***************************************/
			currentSymbol->functionParameterOffset.push_back(currentOffset);
			asmCode<<"\tMOV AX, [BP-"<<(i+1)*2<<"]\nPUSH AX"<<endl;
			numberOfPushes++;
			currentOffset+=2;
	}
	
	asmCode<<"\tMOV BP,BX"<<endl;
	if($2->getName() == "main")
		endMSG="MOV AH, 4CH\nMOV AL, 01 ;your return code.\nINT 21H\n";
	else
		endMSG="\n\tRET\n";
		
}

 compound_statement{
		$$=new SymbolInfo($1->getName()+space+$2->getName()+space+"( "+$4->getName()+space+")"+$7->getName(),"");
		printMSG("func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement",$$->getName());
		temporaryParameterList.clear();
		if($1->getType()=="VOID"){
			currentOffset=temporaryOffset;
			for(int i=0;i<numberOfPushes;i++)
				asmCode<<"POP AX"<<endl;
			asmCode<<";NUMBER OF PUSHES"<<numberOfPushes<<endl;
			numberOfPushes= temporaryPush;
			asmCode<<"POP TEMPORARY_VALUE\nPOP t1\nPOP t0\nPOP DI\nPOP SI\nPOP DX\nPOP CX\nPOP BX\nPOP AX\n";
			if($2->getName() == "main")
				asmCode<<"MOV AH, 4CH\nMOV AL, 01 ;your return code.\nINT 21H\nMAIN ENDP"<<endl;
			else
				asmCode<<"\n\tRET\n"<<$2->getName()<<" ENDP\n\n";
		}
		else{
			currentOffset=temporaryOffset;
			numberOfPushes= temporaryPush;
			if($2->getName() == "main")
				asmCode<<"MAIN ENDP"<<endl;
			else
				asmCode<<$2->getName()<<" ENDP\n\n";
		}
		//MARKER IM
		
 }
	
		| type_specifier ID LPAREN RPAREN{

			temporaryOffset=currentOffset;
			currentOffset=2;
			if($2->getName() == "main")
				asmCode<< "MAIN PROC\n\tMOV AX, @DATA\n\tMOV DS, AX\n";
			else
				asmCode<< $2->getName()<<" PROC"<<endl;
			temporaryPush=numberOfPushes;
			numberOfPushes=0;
			if($2->getName()!="main")
				asmCode<<"PUSH AX\nPUSH BX\nPUSH CX\nPUSH DX\nPUSH SI\nPUSH DI\nPUSH t0\nPUSH t1\nPUSH TEMPORARY_VALUE\n";
			asmCode<<"\tMOV BP,SP"<<endl;
			if($2->getName() == "main")
				endMSG="MOV AH, 4CH\nMOV AL, 01 ;your return code.\nINT 21H\n";
			else
				endMSG="\n\tRET\n";
		} compound_statement{


				$$=new SymbolInfo($1->getName()+space+$2->getName()+space+"()"+$6->getName(),"func_definition");
				printMSG("func_definition : type_specifier ID LPAREN RPAREN compound_statement",$$->getName());

				SymbolInfo *currentSymbol = table->LookUp($2->getName());

				if(currentSymbol==NULL){
					SymbolInfo* newSymbol = new SymbolInfo();
					newSymbol->typeOfID = "FUNCTION";
					newSymbol->returnTypeOfFunction = $1->getType();
					newSymbol->isFunction = true;
					newSymbol->isFunctionDefined = true;
					newSymbol->setName($2->getName());
					newSymbol->setType($2->getType());

					table->Insert(newSymbol);
				}else{
					if(currentSymbol->isFunctionDeclared){
						string actualReturnType = $1->getType();
						string funcReturnType = currentSymbol->returnTypeOfFunction;

						if(actualReturnType != funcReturnType){
							printError("Return type mismatch" ,currentSymbol->getName());
							currentSymbol->isFunction = false;
						}
					}else if(currentSymbol->isFunctionDefined){
						printError("Multiple defination of function" ,currentSymbol->getName());
						temporaryParameterList.clear();
						
					}
				}
				temporaryParameterList.clear();
				
				cout<<$2->returnTypeOfFunction<<"???????????????/////"<<endl;
				if($1->getType()=="VOID"){
					currentOffset=temporaryOffset;
					for(int i=0;i<numberOfPushes;i++)
						asmCode<<"POP AX"<<endl;
					asmCode<<";NUMNBER OF PUSHES"<<numberOfPushes<<endl;
					numberOfPushes= temporaryPush;
					if($2->getName()!="main")
						asmCode<<"POP TEMPORARY_VALUE\nPOP t1\nPOP t0\nPOP DI\nPOP SI\nPOP DX\nPOP CX\nPOP BX\nPOP AX\n";
					if($2->getName() == "main")
						asmCode<<"MOV AH, 4CH\nMOV AL, 01 ;your return code.\nINT 21H\nMAIN ENDP"<<endl;
					else
						asmCode<<"\n\tRET\n"<<$2->getName()<<" ENDP\n\n";
				}
				else{
					currentOffset=temporaryOffset;
					numberOfPushes= temporaryPush;
					if($2->getName() == "main")
						asmCode<<"MAIN ENDP"<<endl;
					else
						asmCode<<$2->getName()<<" ENDP\n\n";
				}
				
				
				
			}
 		;				


parameter_list  : parameter_list COMMA type_specifier ID{
	//print our msg
	$$=new SymbolInfo($1->getName()+","+$3->getName()+space+$4->getName(),"");
	printMSG("parameter_list : parameter_list COMMA type_specifier ID",$$->getName());
	temporaryParameterList.push_back(make_pair($4->getName(),$3->getType()));
	$$->functionParameterList=$1->functionParameterList;
	$$->functionParameterList.push_back(make_pair($4->getName(),$3->getType()));
	
    }
		| parameter_list COMMA type_specifier{
			$$=new SymbolInfo($1->getName()+","+$3->getName(),"");
			printMSG("parameter_list : parameter_list COMMA type_specifier ",$$->getName());
			temporaryParameterList.push_back(make_pair("",$3->getType()));
			$$->functionParameterList=$1->functionParameterList;
			$$->functionParameterList.push_back(make_pair("",$3->getType()));
		}
 		| type_specifier ID{
			
			$$=new SymbolInfo($1->getName()+space+$2->getName(),$1->getType());
			logfile2<<$1->getName();
			printMSG("parameter_list : type_specifier ID ",$$->getName());
			temporaryParameterList.push_back(make_pair($2->getName(),$1->getType()));
			$$->functionParameterList.push_back(make_pair($2->getName(),$1->getType()));
		}
		| type_specifier  {
			
			$$=new SymbolInfo($1->getName(),$1->getType());
			printMSG("parameter_list : type_specifier ",$$->getName());
			temporaryParameterList.push_back(make_pair("",$1->getType()));
			$$->functionParameterList.push_back(make_pair("",$1->getType()));
			
		}
 		;

 		
compound_statement : LCURL{
	table->EnterScope();
	checkParameterUniquenessForFunDefinition();
	} 
	statements RCURL
	{
	$$=new SymbolInfo("{\n"+$3->getName()+"\n}","compound_statement");
	printMSG("compound_statement :LCURL statements RCURL",$$->getName());
	table->printAllLex(logfile2);
	table->ExitScope();
	
}
 		    | LCURL {
				table->EnterScope();
				
				checkParameterUniquenessForFunDefinition();
			}RCURL{
				$$=new SymbolInfo("{\n\n}","compound_statement");
				printMSG("compound_statement :LCURL  RCURL");
				table->printAllLex(logfile2);
				table->ExitScope();
			}
 		    ;
     

 		    
var_declaration : type_specifier declaration_list SEMICOLON {

				$$=new SymbolInfo($1->getName()+space+$2->getName()+";",$1->getName());
				asmCode<<";"<<$$->getName()<<endl;
				if($1->getName()=="void")
					printError("Variable type cannot be void",$$->getName());
				for(int i=0;i<declared_varList.size();i++){
					 SymbolInfo*cur= table->LookUp(declared_varList[i]->getName());
					if(cur->typeOfVar=="")
						cur->typeOfVar=$1->getType();	
					
				}
				declared_varList.clear();
				printMSG("var_declaration : type_specifier declaration_list SEMICOLON",$$->getName());
			}
 		 ;
 		 
type_specifier	: INT {
						$$= new SymbolInfo("int","CONST_INT");
						printMSG("type_specifier : INT","int");
						}
 		| FLOAT {
			$$= new SymbolInfo("float","CONST_FLOAT");
			printMSG("type_specifier :FLOAT ","float");
			}
 		| VOID {
			$$= new SymbolInfo("void","VOID");
			printMSG("type_specifier : VOID ","void");
		}
 		;
 		
declaration_list : declaration_list COMMA ID {
				$$=new SymbolInfo($1->getName()+","+$3->getName(),"DeclarationList");
				asmCode<<";"<<$$->getName()<<endl;
				/****************************ICG CODE*************************************/
								if(table->getCurrentScopeID()=="1"){
									asmData<<$3->getName()<<"  DW ?"<<endl;
								}
								else {
									$3->offset=currentOffset;
									currentOffset+=2;
									asmCode<<"\tPUSH 0\n";
									numberOfPushes++;
								}
			/****************************************************************************/
				if(!table->Insert($3)){
					printError("Multiple declaration of"+table->LookUp($3->getName())->typeOfVar,$3->getName());
				}
				printMSG("declaration_list :declaration_list COMMA ID",$$->getName());
				declared_varList.push_back($3);
			

			}|declaration_list error COMMA ID {
				yyerror;
				yyerrok;
				yyclearin;
				$$=new SymbolInfo($1->getName()+","+$4->getName(),"DeclarationList");
				if(!table->Insert($4)){
					printError("Multiple declaration of"+table->LookUp($3->getName())->typeOfVar,$3->getName());
				}
				printMSG("declaration_list :declaration_list COMMA ID",$$->getName());
				declared_varList.push_back($4);
			}
 		  | declaration_list COMMA ID LTHIRD CONST_INT RTHIRD{
			$$=new SymbolInfo($1->getName()+","+$3->getName()+"["+$5->getName()+"]","DeclarationList");
				/****************************ICG CODE*************************************/
							if(table->getCurrentScopeID()=="1"){
								asmData<<$3->getName()<<"  DW "<<$5->getName()<<"  dup( ?)"<<endl;
							}
							else {
								int len=stoi($5->getName().c_str());
								$3->offset=currentOffset;
								currentOffset+=2*len;
								for(int i=0;i<len;i++){
									asmCode<<"\tPUSH 0\n";
									numberOfPushes++;
								}
							}
			/****************************************************************************/
				$3->setType("array");
				$3->typeOfID="ARRAY";
				$3->setLen(atoi($5->getName().c_str()));
				if(!table->Insert($3)){
					printError("Multiple declaration of",$3->getName());
				}
				printMSG("declaration_list :declaration_list COMMA ID LTHIRD CONST_INT RTHIRD",$$->getName());
				declared_varList.push_back($3);
		  }
 		  | ID {$$=new SymbolInfo($1->getName(),"ID");
		  	/****************************ICG CODE*************************************/
							if(table->getCurrentScopeID()=="1"){
								asmData<<$1->getName()<<"  DW ?"<<endl;
							}
							else {
								$1->offset=currentOffset;
								currentOffset+=2;
								asmCode<<"\tPUSH 0\n";
								numberOfPushes++;
							}
			/****************************************************************************/
				if(!table->Insert($1)){
					printError("Multiple declaration of",$1->getName());
				}
				printMSG("declaration_list :ID",$$->getName());
				declared_varList.push_back($1);
				}
 		  | ID LTHIRD CONST_INT RTHIRD {$$=new SymbolInfo($1->getName()+"["+$3->getName()+"]","array");
			/****************************ICG CODE*************************************/
							if(table->getCurrentScopeID()=="1"){
								asmData<<$1->getName()<<"  DW "<<$3->getName()<<"  dup( ?)"<<endl;
							}
							else {
								int len=stoi($3->getName().c_str());
								$1->offset=currentOffset;
								currentOffset+=2*len;
								for(int i=0;i<len;i++){
									asmCode<<"\tPUSH 0\n";
									numberOfPushes++;
								}
							}
			/****************************************************************************/
				$1->setLen(atoi($3->getName().c_str()));
				$1->setType("array");
				if(!table->Insert($1)){
					printError("Multiple declaration of",$1->getName());
				}
				printMSG("declaration_list :ID LTHIRD CONST_INT RTHIRD",$$->getName());
				declared_varList.push_back($1);
				}
 		  ;
 		  
statements : statement
		{$$ = $1;
	 	logfile2<<"Line "<<line_count<<": statements : statement"<<endl<<endl<<$$->getName()<<endl<<endl;
	 
	 }| statements statement{
	 	$$ = new SymbolInfo($1->getName()+"\n"+$2->getName(),"statement");
		
	 	logfile2<<"Line "<<line_count<<": statements : statements statement"<<endl<<endl<<$$->getName()<<endl<<endl;
	 }
	   ;
	   
statement : var_declaration
		{
	 	
	 	$$ = $1;
		asmCode<<"; statement : var_declaration"<<endl;
	 	logfile2<<"Line "<<line_count<<": statement : var_declaration"<<endl<<endl<<$$->getName()<<endl<<endl;
	 }
	  | expression_statement
	  {
	 	
	 	$$ = $1;
	 	logfile2<<"Line "<<line_count<<": statement : expression_statement"<<endl<<endl<<$$->getName()<<endl<<endl;
	 }
	  | compound_statement{
	 	
	 	$$ = $1;
	 	logfile2<<"Line "<<line_count<<": statement : compound_statement"<<endl<<endl<<$$->getName()<<endl<<endl;
	 }
	  | FOR LPAREN expression_statement{
		forLoopStart=string(newLabel()),ENDLOOP=string(newLabel()),LoopLabel=string(newLabel());
		IncLabel=string(newLabel());
		asmCode<<forLoopStart<<":\n";
	  } expression_statement{
		asmCode<<"\tCMP AX,0\n\tJE "<<ENDLOOP<<"\n\tJMP "<<LoopLabel<<endl<<IncLabel<<":"<<endl;
	  } expression RPAREN{
		asmCode<<"\tJMP "<<forLoopStart<<endl<<LoopLabel<<":\n";
	  } statement{
		$$ = new SymbolInfo("for("+$3->getName()+$5->getName()+$7->getName()+")"+$10->getName(),"for");	 	
	 	logfile2<<"Line "<<line_count<<": statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement"<<endl<<endl<<$$->getName()<<endl<<endl;
		asmCode<<"\tJMP "<<IncLabel<<endl<<ENDLOOP<<":"<<endl;
		asmCode<<";OK SAKIN"<<endl;
		
	 //MARKER1
	  }
	  |CONDITIONAL_STATEMENT RPAREN statement %prec  LOWER_THAN_ELSE {
	 	$$ = new SymbolInfo($1->getName()+")"+$3->getName(),"if");	 		 	
	 	logfile2<<"Line "<<line_count<<": statement : IF LPAREN expression RPAREN statement"<<endl<<endl<<$$->getName()<<endl<<endl;
	 	asmCode<<"\t"<<conditionEnd<<":"<<endl;

	 }
	  | CONDITIONAL_STATEMENT RPAREN statement ELSE{
		asmCode<<";CONDITIONAL_STATEMENT RPAREN statement ELSE"<<endl;
		elseLabel=conditionEnd;
		conditionEnd=string(newLabel());
		
		asmCode<<"\tJMP "<<conditionEnd<<endl;
	  	conditionStack.push(conditionEnd);
		asmCode<<"\t"<<elseLabel<<":"<<endl;
	  }  statement{
		asmCode<<";CONDITIONAL_STATEMENT RPAREN statement ELSE statement"<<endl;
	 	$$ = new SymbolInfo($1->getName()+")"+$3->getName()+"else"+$6->getName(),"if");
	 	logfile2<<"Line "<<line_count<<": statement : IF LPAREN expression RPAREN statement ELSE statement"<<endl<<endl<<$$->getName()<<endl<<endl;
	 	conditionEnd=conditionStack.top();
		conditionStack.pop();
		asmCode<<"\t"<<conditionEnd<<":"<<endl;

	 }
	  | WHILE{
		asmCode<<";WHILE LPAREN EXPRESSION RPAREN"<<endl;
		whileLabel=string(newLabel()),whileEnd=string(newLabel());
		asmCode<<"\t"<<whileLabel<<":"<<endl;
	  } LPAREN expression{
		asmCode<<"\tCMP AX,0\n\tJE "<<whileEnd<<endl;
	  } RPAREN statement{
	 	$$ = new SymbolInfo("while("+$4->getName()+")"+$7->getName(),"while");
	 	logfile2<<"Line "<<line_count<<": statement : WHILE LPAREN expression RPAREN statement"<<endl<<endl<<$$->getName()<<endl<<endl;
	 	asmCode<<"\tJMP "<<whileLabel<<"\n\t"<<whileEnd<<":"<<endl;
	 }
	  | PRINTLN LPAREN ID RPAREN SEMICOLON{

	 	$$ = new SymbolInfo("printf("+$3->getName()+");","print");
	 	asmCode<<"; PRINT STATEMENT"<<endl;
	 	logfile2<<"Line "<<line_count<<": statement : PRINTLN LPAREN ID RPAREN SEMICOLON"<<endl<<endl;
	 	if(table->LookUp($3->getName()) == nullptr){
	 		errorfile<<"Error at line "<<line_count<<" : Undeclared variable "<< ($3->getName())<<endl<<endl;error_count++;	
  			logfile2<<"Error at line "<<line_count<<" : Undeclared variable "<< ($3->getName())<<endl<<endl;  
	 	}
	 	logfile2<<$$->getName()<<endl<<endl;

		/******************************ICG CODE********************************************/
		if(table->LookUp($3->getName())->getScopeTableID()=="1")
			asmCode<<"\tMOV AX,"<<$3->getName()<<endl;
		else
			asmCode<<"\tMOV AX,[BP-"<<table->LookUp($3->getName())->offset<<"]"<<endl;
		asmCode<<"\tCALL PRINT_FUNC"<<endl;
		/*********************************************************************************/
	 }
	  | RETURN expression SEMICOLON{
	 	$$ = new SymbolInfo($1->getName()+space+$2->getName()+" ;","return");	 	
		asmCode<<"; RETURN STATEMENT"<<endl;
	 	logfile2<<"Line "<<line_count<<": statement : RETURN expression SEMICOLON"<<endl<<endl<<$$->getName()<<endl<<endl;
	 	/******************************ICG CODE*******************************/
		asmCode<<"\tMOV FUNC_RETURN_VALUE,AX"<<endl;

		for(int i=0;i<numberOfPushes;i++)
			asmCode<<"POP AX"<<endl;
		asmCode<<";NUMBER OF PUSHES CURRENTLY DONE "<<numberOfPushes<<endl;
		asmCode<<"POP TEMPORARY_VALUE\nPOP t1\nPOP t0\nPOP DI\nPOP SI\nPOP DX\nPOP CX\nPOP BX\nPOP AX\n";
	 	asmCode<<endMSG<<endl;
	 }|error{
		yyerror;
		yyerrok;
		yyclearin;
	 }
	  ;
CONDITIONAL_STATEMENT  :IF LPAREN expression{
	//MARKER2
	$$ = new SymbolInfo("if("+$3->getName(),"");
	asmCode<<"; IF STATEMENT"<<endl;
	 conditionEnd=string(newLabel());
	 
		asmCode<<"\tCMP AX,0\n\tJE "<<conditionEnd<<endl;
	  }	  
expression_statement 	: SEMICOLON	{$$ = new SymbolInfo(";","expression");
	
}		
			| expression SEMICOLON {
	 	$$ = new SymbolInfo($1->getName()+";","expression");
	 	asmCode<<";"<<"EXPRESSION"<<endl;
	 	logfile2<<"Line "<<line_count<<": expression_statement : expression SEMICOLON"<<endl<<endl<<$$->getName()<<endl<<endl;
	 } 
			;
	  
variable : ID {
	 	$$ = new SymbolInfo($1->getName(),"variable");	 	
	 	
	 	SymbolInfo* currentSymbol = table->LookUp($1->getName());
		
	 	if(currentSymbol == NULL){
  			errorfile<<"Error at line "<<line_count<<" : Undeclared variable "<< ($1->getName())<<endl<<endl;error_count++;	
  			logfile2<<"Error at line "<<line_count<<" : Undeclared variable "<< ($1->getName())<<endl<<endl;  				  		
  		}  		
  		else{
  			$$->setType(currentSymbol->typeOfVar); 
						
  			
  			string str($1->getName());
  			if(currentSymbol->getType() == "array" ){
  				 
  				errorfile<<"Error at line "<<line_count<<" : Type Mismatch, "<<$1->getName()<<" is an array"<<endl<<endl; error_count++;
				logfile2<<"Error at line "<<line_count<<" : Type Mismatch, "<<$1->getName()<<" is an array"<<endl<<endl;
  			}
	  		/*******************************ICG CODE****************************************************/
				if(currentSymbol->getScopeTableID()=="1"){
					asmCode<<"\tLEA SI,"<<currentSymbol->getName()<<endl;
					$$->isGlobal=true;
				}
				else{
					asmCode<<"\tMOV SI,-"<<currentSymbol->offset<<endl;
				}
			/********************************************************************************/	 	
  		}
		logfile2<<"Line "<<line_count<<": variable : ID"<<endl<<endl;	  		
	 	logfile2<<$$->getName()<<endl<<endl;

	 }			
	 | ID LTHIRD expression RTHIRD {
	 	$$ = new SymbolInfo($1->getName()+"["+$3->getName()+"]","var");
	 	SymbolInfo* currentSymbol = table->LookUp($1->getName());
	 	if(currentSymbol == NULL){
  			errorfile<<"Error at line "<<line_count<<" : Undeclared variable "<< ($1->getName())<<endl<<endl;error_count++;	
  			logfile2<<"Error at line "<<line_count<<" : Undeclared variable "<< ($1->getName())<<endl<<endl;
  			 		
  		}
	 	else{	 		
			$$->setType(currentSymbol->typeOfVar); 
			if($$->getType()=="")
				printError("************************",""); 	 
		 	printMSG("variable :ID LTHIRD expression RTHIRD",$$->getName());
		 	if(currentSymbol->getLen()<2){
		 		errorfile<<"Error at line "<<line_count<<" : "<<$1->getName()<<" not an array"<<endl<<endl;error_count++;
		 		logfile2<<"Error at line "<<line_count<<" : "<<$1->getName()<<" not an array"<<endl<<endl;
		 	}
		 	else if($3->getType() != "CONST_INT"){
		 		errorfile<<"Error at line "<<line_count<<" : Expression inside third brackets not an integer"<<endl<<endl;error_count++;
		 		logfile2<<"Error at line "<<line_count<<" :Expression inside third brackets not an integer"<<endl<<endl;
		 	}
			// else if(currentSymbol->getLen()>=atoi($3->getName().c_str())){
			// 	errorfile<<"Error at line "<<line_count<<" : Out of Bound Index"<<endl<<endl;error_count++;
		 	// 	logfile2<<"Error at line "<<line_count<<" :Out of Bound Index"<<endl<<endl;
			// }		 	
	 		/*******************************ICG CODE****************************************************/
				if(currentSymbol->getScopeTableID()=="1"){
					asmCode<<"\tLEA SI,"<<currentSymbol->getName()<<endl;
					asmCode<<"\tADD SI,"<<atoi($3->getName().c_str())*2<<endl;
					$$->isGlobal=true;
				}
					
				else{
					asmCode<<"\tMOV SI,-"<<currentSymbol->offset+2*atoi($3->getName().c_str())<<endl;
					asmCode<<";CURRENT OFFSET"<<currentSymbol->offset<<endl;
				}
			/********************************************************************************/	 	
		}
	 	
	 } 
	 ;
	 
 expression : logic_expression	{
	 	
	 	$$ = $1;
	 	logfile2<<"Line "<<line_count<<": expression : logic_expression	"<<endl<<endl<<$$->getName()<<endl<<endl;
	 	asmCode<<"; expression : logic_expression	"<<endl<<endl;
	 	
	 }
	   | variable{
		asmCode<<"\tMOV DI,SI"<<endl;
	   } ASSIGNOP logic_expression {
		//TODO
	$$ = new SymbolInfo($1->getName()+$3->getName()+$4->getName(),$1->getType());
	asmCode<<";"<<$$->getName()<<endl;
	string v_type = $1->getType();
	string log_exp_type = $4->getType();
	
	if($4->getType()=="VOID"){
			printError("Type Mismatch: cannot assign to VOID type",$$->getName());
	} else {
		
		// if(v_type!=log_exp_type)
		// {

		// 	printError("Type Mismatch-1"+v_type+log_exp_type,$$->getName());
		// }
		if((v_type=="CONST_INT")&&(log_exp_type=="CONST_FLOAT"))
		{
			printError("Type Mismatch-3",$$->getName());
		}
	}

	printMSG("expression : variable ASSIGNOP logic_expression",$$->getName());

	/*******************************ICG CODE****************************************************/
				asmCode<<"\t;******************************"<<endl;
				if($1->isGlobal){
					asmCode<<"MOV [DI],AX"<<endl;
				}
				else{
					
					asmCode<<"\tMOV [BP+DI], AX"<<endl;
					}
			

	/********************************************************************************/	 	
	 }	
	   ;
			
logic_expression : rel_expression 	{
	 
	 	$$ = $1;
	 	logfile2<<"Line "<<line_count<<": logic_expression : rel_expression"<<endl;
	 	asmCode<<"; logic_expression : rel_expression"<<endl<<endl<<endl;
	 	
	 }
		 | rel_expression {
			asmCode<<"; logic_expression :rel_expression LOGICOP rel_expression"<<endl<<endl<<endl;
	 	
			asmCode<<"\tPUSH AX"<<endl;
			numberOfPushes++;
		 } LOGICOP rel_expression {
	 	$$ = new SymbolInfo($1->getName()+$3->getName()+$4->getName(),"expression");
	 	// logfile2<<"Line "<<line_count<<": logic_expression : rel_expression LOGICOP rel_expression"<<endl<<endl;
	 	if(($1->getType() == "CONST_INT" || $1->getType() == "CONST_FLOAT") && ($1->getType() == "CONST_INT" || $1->getType() == "CONST_FLOAT")) {$$->setType("CONST_INT");}
	 	if($3->getType() == "VOID" || $1->getType() == "VOID"){
			errorfile<<"Error at line "<<line_count<<" : Void function used in expression "<<endl<<endl; error_count++;
			logfile2<<"Error at line "<<line_count<<" : Void function used in expression "<<endl<<endl;
			$$->setType($1->getType());
		}
		else if($1->returnTypeOfFunction == "VOID" || $4->returnTypeOfFunction == "VOID"){
			errorfile<<"Error at line "<<line_count<<" : Void function used in expression "<<endl<<endl; error_count++;
			logfile2<<"Error at line "<<line_count<<" : Void function used in expression "<<endl<<endl;
			$$->setType($3->getType());
		} 
	 	logfile2<<"Line "<<line_count<<": logic_expression : rel_expression LOGICOP rel_expression"<<endl<<endl<<$$->getName()<<endl<<endl;
	 	/**********************ICG CODE***********************************************/
		asmCode<<"\tPOP BX"<<endl;
		numberOfPushes--;
		string sign=$3->getName();
		string label1=string(newLabel()),label2=string(newLabel());
		if(sign== "&&"){
		asmCode<< "\tCMP BX, 0 \n\tJE "<<label1<<"\n\tCMP AX, 0\n\tJE "<<label1<<"\n MOV AX, 1\n\t JMP "<<label2<<"\n"<<label1<<":\n\tMOV AX,0\n"<<label2<<":"<<endl;
		}
		else{
		asmCode<< "\tCMP BX, 1 \n\tJE "<<label1<<"\n\tCMP AX, 1\n\tJE "<<label1<<"\n MOV AX, 0\n\t JMP "<<label2<<"\n"<<label1<<":\n\tMOV AX,1\n"<<label2<<":"<<endl;
		}

		/******************************************************************************/
	 
	 }	
		 ;
			
rel_expression	: simple_expression {
	 	
	 	$$ = $1;
	 	logfile2<<"Line "<<line_count<<": rel_expression : simple_expression"<<endl<<endl<<$$->getName()<<endl<<endl;
	 	asmCode<<"; rel_expression :  simple_expression"<<endl;
	 }		
		| simple_expression{
			asmCode<<"MOV T3,AX\nMOV AX,T1\n";
			asmCode<<"\tMOV MY_STACKINPUT,AX\nMOV AX,T3"<<endl;
		asmCode<<"\tCALL MY_PUSH"<<endl;
			asmCode<<"\tMOV t1,AX"<<endl;
			asmCode<<"; rel_expression : simple_expression RELOP simple_expression"<<endl;
		} RELOP simple_expression	{
	 	$$ = new SymbolInfo($1->getName()+$3->getName()+$4->getName(),"expression");
	 	
	 	if(($1->getType() == "CONST_INT" || $1->getType() == "CONST_FLOAT") && ($1->getType() == "CONST_INT" || $1->getType() == "CONST_FLOAT")) {$$->setType("CONST_INT");$$->setType("CONST_INT");}
	 	// logfile2<<"Line "<<line_count<<": rel_expression : simple_expression RELOP simple_expression"<<endl<<endl;
	 	if($1->returnTypeOfFunction == "VOID" || $4->returnTypeOfFunction == "VOID"){
			errorfile<<"Error at line "<<line_count<<" : Void function used in expression "<<endl<<endl; error_count++;
			logfile2<<"Error at line "<<line_count<<" : Void function used in expression "<<endl<<endl;
			$$->setType($1->getType());
		}else if($1->getType() == "VOID" || $4->getType() == "VOID"){
			errorfile<<"Error at line "<<line_count<<" : Void function used in expression "<<endl<<endl; error_count++;
			logfile2<<"Error at line "<<line_count<<" : Void function used in expression "<<endl<<endl;
			$$->setType($1->getType());
		}
	/******************************ICG CODE***************************************************/
	//todo
	//marker
	asmCode<<"\tMOV DX,t1"<<endl;
	asmCode<<"CALL MY_POP"<<endl;
	asmCode<<"MOV T3,AX\n";
	asmCode<<"MOV AX,MY_STACKOUTPUT"<<endl;
	asmCode<<"MOV T1,AX\nMOV AX,T3\n";
	asmCode<<"\tCMP DX,AX"<<endl;
	string sign=$3->getName();
	string label1=string(newLabel()),label2=string(newLabel());
	if(sign=="<"){
		asmCode<<"\tJL "<<label1<<endl<<"\tMOV AX,0"<<endl<<"\tJMP "<<label2<<endl;
	}
	else if(sign=="<="){
		asmCode<<"\tJLE "<<label1<<endl<<"\tMOV AX,0"<<endl<<"\tJMP "<<label2<<endl;
	}
	else if(sign==">"){
		asmCode<<"\tJG "<<label1<<endl<<"\tMOV AX,0"<<endl<<"\tJMP "<<label2<<endl;
	}
	else if ( sign==">="){
		asmCode<<"\tJGE "<<label1<<endl<<"\tMOV AX,0"<<endl<<"\tJMP "<<label2<<endl;
	}
	else if(sign=="=="){	asmCode<<"\tJE "<<label1<<endl<<"\tMOV AX,0"<<endl<<"\tJMP "<<label2<<endl;
	}
	else if(sign=="!="){
		asmCode<<"\tJNE "<<label1<<endl<<"\tMOV AX,0"<<endl<<"\tJMP "<<label2<<endl;
	}
	asmCode<<label1<<":"<<"\tMOV AX,1"<<endl<<label2<<":"<<endl;
	/****************************************************************************************/
	 	printMSG("rel_expression :simple_expression RELOP simple_expression",$$->getName());
	 } 	
		;
				
simple_expression : term {
	 	$$ = $1;
	 	logfile2<<"Line "<<line_count<<": simple_expression : term"<<endl<<endl<<$$->getName()<<endl<<endl;
		asmCode<<"; simple_expression : term"<<endl;
		
	
	 }
		  | simple_expression{
		/***************************************ICG CODE **********************************/
		asmCode<<"; simple_expression : simple_expression ADDOP term"<<endl;
		asmCode<<"\tMOV MY_STACKINPUT,CX"<<endl;
		asmCode<<"\tCALL MY_PUSH"<<endl;
		asmCode<<"\tMOV CX,AX"<<endl;
		/*********************************************************************************/
		  } ADDOP term {
	 	$$ = new SymbolInfo($1->getName()+$3->getName()+$4->getName(),"expression");
		asmCode<<"; simple_expression : simple_expression ADDOP term"<<$$->getName()<<endl;
	 	logfile2<<"Line "<<line_count<<": simple_expression : simple_expression ADDOP term"<<endl<<endl;
	 	if($4->returnTypeOfFunction == "VOID" || $1->returnTypeOfFunction == "VOID"){
			errorfile<<"Error at line "<<line_count<<" : Void function used in expression "<<endl<<endl; error_count++;
			logfile2<<"Error at line "<<line_count<<" : Void function used in expression "<<endl<<endl;			
		}
		else if($4->getType() == "VOID" || $1->getType() == "VOID"){
			errorfile<<"Error at line "<<line_count<<" : Void function used in expression "<<endl<<endl; error_count++;
			logfile2<<"Error at line "<<line_count<<" : Void function used in expression "<<endl<<endl;			
		}	 	
	 	if($1->getType() == "CONST_FLOAT" || $4->getType() == "CONST_FLOAT"){$$->setType("CONST_FLOAT");}
	 	else {$$->setType("CONST_INT");}
	 	logfile2<<$$->getName()<<endl<<endl;
		/***************************************ICG CODE **********************************/
		if($3->getName()=="+")
				asmCode<<"\tADD AX,CX"<<endl;
		else{
			asmCode<<"\tSUB AX,CX"<<endl;
			asmCode<<"\tNEG AX"<<endl;
		}
		asmCode<<"CALL MY_POP"<<endl;
		asmCode<<"MOV CX,MY_STACKOUTPUT"<<endl;
		/*********************************************************************************/
	 } 
		  ;
					
term :unary_expression{
			$$ = $1;
			logfile2<<"Line "<<line_count<<": term : unary_expression"<<endl<<endl<<$$->getName()<<endl<<endl;
			/*****************************ICG CODE *******************************************/
			asmCode<<"; term : unary_expression"<<endl;
				
				asmCode<<"\tPOP AX "<<endl;
				numberOfPushes--;
			/********************************************************************************/
		}
     |  term {
		asmCode<<"; term : term MULOP unary_expression"<<endl;
		asmCode<<"MOV T3,AX\nMOV AX,T0\n";
		asmCode<<"\tMOV MY_STACKINPUT,AX\nMOV AX,T3"<<endl;
		asmCode<<"\tCALL MY_PUSH"<<endl;
		asmCode<<"\tMOV t0,AX"<<endl;
	 }MULOP unary_expression{
			$$ = new SymbolInfo($1->getName()+$3->getName()+$4->getName(),"expression");
			asmCode<<"; term : term MULOP unary_expression"<<$$->getName()<<endl;	
			logfile2<<"Line "<<line_count<<": term : term MULOP unary_expression"<<endl<<endl;
			if($3->getName() == "%"){
				if($1->getType() != "CONST_INT" || $4->getType() != "CONST_INT"){
					errorfile<<"Error at line "<<line_count<<" : Non-Integer operand on modulus operator "<<endl<<endl; error_count++;
					logfile2<<"Error at line "<<line_count<<" : Non-Integer operand on modulus operator "<<endl<<endl;
					$$->setType("undefined");
				}
				else if($4->getName() == "0"){
					errorfile<<"Error at line "<<line_count<<" : Modulus by Zero "<<endl<<endl; error_count++;
					logfile2<<"Error at line "<<line_count<<" : Modulus by Zero"<<endl<<endl;
					$$->setType("undefined");
				}
				else {$$->setType("CONST_INT");}
			}
			else if($4->getType() == "VOID" || $1->getType() == "VOID"){
				errorfile<<"Error at line "<<line_count<<" : Void function used in expression "<<endl<<endl; error_count++;
				logfile2<<"Error at line "<<line_count<<" : Void function used in expression "<<endl<<endl;
				$$->setType($1->getType());
			}		
			else if($1->getType() == "CONST_FLOAT" || $4->getType() == "CONST_FLOAT"){
				$$->setType("CONST_FLOAT");
			}	
			else {$$->setType("CONST_INT");}
			logfile2<<$$->getName()<<endl<<endl;		

			/*****************************ICG CODE *******************************************/
				asmCode<<"\tPOP BX"<<endl;
				asmCode<<"\tMOV AX,t0"<<endl;
				asmCode<<"CALL MY_POP"<<endl;
				asmCode<<"MOV T3,AX\n";
				asmCode<<"MOV AX,MY_STACKOUTPUT\nMOV T0,AX\nMOV AX,T3"<<endl;
				numberOfPushes--;
				if($3->getName()=="*")	
					asmCode<<"\tMUL BX "<<endl;
				else if($3->getName()=="%"){
					asmCode<<"\tPUSH DX"<<endl;
					numberOfPushes++;
					asmCode<<"\n\tXOR DX, DX"<<endl;
					asmCode<<"\tDIV BX\n\tMOV AX, DX\n\n\tPOP DX"<<endl;
					numberOfPushes--;
				}else{
					asmCode<<"\tPUSH DX"<<endl;
					numberOfPushes++;
					asmCode<<"\n\tXOR DX, DX"<<endl;
					asmCode<<"\tDIV BX\n\n\tPOP DX"<<endl;
					numberOfPushes--;
				}
			/********************************************************************************/			
			
				
		
		}
     ;

unary_expression : ADDOP unary_expression {
    		$$ = new SymbolInfo($1->getName()+$2->getName(),$2->getType());
		 	logfile2<<"Line "<<line_count<<": unary_expression : ADDOP unary_expression"<<endl<<endl<<$$->getName()<<endl<<endl;
		 	/*****************************ICG CODE ***************************************/
			if($1->getName()=="-"){
				asmCode<<"\tPOP BX"<<endl;
				numberOfPushes--;
				asmCode<<"\tNEG BX"<<endl;
				asmCode<<"\tPUSH BX"<<endl;
				numberOfPushes++;
			}
			/****************************************************************************/
		 }   
		 | NOT unary_expression {
    		$$ = new SymbolInfo("!"+$2->getName(),$2->getType());    		
		 	logfile2<<"Line "<<line_count<<": unary_expression : NOT unary_expression"<<endl<<endl<<$$->getName()<<endl<<endl;
		 	/*****************************ICG CODE ***************************************/
			    asmCode<<"\tPOP BX"<<endl;
				numberOfPushes--;
				asmCode<<"\tNOT [SP]"<<endl;
				asmCode<<"\tPUSH BX"<<endl;
				numberOfPushes++;
			
			/****************************************************************************/
		 }
		 | factor  {   		
		 	$$ = $1;
		 	logfile2<<"Line "<<line_count<<": unary_expression : factor"<<endl<<endl<<$$->getName()<<endl<<endl;		 	
		 	
		 }
		 ;
	
factor	: variable {
			$$ = $1;		 	
		 	logfile2<<"Line "<<line_count<<": factor : variable"<<endl<<endl<<$$->getName()<<endl<<endl;		
			/*****************************ICG CODE *******************************************/
				if($1->isGlobal){
					asmCode<<"\t PUSH [SI] "<<endl;
					numberOfPushes++;
				}
				else {
					asmCode<<"\t PUSH [BP-SI] "<<endl;
					numberOfPushes++;
				}
			/********************************************************************************/
		}
	| ID LPAREN argument_list RPAREN {
		//TODO
		$$=new SymbolInfo($1->getName()+space+"("+space+$3->getName()+space+")",$1->returnTypeOfFunction);
		printMSG("factor : ID LPAREN argument_list RPAREN",$$->getName());


		SymbolInfo* currentSymbol = table->LookUp($1->getName());
		/****************ICG CODE**************************/
		
		asmCode<<"\tMOV TEMPORARY_VALUE,BP\n\tMOV BP,SP\nADD BP,"<<$3->functionParameterList.size()*2<<endl;
		
		
		asmCode<<"\tCALL "<<$1->getName()<<"\n\tMOV BP, TEMPORARY_VALUE"<<endl;
		asmCode<<"\tPUSH FUNC_RETURN_VALUE"<<endl;
		numberOfPushes++;
		/*********************************************************/
		if(currentSymbol==NULL){
			printError("Undeclared or Undefined Function",$1->getName());
			$3->functionParameterList.clear();
		} else {
			if(currentSymbol->typeOfID=="FUNCTION"){
				if(currentSymbol->isFunction)
				{
					//CHECK NUMER OF ARGUMENTS ARE EQUAL!!!
					int given_arg_list = $4->functionParameterList.size();
					int defined_arg_list = currentSymbol->functionParameterList.size();

					if(given_arg_list!=defined_arg_list){
						printError(" Total number of arguments mismatch in function",$1->getName());
						errorfile<<given_arg_list<<" "<<defined_arg_list<<endl;
						$3->functionParameterList.clear();
					}else{
						//CHECK FOR ARGUMENT SEQUENCE OF DEFINED AND CALLED FUNCTION
						
						for(int i=0;i<defined_arg_list;i++)
						{
							string temp1 = $3->functionParameterList[i].second;
							string temp2 = currentSymbol->functionParameterList[i].second;
							
							if(conversionError(temp1,temp2))
							{
								printError(to_string(i+1)+"th argument mismatch"+temp1+","+temp2+"in function func\n",$$->getName());
								break;
							}
						}
						$3->functionParameterList.clear();
					}

					$$->setType(currentSymbol->returnTypeOfFunction);
					$$->typeOfID = currentSymbol->typeOfID;
				} else {
					printError("function not properly defined or declared","");
					$$->setType(currentSymbol->returnTypeOfFunction);
					$$->typeOfID = currentSymbol->typeOfID;
				}
			} else{
				printError("Function call on Non function ID","");
				$$->setType("CONST_INT");
				
			}
		

		}
		
		}
	| LPAREN expression RPAREN{
	
	$$=new SymbolInfo("("+$2->getName()+")",$2->getType());
	printMSG("factor : LPAREN expression RPAREN",$$->getName());
	asmCode<<"\tPUSH AX"<<endl;
	numberOfPushes++;
}
	| CONST_INT {
			$$ = $1;						
			logfile2<<"Line "<<line_count<<": factor : CONST_INT"<<endl<<endl<<$$->getName()<<endl<<endl;
			/*******************************ICG CODE****************************************************/

				asmCode<<"\tPUSH "<<$1->getName()<<endl;
				numberOfPushes++;
				

			/********************************************************************************/	 	
		}
	| CONST_FLOAT
	{
			$$ = $1;			
			logfile2<<"Line "<<line_count<<": factor : CONST_FLOAT"<<endl<<endl<<$$->getName()<<endl<<endl;
			/*******************************ICG CODE****************************************************/

				asmCode<<"\tPUSH"<<$1->getName()<<endl;
				numberOfPushes++;

			/********************************************************************************/
		
		}
	| variable INCOP {
			$$ = new SymbolInfo($1->getName()+$2->getName(),$1->getType());
		 	logfile2<<"Line "<<line_count<<": factor : variable INCOP"<<endl<<endl<<$$->getName()<<endl<<endl;		
			/*****************************ICG CODE*****************/
			
			if($1->isGlobal){
				
				asmCode<<"\tPUSH [SI]"<<endl;
				numberOfPushes++;
				asmCode<<"\tINC [SI]"<<endl;
			}
				else {
					
					asmCode<<"\t PUSH [BP+SI] "<<endl;
					numberOfPushes++;
					asmCode<<"\tINC [BP+SI]"<<endl;
				}
			

		}
	| variable DECOP{
			$$ = new SymbolInfo($1->getName()+$2->getName(),$1->getType());
		 	logfile2<<"Line "<<line_count<<": factor : variable DECOP"<<endl<<endl<<$$->getName()<<endl<<endl;		
			/*****************************ICG CODE*****************/
			if($1->isGlobal){
				
				asmCode<<"\tPUSH [SI]"<<endl;
				numberOfPushes++;
				asmCode<<"\tINC [SI]"<<endl;
			}
				else {
					
					asmCode<<"\t PUSH [BP+SI] "<<endl;
					numberOfPushes++;
					asmCode<<"\tDEC [BP+SI]"<<endl;
				}
		} 	
	
	;
	
argument_list : arguments{

		$$=$1;
		printMSG("argument_list : arguments",$$->getName());
	}
	|{$$=new SymbolInfo("","");printMSG("argument_list : arguments");}
			  ;
	
arguments : arguments COMMA logic_expression {
	
	$$=new SymbolInfo($1->getName()+","+$3->getName(),"");
	printMSG("arguments : arguments COMMA logic_expression",$$->getName());
	string name = $3->getName();
	string variable_type = $3->getType();

	if($3->typeOfVar == "VOID"||$3->getType() == "VOID")
	{
		printError("Void passed as parameter","");
	}else{
		$$->functionParameterList=$1->functionParameterList;  
		$$->functionParameterList.push_back(make_pair(name,variable_type));
		asmCode<<"\tPUSH AX"<<endl;
		numberOfPushes++;
	}

	
}
	      | logic_expression{
			$$=new SymbolInfo($1->getName(),"");
			string name = $1->getName();
			string variable_type = $1->getType();
			printMSG("arguments : logic_expression",$$->getName());
			$$->functionParameterList.push_back(make_pair(name,variable_type));
		  	asmCode<<"\tPUSH AX"<<endl;
			numberOfPushes++;
		  }
	      ;

%%
int main(int argc,char *argv[])
{
	cout<<"staring.............."<<endl;
	table=new SymbolTable(30);
	cout<<"table created...."<<endl;
	table->EnterScope();
	if((fp=fopen(argv[1],"r"))==NULL)
	{
		printf("Cannot Open Input File sakib.\n");
		exit(1);
	}
	cout<<"opened............."<<endl;
	// fp2= fopen(argv[2],"w");
	// fclose(fp2);
	// fp3= fopen(argv[3],"w");
	// fclose(fp3);
	
	// fp2= fopen(argv[2],"a");
	// fp3= fopen(argv[3],"a");
	

	yyin=fp;
	yyparse();
	

	// fclose(fp2);
	// fclose(fp3);
	cout<<"*********************************"<<endl;
	table->printAllLex(logfile2);
	delete table;
	logfile2<<"Total lines: "<<line_count-1<<endl;

	logfile2<<"Total errors: "<<error_count<<endl;
	return 0;
}

