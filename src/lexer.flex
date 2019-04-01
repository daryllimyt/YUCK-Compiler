%option noyywrap
%option yylineno

Decimal			[0-9]
Letter			[a-zA-Z_]
Hex			    [a-fA-F0-9]
Exponent	  [Ee][+-]?{Decimal}+
FloatType		(f|F|l|L)
LongType		(u|U|l|L)*

%{
  #include "parser.tab.hpp"
  #include <stdlib.h>
  #include <stdio.h>		
  #include <string>
  #include <iostream>
  #include "../include/ast/ast_structure.hpp"	

  /* map  tokendeclarations to yylval */
  void yyerror (char const *s);
  extern FILE *yyin;
  extern FILE *yyout;

  int line_no = 1; //keep track of error; easy to debug

  int token(int token);


  // Avoid error "error: `fileno' was not declared in this scope"
  extern "C" int fileno(FILE *stream);
%}

%%
"*"             { return token(MULTIPLY); }
"+"             { return token(PLUS); }
"-"             { return token(MINUS); }
"/"             { return token(DIVIDE); }
"%"             { return token(REMAINDER); }
"++"            { return token(INCREMENT); }
"--"            { return token(DECREMENT); }

"("             { return token(RBRACKET_L); }
")"             { return token(RBRACKET_R); }
"{"|"<%"|"??<"  { return token(CBRACKET_L); }
"}"|"%>"|"??>"  { return token(CBRACKET_R); }
"["|"<:"|"??("  { return token(SBRACKET_L); }
"]"|":>"|"??)"  { return token(SBRACKET_R); }
[\']            { /*return token(SQUOTE);*/ }
[\"]            { /*return token(DQUOTE);*/ }

"=="            { return token(EQUAL); }
"!="            { return token(NOTEQUAL); }
">"             { return token(GREATER); }
"<"             { return token(LESS); }
">="            { return token(GREATEREQUAL); }
"<="            { return token(LESSEQUAL); }
"?"             { return token(CONDITIONAL); }
":"             { return token(COLON); }
"->"            { /*return token(ARROW);*/ }
"."             { /*return token(POINT);*/ }
","             { return token(COMMA); }
";"             { return token(SEMICOLON); }

"&&"            { return token(AND); }
"||"            { return token(OR); }
"!"             { return token(NOT); }

"&"             { return token(BITAND); }
"|"|"??!"       { return token(BITOR); }
"^"|"??'"       { return token(BITXOR); }
"~"|"??-"       { return token(BITNOT); }
"<<"            { return token(LSHIFT); }
">>"            { return token(RSHIFT); }

"="             { return token(ASSIGN); }
"+="            { return token(ADDASSIGN); }
"-="            { return token(SUBASSIGN); }
"*="            { return token(MULTASSIGN); }
"/="            { return token(DIVASSIGN); }
"%="            { return token(REMAINASSIGN); }
"<<="           { return token(LSHIFTASSIGN); }
">>="           { return token(RSHIFTASSIGN); }
"&="            { return token(BITANDASSIGN); }
"|="            { return token(BITORASSIGN); }
"^="            { return token(BITXORASSIGN); }

"return"        { return token(RETURN); }
"if"            { return token(IF); }
"else"          { return token(ELSE); }
"for"           { return token(FOR); }
"while"         { return token(WHILE); }
"do"            { return token(DO); }
"break"         { return token(BREAK); }
"switch"        { return token(SWITCH); }
"case"          { return token(CASE); }
"default"       { return token(DEFAULT); }
"const"         { return token(CONST); }
"true"          { yylval.number = 1; return NUMBER; }
"false"         { yylval.number = 0; return NUMBER; }
"this"          { /*return token(THIS);*/ }
"throw"         { /*return token(THROW);*/ }
"catch"         { /*return token(CATCH);*/ }
"try"           { /*return token(TRY);*/ }

"void"          { return token(VOID); }
"bool"          { return token(BOOL); }
"char"          { return token(CHAR); }
"float"         { return token(FLOAT); }
"int"           { return token(INT); }
"double"        { return token(DOUBLE); }
"long"          { return token(LONG); }
"short"         { return token(SHORT); }
"signed"        { return token(SIGNED); }
"unsigned"      { return token(UNSIGNED); }
"auto"          { return token(AUTO); }
"typedef"       { return token(TYPEDEF); }
"operator"      { /*return token(OPERATOR);*/ }

"enum"			    { return token(ENUM); }
"extern"		    { return token(EXTERN); }
"continue"      { return token(CONTINUE); }
"union"         { /*return token(UNION)*/ }
"static"        { return token(STATIC); }
"struct"        { /*return token(STRUCT);*/ }
"sizeof"        { return token(SIZEOF); }
"register"      { /*return token(REGISTER);*/ }
"..."           { return token(ELLIPSIS);}

"0"[xX]{Hex}+{LongType}?    { // Hexadecimal Number
  std::string s(yytext); s.erase(0,2); yylval.number = std::stoi(s, NULL, 16); return NUMBER; }
"0"[0-7]+{LongType}?        { // Octal Number
  std::string s(yytext); s.erase(0,1); yylval.number = std::stoi(s, NULL, 8); return NUMBER; }
"0"[bB](0|1)+{LongType}?    { // Binary Number
  std::string s(yytext); s.erase(0,2); yylval.number = std::stoi(s, NULL, 2); return NUMBER; }

{Decimal}+{LongType}?                           { yylval.number=strtod(yytext, 0); return NUMBER; }
{Decimal}+{Exponent}{FloatType}?                { yylval.number=strtod(yytext, 0); return NUMBER; }
{Decimal}+"."{Decimal}*{Exponent}?{FloatType}?  { yylval.number=strtod(yytext, 0); return NUMBER; }
{Decimal}*"."{Decimal}+{Exponent}?{FloatType}?  { yylval.number=strtod(yytext, 0); return NUMBER; }

{Letter}({Letter}|{Decimal})*   { yylval.string=new std::string(yytext); return VARIABLE; }

\"(\\.|\\\n|[^"\\])*\"          { yylval.string=new std::string(yytext); return STRING_LITERAL; }

"//".*             { /* Comment */ ; }
"/*"[^"*/"]*"*/"   { /* Comment */ ; }

[ \t\f]+		  { /* Whitespace */ ; }
[\r\n\v]			{ line_no++; }

.             { yyerror(yytext); }
%%

void yyerror (char const *s)
{
   /* if s is unrecognised, print error */
  fprintf (stderr, "Parse error : %s\n", s);
  std::cerr << " Syntax/lex error found at line: " << line_no << std::endl;
  std::cerr << "Last accepted token: " << yytext << std::endl;
	
  exit(1);
}


int token(int token) {
		yylval.string = new std::string(yytext);		
		return token;
}
