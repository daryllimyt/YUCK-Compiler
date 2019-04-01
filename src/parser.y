%code requires{
  #include "ast.hpp"
  #include "ast/ast_node.hpp"

  #include <fstream>
  #include <cassert>
  
  extern FILE *yyin;
  extern const Tree *g_root; // A way of getting the AST out

  //! This is to fix problems when generating C++
  // We are declaring the functions provided by Flex, so
  // that Bison generated code can call them.
  int yylex(void);
  void yyerror(const char *);

}



// Represents the value associated with any kind of
// AST node.
%union{
  Tree *nodetype;

  double number;
  std::string *string;
}


%right REDUCE_PREC
%nonassoc CASE DEFAULT IF SWITCH WHILE DO FOR 
%right CONTINUE BREAK RETURN
%left SEMICOLON 
%left COMMA
%right TYPEDEF EXTERN STATIC AUTO
%right VOID BOOL CHAR FLOAT INT DOUBLE SHORT LONG SIGNED UNSIGNED 
%right CONST VOLATILE SIZEOF
%right ENUM ELLIPSIS
%nonassoc VARIABLE NUMBER STRING_LITERAL
%nonassoc RBRACKET_L RBRACKET_R CBRACKET_L CBRACKET_R SBRACKET_L SBRACKET_R
%nonassoc ELSE
%right BITANDASSIGN BITXORASSIGN BITORASSIGN
%right LSHIFTASSIGN RSHIFTASSIGN
%right MULTASSIGN DIVASSIGN REMAINASSIGN
%right ADDASSIGN SUBASSIGN
%right ASSIGN
%right CONDITIONAL COLON
%left OR
%left AND
%left BITOR
%left BITXOR
%left BITAND
%left EQUAL NOTEQUAL
%left GREATER LESS GREATEREQUAL LESSEQUAL
%left LSHIFT RSHIFT
%left PLUS MINUS
%left MULTIPLY DIVIDE REMAINDER
// Pointers
%right NOT BITNOT
%nonassoc INCREMENT DECREMENT
// Scope


%type<nodetype> PROGRAM 
%type<nodetype> VARIABLE_DECLARATION DECLARATION_SPECIFIERS 
%type<nodetype> STORAGE_CLASS TYPE QUALIFIER INIT_DECLARATION_LIST INIT_DECLARATION 
%type<nodetype> DECLARATION_IDENTIFIER DIRECT_DECLARATOR DIRECT_DECLARATOR_PARAMETER
%type<nodetype> POINTER QUALIFIER_LIST
%type<nodetype> INITIALIZER INITIALIZER_LIST
%type<nodetype> FUNCTION_DECLARATION IDENTIFIER_LIST FORWARD_DECLARATION
%type<nodetype> PARAMETER_TYPE_LIST PARAMETER_LIST PARAMETER_DECLARATION
%type<nodetype> COMPOUND_STATEMENT COMPOUND_LIST COMPOUND_LIST_TYPE 
%type<nodetype> DECLARATION_LIST STATEMENT_LIST
%type<nodetype> STATEMENT LABELLED_STATEMENT EXPRESSION_STATEMENT
%type<nodetype> INIT_STATEMENT ITERATION_CONDITION LABELLED_CONDITION
%type<nodetype> SELECTION_STATEMENT ITERATION_STATEMENT JUMP_STATEMENT
%type<nodetype> ASSIGNMENT_EXPR CONDITIONAL_EXPR CONSTANT_EXPRESSION
%type<nodetype> LOGICAL_OR_EXPR LOGICAL_AND_EXPR INCLUSIVE_OR_EXPR EXCLUSIVE_OR_EXPR
%type<nodetype> AND_EXPR EQUALITY_EXPR RELATIONAL_EXPR SHIFT_EXPR
%type<nodetype> ADDITIVE_EXPR MULTIPLICATIVE_EXPR CAST_EXPR UNARY_EXPR
%type<nodetype> POSTFIX_EXPR ARGUMENT_EXPR_LIST PRIMARY_EXPR EXPRESSION
%type<nodetype> ENUM_SPECIFIER ENUMERATOR_LIST ENUMERATOR
%type<nodetype> TYPE_NAME SPECIFIER_QUALIFIER_LIST
%type<nodetype> ABSTRACT_DECLARATOR DIRECT_ABSTRACT_DECLARATOR ABSTRACT_DECLARATOR_PARAMETER

