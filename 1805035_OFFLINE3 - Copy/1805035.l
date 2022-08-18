%option noyywrap noline

%x StringLiterals
%x SingleComment
%x MultilineComment
%x CharLiterals
%x CharLiteralsPhase2

%{
#include<bits/stdc++.h>    
// #include "ScopetableFiles/requestProcessor.cpp"
#include "SymbolInfo.h"
#include "y.tab.h"

using namespace std;

int line_count=1,error_count=0;
string stringInput="";
string comment="";
char charInput;
ofstream token;
ofstream logfile;
//requestProcessor* //RP;


string unescape(const string& s)
{
  string res;
  string::const_iterator it = s.begin();
  while (it != s.end())
  {
    char c = *it++;
    if (c == '\\' && it != s.end())
    {
      switch (*it++) {
      case '\\': c = '\\'; break;
      case 'n': c = '\n'; break;
      case 't': c = '\t'; break;
      // all other escapes
      case 'a': c='\a';break;
      case 'f':c='\f'; break;
      case 'r' :c='\r';break;
      case 'v' :c='\v';break;
      case '0' :c='\0';break;
      case 'b' :c='\b';break;
      case '\'' :c='\'';break;
      case '\"' :c='\"';break;
      default: 
        // invalid escape sequence - skip it. alternatively you can copy it as is, throw an exception...
        continue;
      }
    }
    res += c;
  }
 
  return res;
}


int unescape2(const string& s)
{
  string res;
  string::const_iterator it = s.begin();
  while (it != s.end())
  {
    char c = *it++;
    if (c == '\\' && it != s.end())
    {
      switch (*it++) {
      case '\\': c='\\'; break;
      case 'n': c = '\n'; break;
      case 't': c = '\t'; break;
      // "\\\\"|"\\'"|"\\a"|"\\f"|"\\r"|"\\b"|"\\v"|"\\0"
      case 'a': c='\a';break;
      case 'f':c='\f'; break;
      case 'r' :c='\r';break;
      case 'v' :c='\v';break;
      case '0' :c='\0';break;
      case 'b' :c='\b';break;
      case '\'' :c='\'';break;

      default: 
        // invalid escape sequence - skip it. alternatively you can copy it as is, throw an exception...
        continue;
      }
    }
    return c;
  }
 
  return 0;
}
%}

DIGIT [0-9]
ALPHA [a-zA-Z]
WHITESPACE [ \t\f\r\v]+ 
NEWLINE (\r\n)|\n
ADDOP [+-]
MULOP "*"|"%"|"/"
INCOP "++"
DECOP "--"
RELOP "<"|"<="|">"|">="|"=="|"!="
LOGICOP "&&"|"||"
NOT	"!"
LPAREN "\("
ASSIGNOP =
RPAREN "\)"

LTHIRD "\["
RTHIRD "\]"
COMMA  ,
SEMICOLON ;
KEYWORD if|char|else|default|for|do|int|float|void|switch|while|break|double|return|case|continue|println
UNDERSCORE _
IDENTIFIERS (({ALPHA}|{UNDERSCORE})({UNDERSCORE}|{DIGIT}|{ALPHA})*)
ERROR_IDENTIFIERS ({DIGIT}+({UNDERSCORE}|{ALPHA})+)

ESCAPE_STR_SEQ   "\\n"|"\\t"|"\\\\"|"\\'"|"\\a"|"\\f"|"\\r"|"\\b"|"\\v"|"\\0"
FLOAT [0-9]*[.][0-9]+([Ee][+-]?[0-9]+)?
ILL_FORMED_FLOAT {FLOAT}([.][0-9]+([Ee][+-]?[0-9]+)?)+

%%
{NEWLINE} {line_count++;}

{ILL_FORMED_FLOAT} {logfile<<"Error at line number :"<<line_count<<"Too many decimal point error or Ill formed number"<<endl;error_count++;}
{WHITESPACE} {}
\/\/ {BEGIN SingleComment;comment="";}
<SingleComment>.* {comment=yytext;logfile<<"Line No. "<<line_count<<"<SINGLELINE_COMMENT,"<<yytext<<"> "<<endl; }
<SingleComment>{NEWLINE} {BEGIN INITIAL;line_count++;}
\/\* {BEGIN MultilineComment;comment="";}
<MultilineComment><<EOF>>  { logfile<<"Line No. "<<line_count<<"Error at line number :"<<line_count<<"Unfinished comment UNEXPECTED ENDING"<<endl;error_count++;BEGIN INITIAL ;}
<MultilineComment>\*\/ {BEGIN INITIAL;logfile<<"Line No. "<<line_count<<"<MULTILINE_COMMENT,"<<comment<<"> "<<endl; }
<MultilineComment>{NEWLINE} {line_count++;}
<MultilineComment>([^(\*\/){NEWLINE}])* {comment+=yytext;}
{FLOAT} {token<<"< CONST_FLOAT,"<<yytext<<"> ";
        string cmd="I ";
                      cmd+=yytext;
                      cmd+=" FLOAT";
                     logfile<<"Line No. "<<line_count<<" Token :  CONST_FLOAT   Lexeme : "<<yytext<<" "<<endl;
                       //RP->processRequest(cmd,logfile);
          yylval.symbol_val=new SymbolInfo(yytext,"CONST_FLOAT");
          return  CONST_FLOAT;
        }