%type<number> NUMBER
%type<string> VARIABLE STRING_LITERAL
%type<string> TYPEDEF EXTERN STATIC AUTO
%type<string> VOID BOOL CHAR FLOAT INT DOUBLE SHORT LONG SIGNED UNSIGNED ENUM
%type<string> CONST VOLATILE SIZEOF
%type<string> SEMICOLON COMMA 
%type<string> ASSIGN
%type<string> ELLIPSIS

%start ROOT

%%

// Top Level Program
ROOT  : PROGRAM { g_root = new RootNode( $1 ); }

PROGRAM 
      : VARIABLE_DECLARATION              { $$ = $1; }
      | FUNCTION_DECLARATION              { $$ = $1; }
      | FORWARD_DECLARATION               { $$ = $1; }
      | PROGRAM VARIABLE_DECLARATION      { $$ = new ProgramNode( $1, $2 ); }
      | PROGRAM FUNCTION_DECLARATION      { $$ = new ProgramNode( $1, $2 ); }
      | PROGRAM FORWARD_DECLARATION       { $$ = new ProgramNode( $1, $2 ); }
      ;

// Variable Declarations
VARIABLE_DECLARATION 
      : DECLARATION_SPECIFIERS SEMICOLON                          { $$ = $1; }
      | DECLARATION_SPECIFIERS INIT_DECLARATION_LIST SEMICOLON    { $$ = new VariableDeclarationNode( $1, $2 ); }
      ;

DECLARATION_SPECIFIERS
      : TYPE                                                { $$ = $1; }
      | QUALIFIER                                           { $$ = $1; }
      | STORAGE_CLASS		                              { $$ = $1; }
      | TYPE DECLARATION_SPECIFIERS                         { $$ = new DeclarationSpecifierNode( $1, $2 ); }
      | QUALIFIER DECLARATION_SPECIFIERS                    { $$ = new DeclarationSpecifierNode( $1, $2 ); }
      | STORAGE_CLASS DECLARATION_SPECIFIERS  	            { $$ = new DeclarationSpecifierNode( $1, $2) ;}
      ;

STORAGE_CLASS
      : TYPEDEF		{ $$ = new StorageClassNode( "typedef" ); } 
	| EXTERN		{ $$ = new StorageClassNode( "extern" ); } 
	| STATIC		{ $$ = new StorageClassNode( "static" ); } 
	| AUTO		{ $$ = new StorageClassNode( "auto" ); } 
	; 
      /* left out register */

TYPE
      : VOID            { $$ = new TypeNode( "void" ); }
      | BOOL            { $$ = new TypeNode( "bool" ); }
      | CHAR            { $$ = new TypeNode( "char" ); }
      | FLOAT           { $$ = new TypeNode( "float" ); }
      | INT             { $$ = new TypeNode( "int" ); }
      | DOUBLE          { $$ = new TypeNode( "double" ); }
      | SHORT           { $$ = new TypeNode( "short" ); }
      | LONG            { $$ = new TypeNode( "long" ); }
      | SIGNED          { $$ = new TypeNode( "signed" ); }
      | UNSIGNED        { $$ = new TypeNode( "unsigned" ); }
      | ENUM_SPECIFIER  { $$ = $1; } 
      ;

QUALIFIER
      : CONST     { $$ = new QualifierNode( "const" ); }
      | VOLATILE  { $$ = new QualifierNode( "volatile" ); }
      ;

INIT_DECLARATION_LIST
      : INIT_DECLARATION                              { $$ = $1; }
      | INIT_DECLARATION_LIST COMMA INIT_DECLARATION  { $$ = new InitDeclarationListNode( $1, $3 ); }
      ;

INIT_DECLARATION 
      : DECLARATION_IDENTIFIER                        { $$ = new InitDeclarationNode( $1, NULL ); }
      | DECLARATION_IDENTIFIER ASSIGN INITIALIZER     { $$ = new InitDeclarationNode( $1, $3 ); }
      ;

DECLARATION_IDENTIFIER
      : DIRECT_DECLARATOR           { $$ = new DeclarationIdentifierNode( NULL, $1 ); }
      | POINTER DIRECT_DECLARATOR   { $$ = new DeclarationIdentifierNode( $1, $2 ); }
      ;

DIRECT_DECLARATOR
      : VARIABLE                                                        { $$ = new Variable( *$1 ); }
      | RBRACKET_L DECLARATION_IDENTIFIER RBRACKET_R                    { $$ = $2; }
      | DIRECT_DECLARATOR SBRACKET_L CONDITIONAL_EXPR SBRACKET_R        { $$ = new DirectDeclarationNode( "array declaration", $1, $3 ); }
      | DIRECT_DECLARATOR SBRACKET_L SBRACKET_R                         { $$ = new DirectDeclarationNode( "array declaration", $1, NULL ); }
      | DIRECT_DECLARATOR DIRECT_DECLARATOR_PARAMETER %prec REDUCE_PREC { $$ = new DirectDeclarationNode( "direct declaration", $1, $2 ); }
      ;

DIRECT_DECLARATOR_PARAMETER
      : RBRACKET_L PARAMETER_TYPE_LIST RBRACKET_R     { $$ = $2; }
      | RBRACKET_L IDENTIFIER_LIST RBRACKET_R         { $$ = $2; }
      | RBRACKET_L RBRACKET_R                         { $$ = NULL; }
      ;

POINTER
      : MULTIPLY                          { $$ = new PointerNode( NULL, NULL ); }
      | MULTIPLY QUALIFIER_LIST           { $$ = new PointerNode( $2, NULL ); }
      | MULTIPLY POINTER                  { $$ = new PointerNode( NULL, $2 ); }
      | MULTIPLY QUALIFIER_LIST POINTER   { $$ = new PointerNode( $2, $3 ); }
      ;

QUALIFIER_LIST
      : QUALIFIER                   { $$ = $1; }
      | QUALIFIER_LIST QUALIFIER    { $$ = new QualifierListNode( $1, $2 ); }
      ;

INITIALIZER
      : ASSIGNMENT_EXPR                               { $$ = $1; }
      | CBRACKET_L INITIALIZER_LIST CBRACKET_R        { $$ = new InitializerNode( $2 ); }
      ;

INITIALIZER_LIST
      : INITIALIZER                                   { $$ = $1; }
      | INITIALIZER_LIST COMMA INITIALIZER            { $$ = new InitializerListNode( $1, $3 ); }
      ;

// Function Declarations
FUNCTION_DECLARATION
      : DECLARATION_SPECIFIERS DECLARATION_IDENTIFIER COMPOUND_STATEMENT      { $$ = new FunctionDeclarationNode( $1, $2, $3 ); }
      | DECLARATION_IDENTIFIER COMPOUND_STATEMENT                             { $$ = new FunctionDeclarationNode( NULL, $1, $2 ); }
      /* Left out stuff with declaration 'lists' */
      ;

FORWARD_DECLARATION
      : DECLARATION_SPECIFIERS DIRECT_DECLARATOR DIRECT_DECLARATOR_PARAMETER SEMICOLON {
            $$ = new FunctionDeclarationNode(
                  $1, 
                  new DirectDeclarationNode( "forward declaration", $2, $3 ), 
                  NULL
            ); 
      }