[0-9]+ {token<<"< CONST_INT,"<<yytext<<"> ";
        string cmd="I ";
                      cmd+=yytext;
                      cmd+=" INT";
                      //RP->processRequest(cmd,logfile);
       logfile<<"Line No. "<<line_count<<" Token :  CONST_INT   Lexeme : "<<yytext<<" "<<endl;
       yylval.symbol_val=new SymbolInfo(yytext,"CONST_INT");
       return CONST_INT;
        }
<CharLiterals>([^\'{NEWLINE}]|{ESCAPE_STR_SEQ}) {
						string s=yytext;
						if(yyleng>1){
							charInput=unescape2(s.substr(0,2));
							
							}
						else
							charInput=s[0];
            BEGIN CharLiteralsPhase2;
              
					}
' {BEGIN CharLiterals;}
<CharLiterals>\' {logfile<<"Error at line number :"<<line_count<<"Empty character constant error"<<endl;error_count++;BEGIN INITIAL;}
<CharLiteralsPhase2>\' {token<<"<CONST_CHAR,"<<charInput<<">"<<endl;
                       logfile<<"Line No. "<<line_count<<" Token : CONST_CHAR   Lexeme : "<<charInput<<" "<<endl;
                        string cmd="I ";
                          cmd+=charInput;
                          cmd+=" CONST_CHAR";
                          //RP->processRequest(cmd,logfile);
                        BEGIN INITIAL;
                        yylval.char_val=charInput;
                        return CONST_CHAR;
                        }
<CharLiteralsPhase2>({NEWLINE}) {
                                      logfile<<"Error at line number :"<<line_count<<"Unfinished character"<<endl;error_count++;
                                      line_count++;
                                      BEGIN INITIAL;
                                    }
<CharLiteralsPhase2>[^\'" "{NEWLINE}]*(\')? {BEGIN INITIAL;
                                        logfile<<"Error at line number :"<<line_count<<"Multi character constant error for character sequence "<<endl;
                                        error_count++;}
(if) {yylval.symbol_val= new SymbolInfo(yytext,"KEYWORD"); return IF;}
(for) {yylval.symbol_val= new SymbolInfo(yytext,"KEYWORD"); return FOR;}
(do) {yylval.symbol_val= new SymbolInfo(yytext,"KEYWORD"); return DO;}
(float) {yylval.symbol_val= new SymbolInfo(yytext,"KEYWORD"); return FLOAT;}
(void) {yylval.symbol_val= new SymbolInfo(yytext,"KEYWORD"); return VOID;}
(int) {yylval.symbol_val= new SymbolInfo(yytext,"KEYWORD"); return INT;}
(else) {yylval.symbol_val= new SymbolInfo(yytext,"KEYWORD"); return ELSE;}
(while) {yylval.symbol_val= new SymbolInfo(yytext,"KEYWORD"); return WHILE;}
(char) {yylval.symbol_val= new SymbolInfo(yytext,"KEYWORD"); return CHAR;}
(double) {yylval.symbol_val= new SymbolInfo(yytext,"KEYWORD"); return DOUBLE;}
(return) {yylval.symbol_val= new SymbolInfo(yytext,"KEYWORD"); return RETURN;}
(continue) {yylval.symbol_val= new SymbolInfo(yytext,"KEYWORD"); return CONTINUE;}
(println) {yylval.symbol_val= new SymbolInfo(yytext,"KEYWORD"); return PRINTLN;}

{KEYWORD} {		
				string input=yytext;
				transform(input.begin(), input.end(), input.begin(), ::toupper);
			  token<<"<"<<input<<">";
       logfile<<"Line No. "<<line_count<<" Token : "<<input<<"  Lexeme :  " <<yytext<<endl;
   
       
       }
{IDENTIFIERS} {
        token<<" <ID,"<<yytext<<">";
        string cmd="I ";
                      cmd+=yytext;
                      cmd+=" ID";
                      logfile<<"Line No. "<<line_count<<" Token : ID Lexeme : "<<yytext<<" "<<endl;
                      //RP->processRequest(cmd,logfile);
        yylval.symbol_val=new SymbolInfo(yytext,"ID");
        return ID;
				
			}