PARAMETER_TYPE_LIST
      : PARAMETER_LIST                    { $$ = $1; }
      | PARAMETER_LIST COMMA ELLIPSIS 	{ $$ = new ParameterTypeListNode ($1, new Ellipsis( *$3 )); }
      ;

PARAMETER_LIST
      : PARAMETER_DECLARATION                         { $$ = $1; }
      | PARAMETER_LIST COMMA PARAMETER_DECLARATION    { $$ = new ParameterListNode( $1, $3 ); }
      ;

PARAMETER_DECLARATION
      : DECLARATION_SPECIFIERS DECLARATION_IDENTIFIER       { $$ = new ParameterDeclarationNode( $1, $2 ); }
      | DECLARATION_SPECIFIERS ABSTRACT_DECLARATOR          { $$ = new ParameterDeclarationNode( $1, $2 ); }
      | DECLARATION_SPECIFIERS                              { $$ = new ParameterDeclarationNode( $1, NULL ); }
      ;

IDENTIFIER_LIST
      : VARIABLE                          { $$ = new Variable( *$1 ); }
      | IDENTIFIER_LIST COMMA VARIABLE    { $$ = new IdentifierListNode( $1, new Variable( *$3 ) ); }
      ;

COMPOUND_STATEMENT
      : CBRACKET_L CBRACKET_R                   { $$ = new CompoundStatementNode( NULL ); }
      | CBRACKET_L COMPOUND_LIST CBRACKET_R     { $$ = new CompoundStatementNode( $2 ); }
      ;

COMPOUND_LIST
      : COMPOUND_LIST_TYPE                { $$ = $1; }
      | COMPOUND_LIST COMPOUND_LIST_TYPE  { $$ = new CompoundListNode( $1, $2 ); }
      ;

COMPOUND_LIST_TYPE
      : DECLARATION_LIST %prec REDUCE_PREC      { $$ = $1; }
      | STATEMENT_LIST %prec REDUCE_PREC        { $$ = $1; }
      ;

DECLARATION_LIST
      : VARIABLE_DECLARATION                    { $$ = $1; }
      | DECLARATION_LIST VARIABLE_DECLARATION   { $$ = new DeclarationListNode( $1, $2 ); }
      ;

STATEMENT_LIST
      : STATEMENT                   { $$ = $1; }
      | STATEMENT_LIST STATEMENT    { $$ = new StatementListNode( $1, $2 ); }
      ;

// Statements
STATEMENT
      : COMPOUND_STATEMENT          { $$ = $1; }
      | LABELLED_STATEMENT          { $$ = $1; }
      | EXPRESSION_STATEMENT        { $$ = $1; }
      | SELECTION_STATEMENT         { $$ = $1; }
      | ITERATION_STATEMENT         { $$ = $1; }
      | JUMP_STATEMENT              { $$ = $1; }
      ;

LABELLED_STATEMENT
      : LABELLED_CONDITION COLON STATEMENT_LIST       { $$ = new LabelledStatementNode( $1, $3 ); }
      | LABELLED_CONDITION COLON                      { $$ = new LabelledStatementNode( $1, NULL ); }
      ;

LABELLED_CONDITION
      : VARIABLE                    { $$ = new Variable( *$1 ); }
      | CASE CONSTANT_EXPRESSION    { $$ = $2; }
      | DEFAULT                     { $$ = NULL; }
      ;

EXPRESSION_STATEMENT
      : SEMICOLON             { $$ = new ExpressionStatementNode( NULL ); }
      | EXPRESSION SEMICOLON  { $$ = new ExpressionStatementNode( $1 ); }
      ;

SELECTION_STATEMENT
      : IF RBRACKET_L EXPRESSION RBRACKET_R STATEMENT                   { $$ = new SelectionNode( "if", $3, $5, NULL ); }
      | IF RBRACKET_L EXPRESSION RBRACKET_R STATEMENT ELSE STATEMENT    { $$ = new SelectionNode( "if else", $3, $5, $7 ); }
      | SWITCH RBRACKET_L EXPRESSION RBRACKET_R STATEMENT               { $$ = new SelectionNode( "switch", $3, $5, NULL ); }
      ;

ITERATION_STATEMENT
      : WHILE RBRACKET_L EXPRESSION RBRACKET_R STATEMENT                      { $$ = new IterationNode( "while", $3, NULL, NULL, $5 ); }
      | DO STATEMENT WHILE RBRACKET_L EXPRESSION RBRACKET_R SEMICOLON         { $$ = new IterationNode( "do", $5, NULL, NULL, $2 ); }
      | FOR RBRACKET_L INIT_STATEMENT ITERATION_CONDITION RBRACKET_R STATEMENT     
                                                                              { $$ = new IterationNode( "for", $3, $4, NULL, $6 ); }
      | FOR RBRACKET_L INIT_STATEMENT ITERATION_CONDITION EXPRESSION RBRACKET_R STATEMENT
                                                                              { $$ = new IterationNode( "for", $3, $4, $5, $7 ); }
      ;

INIT_STATEMENT
      : EXPRESSION_STATEMENT                    { $$ = new ExpressionStatementNode( $1 ); }
      | VARIABLE_DECLARATION                    { $$ = $1; }
      ;

ITERATION_CONDITION
      : EXPRESSION_STATEMENT        { $$ = new ExpressionStatementNode( $1 ); }
      | DECLARATION_SPECIFIERS DECLARATION_IDENTIFIER ASSIGN INITIALIZER SEMICOLON    
                  { 
                        $$ = new VariableDeclarationNode(
                              $1, 
                              new InitDeclarationNode( $2, $4 )
                        ); 
                  }
      ;

JUMP_STATEMENT
      : RETURN SEMICOLON                  { $$ = new JumpNode( "return", NULL); }
      | RETURN EXPRESSION SEMICOLON       { $$ = new JumpNode( "return", $2 ); }
      | CONTINUE SEMICOLON                { $$ = new JumpNode( "continue", NULL ); }
      | BREAK SEMICOLON                   { $$ = new JumpNode( "break", NULL ); }
      /* Left out go to : not required by spec */
      ;





// Logical/Algebraic Expressions
CONSTANT_EXPRESSION
      : CONDITIONAL_EXPR      { $$ = $1; }
      ;


EXPRESSION
      : ASSIGNMENT_EXPR                               { $$ = $1; }
      | EXPRESSION COMMA ASSIGNMENT_EXPR              { $$ = new ExpressionNode( $1, $3 ); }
      ;

ASSIGNMENT_EXPR
      : CONDITIONAL_EXPR                              { $$ = $1; }
      | UNARY_EXPR ASSIGN ASSIGNMENT_EXPR             { $$ = new AssignmentExprNode( "assign", $1, $3 ); }
      | UNARY_EXPR ADDASSIGN ASSIGNMENT_EXPR          { $$ = new AssignmentExprNode( "+=", $1, $3 ); }
      | UNARY_EXPR SUBASSIGN ASSIGNMENT_EXPR          { $$ = new AssignmentExprNode( "-=", $1, $3 ); }
      | UNARY_EXPR MULTASSIGN ASSIGNMENT_EXPR         { $$ = new AssignmentExprNode( "*=", $1, $3 ); }
      | UNARY_EXPR DIVASSIGN ASSIGNMENT_EXPR          { $$ = new AssignmentExprNode( "/=", $1, $3 ); }
      | UNARY_EXPR REMAINASSIGN ASSIGNMENT_EXPR       { $$ = new AssignmentExprNode( "%=", $1, $3 ); }
      | UNARY_EXPR LSHIFTASSIGN ASSIGNMENT_EXPR       { $$ = new AssignmentExprNode( "<<=", $1, $3 ); }
      | UNARY_EXPR RSHIFTASSIGN ASSIGNMENT_EXPR       { $$ = new AssignmentExprNode( ">>=", $1, $3 ); }
      | UNARY_EXPR BITANDASSIGN ASSIGNMENT_EXPR       { $$ = new AssignmentExprNode( "&=", $1, $3 ); }
      | UNARY_EXPR BITXORASSIGN ASSIGNMENT_EXPR       { $$ = new AssignmentExprNode( "^=", $1, $3 ); }
      | UNARY_EXPR BITORASSIGN ASSIGNMENT_EXPR        { $$ = new AssignmentExprNode( "|=", $1, $3 ); }
      ;