{INCOP} {token<<" <INCOP,"<<yytext<<">";
          yylval.symbol_val=new SymbolInfo(yytext,"OP");
          logfile<<"Line No. "<<line_count<<" Token : INCOP Lexeme : "<<yytext<<" "<<endl;
          return INCOP;
          }
{ADDOP} {token<<" <ADDOP,"<<yytext<<">";
        yylval.symbol_val=new SymbolInfo(yytext,"OP");
          logfile<<"Line No. "<<line_count<<" Token : ADDOP Lexeme : "<<yytext<<" "<<endl;
          return ADDOP;
          }
{LPAREN} {token<<" <LPAREN,"<<yytext<<">"<<endl;
          logfile<<"Line No. "<<line_count<<" Token : LPAREN Lexeme : "<<yytext<<" "<<endl;
          yylval.symbol_val=new SymbolInfo(yytext,"OP");
          return LPAREN;
          }
{MULOP} {token<<" <MULOP,"<<yytext<<">"<<endl;
        logfile<<"Line No. "<<line_count<<" Token : MULOP Lexeme : "<<yytext<<" "<<endl;
        yylval.symbol_val=new SymbolInfo(yytext,"OP");
        return MULOP;
        }
{RELOP} {token<<" <RELOP,"<<yytext<<">"<<endl;
        logfile<<"Line No. "<<line_count<<" Token : RELOP Lexeme : "<<yytext<<" "<<endl;
        yylval.symbol_val=new SymbolInfo(yytext,"OP");
        return RELOP;}
{ASSIGNOP} {token<<" <ASSIGNOP,"<<yytext<<">"<<endl;
            logfile<<"Line No. "<<line_count<<" Token : ASSIGNOP Lexeme : "<<yytext<<" "<<endl;
            yylval.symbol_val=new SymbolInfo(yytext,"OP");
            return ASSIGNOP;}
{LOGICOP} {token<<" <LOGICOP,"<<yytext<<">"<<endl;
            logfile<<"Line No. "<<line_count<<" Token : LOGICOP Lexeme : "<<yytext<<" "<<endl;
            yylval.symbol_val=new SymbolInfo(yytext,"OP");
            return LOGICOP;}
{NOT} {token<<" <NOT,"<<yytext<<">"<<endl;
      logfile<<"Line No. "<<line_count<<" Token : NOT Lexeme : "<<yytext<<" "<<endl;
      yylval.symbol_val=new SymbolInfo(yytext,"OP");
      return NOT;}
{RPAREN} {token<<" <RPAREN,"<<yytext<<">"<<endl;
        logfile<<"Line No. "<<line_count<<" Token : RPAREN Lexeme : "<<yytext<<" "<<endl;
        yylval.symbol_val=new SymbolInfo(yytext,"OP");
        return RPAREN;}
"{" {token<<" <LCURL,"<<yytext<<">"<<endl;
      logfile<<"Line No. "<<line_count<<" Token : LCURL Lexeme : "<<yytext<<" "<<endl;
      string cmd="S";
                      
                      //RP->processRequest(cmd,logfile);
      return LCURL;}
"}" {token<<" <CURL,"<<yytext<<">"<<endl;
    logfile<<"Line No. "<<line_count<<" Token : CURL Lexeme : "<<yytext<<" "<<endl;
    string cmd="E";

                      //RP->processRequest(cmd,logfile);
    return RCURL;
    }
{LTHIRD} {token<<" <LTHIRD,"<<yytext<<">"<<endl;
          logfile<<"Line No. "<<line_count<<" Token : LTHIRD Lexeme : "<<yytext<<" "<<endl;
          return LTHIRD;}
{RTHIRD} {token<<" <RTHIRD,"<<yytext<<">"<<endl;
          logfile<<"Line No. "<<line_count<<" Token : RTHIRD Lexeme : "<<yytext<<" "<<endl;
          return RTHIRD;}
{COMMA} {token<<" <COMMA,"<<yytext<<">"<<endl;
        logfile<<"Line No. "<<line_count<<" Token : COMMA Lexeme : "<<yytext<<" "<<endl;
        return COMMA;}
{SEMICOLON} {token<<" <SEMICOLON,"<<yytext<<">"<<endl;
            logfile<<"Line No. "<<line_count<<" Token : SEMICOLON Lexeme : "<<yytext<<" "<<endl;
            return SEMICOLON;}

\" {BEGIN(StringLiterals);stringInput="";}
<StringLiterals>\"   { token<<"<STRING ,"<<stringInput<<"> "<<endl;
                      // string cmd="I ";
                      // cmd+=stringInput;
                      // cmd+=" STRING";
                      // //RP->processRequest(cmd,logfile);
                     logfile<<"Line No. "<<line_count<<" Token : STRING   Lexeme : "<<stringInput<<" "<<endl;
                       
                       BEGIN INITIAL ;}

<StringLiterals>\\{NEWLINE} {cout<<"ok"<<line_count;line_count++;}

<StringLiterals>\n {logfile<<"Line No. "<<line_count<<"Error at line number :"<<line_count<<"Unfinished string"<<endl;error_count++;line_count++;BEGIN INITIAL;}
<StringLiterals><<EOF>> {logfile<<"Line No. "<<line_count<<"Error at line number :"<<line_count<<"Unfinished string UNEXPECTED ENDING"<<endl;error_count++;BEGIN INITIAL;}
<StringLiterals>([^\n\\\"]|(\\[^\r\n]))* {stringInput+=unescape(yytext);}

{ERROR_IDENTIFIERS} {logfile<<"Line No. "<<line_count<<"Error at line number :"<<line_count<<"Invalid Suffix on numeric constant or invalid prefix"<<endl;error_count++;}
<<EOF>> {return 0;}
. {return Unrecognized;}