CONDITIONAL_EXPR
      : LOGICAL_OR_EXPR                                                 { $$ = $1; }
      | LOGICAL_OR_EXPR CONDITIONAL EXPRESSION COLON CONDITIONAL_EXPR   { $$ = new ConditionalExprNode( $1, $3, $5 ); }
      | LOGICAL_OR_EXPR CONDITIONAL COLON CONDITIONAL_EXPR              { $$ = new ConditionalExprNode( $1, NULL, $4 ); }
      ;

LOGICAL_OR_EXPR
      : LOGICAL_AND_EXPR                              { $$ = $1; }
      | LOGICAL_OR_EXPR OR LOGICAL_AND_EXPR           { $$ = new LogicalExprNode( "||", $1, $3 ); }
      ;

LOGICAL_AND_EXPR
      : INCLUSIVE_OR_EXPR                             { $$ = $1; }
      | LOGICAL_AND_EXPR AND INCLUSIVE_OR_EXPR        { $$ = new LogicalExprNode( "&&", $1, $3 ); }
      ;

INCLUSIVE_OR_EXPR
      : EXCLUSIVE_OR_EXPR                             { $$ = $1; }
      | INCLUSIVE_OR_EXPR BITOR EXCLUSIVE_OR_EXPR     { $$ = new BitExprNode( "|" , $1, $3 ); }
      ;

EXCLUSIVE_OR_EXPR
      : AND_EXPR                                      { $$ = $1; }
      | EXCLUSIVE_OR_EXPR BITXOR AND_EXPR             { $$ = new BitExprNode( "^", $1, $3 ); }
      ;

AND_EXPR
      : EQUALITY_EXPR                                 { $$ = $1; }
      | AND_EXPR BITAND EQUALITY_EXPR                 { $$ = new BitExprNode( "&", $1, $3 ); }
      ;

EQUALITY_EXPR
      : RELATIONAL_EXPR                               { $$ = $1; }
      | EQUALITY_EXPR EQUAL RELATIONAL_EXPR           { $$ = new LogicalExprNode( "==", $1, $3 ); }
      | EQUALITY_EXPR NOTEQUAL RELATIONAL_EXPR        { $$ = new LogicalExprNode( "!=", $1, $3 ); }
      ;

RELATIONAL_EXPR
      : SHIFT_EXPR                                    { $$ = $1; }
      | RELATIONAL_EXPR GREATER SHIFT_EXPR            { $$ = new LogicalExprNode( ">", $1, $3 ); }
      | RELATIONAL_EXPR LESS SHIFT_EXPR               { $$ = new LogicalExprNode( "<", $1, $3 ); }
      | RELATIONAL_EXPR GREATEREQUAL SHIFT_EXPR       { $$ = new LogicalExprNode( ">=", $1, $3 ); }
      | RELATIONAL_EXPR LESSEQUAL SHIFT_EXPR          { $$ = new LogicalExprNode( "<=", $1, $3 ); }
      ;

SHIFT_EXPR
      : ADDITIVE_EXPR                                 { $$ = $1; }
      | SHIFT_EXPR LSHIFT ADDITIVE_EXPR               { $$ = new ShiftExprNode( "<<", $1, $3 ); }
      | SHIFT_EXPR RSHIFT ADDITIVE_EXPR               { $$ = new ShiftExprNode( ">>", $1, $3 ); }
      ;

ADDITIVE_EXPR
      : MULTIPLICATIVE_EXPR                           { $$ = $1; }
      | ADDITIVE_EXPR PLUS MULTIPLICATIVE_EXPR        { $$ = new AlgebraExprNode( "+", $1, $3 ); }
      | ADDITIVE_EXPR MINUS MULTIPLICATIVE_EXPR       { $$ = new AlgebraExprNode( "-", $1, $3 ); }
      ;

MULTIPLICATIVE_EXPR
      : CAST_EXPR                                     { $$ = $1; }
      | MULTIPLICATIVE_EXPR MULTIPLY CAST_EXPR        { $$ = new AlgebraExprNode( "*", $1, $3); }
      | MULTIPLICATIVE_EXPR DIVIDE CAST_EXPR          { $$ = new AlgebraExprNode( "/", $1, $3); }
      | MULTIPLICATIVE_EXPR REMAINDER CAST_EXPR       { $$ = new AlgebraExprNode( "%", $1, $3); }
      ;

CAST_EXPR
      : UNARY_EXPR                                    { $$ = $1; }
      | RBRACKET_L TYPE_NAME RBRACKET_R CAST_EXPR     { $$ = new CastExprNode( $2, $4 ); }
      ;

UNARY_EXPR
      : POSTFIX_EXPR                            { $$ = $1; }
      | INCREMENT UNARY_EXPR                    { $$ = new UnaryExprNode( "++_", $2 ); }
      | DECREMENT UNARY_EXPR                    { $$ = new UnaryExprNode( "--_", $2 ); }
      | BITAND CAST_EXPR                        { $$ = new UnaryExprNode( "&_", $2 ); }
      | MULTIPLY CAST_EXPR                      { $$ = new UnaryExprNode( "*_", $2 ); }
      | PLUS CAST_EXPR                          { $$ = new UnaryExprNode( "+_", $2 ); }
      | MINUS CAST_EXPR                         { $$ = new UnaryExprNode( "-_", $2 ); }
      | BITNOT CAST_EXPR                        { $$ = new UnaryExprNode( "~_", $2 ); }
      | NOT CAST_EXPR                           { $$ = new UnaryExprNode( "!", $2 ); }
      | SIZEOF UNARY_EXPR                       { $$ = new UnaryExprNode( "sizeof", $2 ); }
      | SIZEOF RBRACKET_L TYPE_NAME RBRACKET_R  { $$ = new UnaryExprNode( "sizeof", $3 ); }
      ;

POSTFIX_EXPR
      : PRIMARY_EXPR                                              { $$ = $1; }
      | POSTFIX_EXPR SBRACKET_L EXPRESSION SBRACKET_R             { $$ = new PostFixExprNode( "array element call", $1, $3, NULL ); }
      | POSTFIX_EXPR RBRACKET_L RBRACKET_R                        { $$ = new PostFixExprNode( "direct function call", $1, NULL, NULL ); }
      | POSTFIX_EXPR RBRACKET_L ARGUMENT_EXPR_LIST RBRACKET_R     { $$ = new PostFixExprNode( "direct function call", $1, NULL, $3 ); }
      /* Left out member functions */
      | POSTFIX_EXPR INCREMENT                                    { $$ = new PostFixExprNode( "_++", $1, NULL, NULL ); }
      | POSTFIX_EXPR DECREMENT                                    { $$ = new PostFixExprNode( "_--", $1, NULL, NULL ); }
      ;

ARGUMENT_EXPR_LIST
      : ASSIGNMENT_EXPR                               { $$ = $1; }
      | ASSIGNMENT_EXPR COMMA ARGUMENT_EXPR_LIST      { $$ = new ArgumentExprNode( $1, $3 ); }
      ;

PRIMARY_EXPR
      : VARIABLE                          { $$ = new Variable( *$1 ); }
      | NUMBER                            { $$ = new Number( $1 ); }
      | STRING_LITERAL                    { $$ = new String( *$1 ); }
      | RBRACKET_L EXPRESSION RBRACKET_R  { $$ = new PrimaryExprNode( $2 ); }
      ;

// Type Casting
TYPE_NAME
      : SPECIFIER_QUALIFIER_LIST %prec REDUCE_PREC    { $$ = new TypeNameNode( $1, NULL ); }
      | SPECIFIER_QUALIFIER_LIST ABSTRACT_DECLARATOR  { $$ = new TypeNameNode( $1, $2 ); }
      ;

SPECIFIER_QUALIFIER_LIST
      : TYPE                                    { $$ = $1; }
      | QUALIFIER                               { $$ = $1; }
      | TYPE SPECIFIER_QUALIFIER_LIST           { $$ = new SpecifierQualifierListNode( $1, $2 ); }
      | QUALIFIER SPECIFIER_QUALIFIER_LIST      { $$ = new SpecifierQualifierListNode( $1, $2 ); }
      ;

ABSTRACT_DECLARATOR
      : POINTER                                 { $$ = new AbstractDeclaratorNode( $1, NULL ); }
      | DIRECT_ABSTRACT_DECLARATOR              { $$ = new AbstractDeclaratorNode( NULL, $1 ); }
      | POINTER DIRECT_ABSTRACT_DECLARATOR      { $$ = new AbstractDeclaratorNode( $1, $2 ); }
      ;

DIRECT_ABSTRACT_DECLARATOR
      : RBRACKET_L ABSTRACT_DECLARATOR RBRACKET_R     { $$ = new DirectAbstractDeclaratorNode( "bracketed abstract declarator", $2, NULL ); }
      | ABSTRACT_DECLARATOR_PARAMETER                 { $$ = $1; }
      | DIRECT_ABSTRACT_DECLARATOR ABSTRACT_DECLARATOR_PARAMETER 
                                                      { $$ = new DirectAbstractDeclaratorNode( "direct abstract declarator", $1, $2 ); }
      ;

ABSTRACT_DECLARATOR_PARAMETER
      : SBRACKET_L SBRACKET_R                         { $$ = new AbstractDeclaratorParameterNode( "square abstract parameter", NULL ); }
      | SBRACKET_L CONSTANT_EXPRESSION SBRACKET_R     { $$ = new AbstractDeclaratorParameterNode( "square abstract parameter", $2 ); }
      | RBRACKET_L RBRACKET_R                         { $$ = new AbstractDeclaratorParameterNode( "round abstract parameter", NULL ); }
      | RBRACKET_L PARAMETER_TYPE_LIST RBRACKET_R     { $$ = new AbstractDeclaratorParameterNode( "round abstract parameter", $2 ); }
      ;

ENUM_SPECIFIER 
      : ENUM CBRACKET_L ENUMERATOR_LIST CBRACKET_R	            { $$ = new EnumSpecifierNode( $3, std::string() ); }			
	| ENUM VARIABLE CBRACKET_L ENUMERATOR_LIST CBRACKET_R	      { $$ = new EnumSpecifierNode( $4, *$2 );   }			
	| ENUM VARIABLE				                        { $$ = new EnumSpecifierNode( NULL, *$2 ); }			
      ;

ENUMERATOR_LIST
      : ENUMERATOR					{ $$ = $1; }
	| ENUMERATOR COMMA ENUMERATOR_LIST		{ $$ = new EnumeratorListNode( $1, $3 ); }
      ;

ENUMERATOR
      : VARIABLE						{ $$ = new EnumeratorNode( *$1 , NULL ); }
	| VARIABLE ASSIGN CONSTANT_EXPRESSION	{ $$ = new EnumeratorNode( *$1 , $3 ); }
      ;

%%
const Tree *g_root; // Definition of variable (to match declaration earlier)

const Tree *parseAST(char* a, char* b){
  g_root=0;

  yyin = fopen(a, "r");
  if(yyin) { 
	  yyparse();
  }
  fclose(yyin);
	
  return g_root;
}
