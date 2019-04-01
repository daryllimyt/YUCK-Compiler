#ifndef ast_node_hpp
#define ast_node_hpp

#include <string>
#include <iostream>
#include <memory>
#include <initializer_list>
#include <map>
#include <vector>
#include <cmath>
#include <regex>
#include <fstream>
#include <stdexcept>


#include "ast_structure.hpp"

typedef const Tree *NodePtr; // Points to any node in the tree

class Tree{
    
    private:
    bool CheckDeleteError(NodePtr branch){
        if(branch != NULL){
            std::cerr << "Warning: branch node of type \"";
            std::cerr << branch->GetType();
            std::cerr << "\" from tree node of type \"";
            std::cerr << type << "\" might have been leaked!" << std::endl;
            return true;
        }
        else{
            return false;
        }
    }

    protected:
    std::string type;

    public:
    ~Tree(){
        bool error_status = (
               CheckDeleteError(GetLeft())
            || CheckDeleteError(GetRight())
            || CheckDeleteError(GetNext())
            || CheckDeleteError(GetPointer())
            || CheckDeleteError(GetIdentifier())
            || CheckDeleteError(GetArguments())
            || CheckDeleteError(GetCondition())
            || CheckDeleteError(GetConditionOne())
            || CheckDeleteError(GetConditionTwo())
            || CheckDeleteError(GetConditionThree())
            || CheckDeleteError(GetTruePath())
            || CheckDeleteError(GetFalsePath())
            || CheckDeleteError(GetReturnValue())
            || CheckDeleteError(GetIndex())
            || CheckDeleteError(GetSpecifiers())
            || CheckDeleteError(GetQualifiers())
            || CheckDeleteError(GetStatements())
            || CheckDeleteError(GetDeclarator())
        );
        // std::cerr << "Tree node of type \"" << type << "\" has been deleted" << std::endl;
        // if(error_status){
        //     std::cerr << "Warning: The child nodes of this node might have leaked!" << std::endl;
        // }
    }
    std::string GetType() const{
        return type;
    }
    virtual NodePtr GetLeft() const{ return NULL; }
    virtual NodePtr GetRight() const{ return NULL; }
    virtual NodePtr GetNext() const{ return NULL; }
    virtual NodePtr GetPointer() const{ return NULL; }
    virtual NodePtr GetIdentifier() const{ return NULL; }
    virtual NodePtr GetArguments() const{ return NULL; }
    virtual NodePtr GetCondition() const{ return NULL; }
    virtual NodePtr GetConditionOne() const{ return NULL; }
    virtual NodePtr GetConditionTwo() const{ return NULL; }
    virtual NodePtr GetConditionThree() const{ return NULL; }
    virtual NodePtr GetTruePath() const{ return NULL; }
    virtual NodePtr GetFalsePath() const{ return NULL; }
    virtual NodePtr GetReturnValue() const{ return NULL; }
    virtual NodePtr GetIndex() const{ return NULL; }
    virtual NodePtr GetSpecifiers() const{ return NULL; }
    virtual NodePtr GetQualifiers() const{ return NULL; }
    virtual NodePtr GetStatements() const{ return NULL; }
    virtual NodePtr GetDeclarator() const{ return NULL; }
    virtual const std::string GetId() const{}
    virtual const double GetValue() const{}
    virtual const std::string GetEllipsis() const{}

    
};

class RootNode : public Tree
{
    protected:
    NodePtr next;

    public:
    RootNode(NodePtr _next){
        type = "root";
        next = _next;
    }
    NodePtr GetNext() const{
        return next;
    }
};

class ProgramNode : public Tree
{
    protected:
    NodePtr left;
    NodePtr right;

    public:
    ProgramNode(NodePtr _left, NodePtr _right){
        type = "program";
        left = _left;
        right = _right;
    }
    NodePtr GetLeft() const{
        return left;
    }
    NodePtr GetRight() const{
        return right;
    }
};

class VariableDeclarationNode : public Tree
{
    protected:
    NodePtr left; // Specifiers
    NodePtr right; // Identifiers

    public:
    VariableDeclarationNode(NodePtr _left, NodePtr _right){
        type = "variable declaration";
        left = _left;
        right = _right;
    }
    NodePtr GetLeft() const{
        return left;
    }
    NodePtr GetRight() const{
        return right;
    }
};

class DeclarationSpecifierNode : public Tree
{
    protected:
    NodePtr left;
    NodePtr right;

    public:
    DeclarationSpecifierNode(NodePtr _left, NodePtr _right){
        type = "declaration specifier";
        left = _left;
        right = _right;
    }
    NodePtr GetLeft() const{
        return left;
    }
    NodePtr GetRight() const{
        return right;
    }
};

class StorageClassNode : public Tree
{
    public:
    StorageClassNode(const std::string &_type){
        type = _type;
    }

};

class TypeNode : public Tree
{
    public:
    TypeNode(const std::string &_type){
        type = _type;
    }

};


class QualifierNode : public Tree
{
    public:
    QualifierNode(const std::string &_type){
        type = _type;
    }
};

class InitDeclarationListNode : public Tree
{
    protected:
    NodePtr left;
    NodePtr right;

    public:
    InitDeclarationListNode(NodePtr _left, NodePtr _right){
        type = "initial declaration list";
        left = _left;
        right = _right;
    }
    NodePtr GetLeft() const{
        return left;
    }
    NodePtr GetRight() const{
        return right;
    }
};

class InitDeclarationNode : public Tree
{
    protected:
    NodePtr left; // Identifier branch
    NodePtr right; // Value

    public:
    InitDeclarationNode(NodePtr _left, NodePtr _right){
        type = "init assign";
        left = _left;
        right = _right;
    }
    NodePtr GetLeft() const{
        return left;
    }
    NodePtr GetRight() const{
        return right;
    }
};

class DeclarationIdentifierNode : public Tree
{
    protected:
    NodePtr pointer;
    NodePtr identifier;

    public:
    DeclarationIdentifierNode(NodePtr _pointer, NodePtr _identifier){
        type = "declaration identifier";
        pointer = _pointer;
        identifier = _identifier;
    }
    NodePtr GetPointer() const{
        return pointer;
    }
    NodePtr GetIdentifier() const{
        return identifier;
    }
};

class DirectDeclarationNode : public Tree
{
    protected:
    NodePtr left;
    NodePtr right; // Parameter

    public:
    DirectDeclarationNode(const std::string& _type, NodePtr _left, NodePtr _right){
        type = _type;
        left = _left;
        right = _right;
    }
    NodePtr GetLeft() const{
        return left;
    }
    NodePtr GetRight() const{
        return right;
    }
};

class PointerNode : public Tree
{
    protected:
    NodePtr qualifiers;
    NodePtr right;

    public:
    PointerNode(NodePtr _qualifiers, NodePtr _right){
        type = "pointer";
        qualifiers = _qualifiers;
        right = _right;
    }
    NodePtr GetQualifiers() const{
        return qualifiers;
    }
    NodePtr GetRight() const{
        return right;
    }
};

class QualifierListNode : public Tree
{
    protected:
    NodePtr left;
    NodePtr right;

    public:
    QualifierListNode(NodePtr _left, NodePtr _right){
        type = "qualifier list";
        left = _left;
        right = _right;
    }
    NodePtr GetLeft() const{
        return left;
    }
    NodePtr GetRight() const{
        return right;
    }
};

class InitializerNode : public Tree
{
    protected:
    NodePtr next;

    public:
    InitializerNode(NodePtr _next){
        type = "array initialization";
        next = _next;
    }
    NodePtr GetNext() const{
        return next;
    }
};

class InitializerListNode : public Tree
{
    protected:
    NodePtr left;
    NodePtr right;

    public:
    InitializerListNode(NodePtr _left, NodePtr _right){
        type = "initializer list";
        left = _left;
        right = _right;
    }
    NodePtr GetLeft() const{
        return left;
    }
    NodePtr GetRight() const{
        return right;
    }
};

class FunctionDeclarationNode : public Tree
{
    protected:
    NodePtr specifiers;
    NodePtr identifier;
    NodePtr statements;

    public:
    FunctionDeclarationNode(NodePtr _specifiers, NodePtr _identifier, NodePtr _statements){
        type = "function declaration";
        specifiers = _specifiers;
        identifier = _identifier;
        statements = _statements;
    }
    NodePtr GetSpecifiers() const{
        return specifiers;
    }
    NodePtr GetIdentifier() const{
        return identifier;
    }
    NodePtr GetStatements() const{
        return statements;
    }
};

class Ellipsis : public Tree
{
    private:
    std::string ellipsis;

    public:
    Ellipsis(const std::string &_ellipsis){
        type = "ellipsis";
        ellipsis = _ellipsis;
    }
    const std::string GetEllipsis() const{
        return ellipsis;
    }
};

class ParameterTypeListNode : public Tree
{
    protected:
    NodePtr left;
    NodePtr right;

    public:
    ParameterTypeListNode(NodePtr _left, NodePtr _right){
        type = "parameter type list";
        left = _left;
        right = _right;
    }
    NodePtr GetLeft() const{
        return left;
    }
    NodePtr GetRight() const{
        return right;
    }

};

class ParameterListNode : public Tree
{
    protected:
    NodePtr left;
    NodePtr right;

    public:
    ParameterListNode(NodePtr _left, NodePtr _right){
        type = "parameter list";
        left = _left;
        right = _right;
    }
    NodePtr GetLeft() const{
        return left;
    }
    NodePtr GetRight() const{
        return right;
    }
};

class ParameterDeclarationNode : public Tree
{
    protected:
    NodePtr specifiers;
    NodePtr identifier;

    public:
    ParameterDeclarationNode(NodePtr _specifiers, NodePtr _identifier){
        type = "parameter declaration";
        specifiers = _specifiers;
        identifier = _identifier;
    }
    NodePtr GetSpecifiers() const{
        return specifiers;
    }
    NodePtr GetIdentifier() const{
        return identifier;
    }
};

class IdentifierListNode : public Tree
{
    protected:
    NodePtr left;
    NodePtr right;

    public:
    IdentifierListNode(NodePtr _left, NodePtr _right){
        type = "identifier list";
        left = _left;
        right = _right;
    }
    NodePtr GetLeft() const{
        return left;
    }
    NodePtr GetRight() const{
        return right;
    }
};

class CompoundStatementNode : public Tree
{
    protected:
    NodePtr next;

    public:
    CompoundStatementNode(NodePtr _next){
        type = "compound statement";
        next = _next;
    }
    NodePtr GetNext() const{
        return next;
    }
};

class CompoundListNode : public Tree
{
    protected:
    NodePtr left;
    NodePtr right;
    public:
    CompoundListNode(NodePtr _left, NodePtr _right){
        type = "compound list";
        left = _left;
        right = _right;
    }
    NodePtr GetLeft() const{
        return left;
    }
    NodePtr GetRight() const{
        return right;
    }
};

class DeclarationListNode : public Tree
{
    protected:
    NodePtr left;
    NodePtr right;

    public:
    DeclarationListNode(NodePtr _left, NodePtr _right){
        type = "declaration list";
        left = _left;
        right = _right;
    }
    NodePtr GetLeft() const{
        return left;
    }
    NodePtr GetRight() const{
        return right;
    }
};

class StatementListNode : public Tree
{
    protected:
    NodePtr left;
    NodePtr right;

    public:
    StatementListNode(NodePtr _left, NodePtr _right){
        type = "statement list";
        left = _left;
        right = _right;
    }
    NodePtr GetLeft() const{
        return left;
    }
    NodePtr GetRight() const{
        return right;
    }
};

class LabelledStatementNode : public Tree
{
    protected:
    NodePtr condition;
    NodePtr statements;

    public:
    LabelledStatementNode(NodePtr _condition, NodePtr _statements){
        type = "labelled statement";
        condition = _condition;
        statements = _statements;
    }
    NodePtr GetCondition() const{
        return condition;
    }
    NodePtr GetStatements() const{
        return statements;
    }
};

class ExpressionStatementNode : public Tree
{
    protected:
    NodePtr next;

    public:
    ExpressionStatementNode(NodePtr _next){
        type = "expression statement";
        next = _next;
    }
    NodePtr GetNext() const{
        return next;
    }
};

class SelectionNode : public Tree
{
    protected:
    NodePtr condition;
    NodePtr truepath;
    NodePtr falsepath;

    public:
    SelectionNode(const std::string &_type, NodePtr _condition, NodePtr _truepath, NodePtr _falsepath){
        type = _type;
        condition = _condition;
        truepath = _truepath;
        falsepath = _falsepath;
    }
    NodePtr GetCondition() const{
        return condition;
    }
    NodePtr GetTruePath() const{
        return truepath;
    }
    NodePtr GetFalsePath() const{
        return falsepath;
    }
};

class IterationNode : public Tree
{
    protected:
    NodePtr condition_1;
    NodePtr condition_2;
    NodePtr condition_3;
    NodePtr statements;

    public:
    IterationNode(const std::string &_type, NodePtr _condition_1, NodePtr _condition_2, NodePtr _condition_3, NodePtr _statements){
        type = _type;
        condition_1 = _condition_1;
        condition_2 = _condition_2;
        condition_3 = _condition_3;
        statements = _statements;
    }
    NodePtr GetConditionOne() const{
        return condition_1;
    }
    NodePtr GetConditionTwo() const{
        return condition_2;
    }
    NodePtr GetConditionThree() const{
        return condition_3;
    }
    NodePtr GetStatements() const{
        return statements;
    }
};

class JumpNode : public Tree
{
    protected:
    NodePtr returnvalue;

    public:
    JumpNode(const std::string &_type, NodePtr _returnvalue){
        type = _type;
        returnvalue = _returnvalue;
    }
    NodePtr GetReturnValue() const{
        return returnvalue;
    }
};

// class ConstantExprNode : public Tree
// {
//     protected:
//     NodePtr next;

//     public:
//     ConstantExprNode(NodePtr _next){
//         type = "constant expression";
//         next = _next;
//     }
//     NodePtr GetNext() const{
//         return next;
//     }
// };

class ExpressionNode : public Tree
{
    protected:
    NodePtr left;
    NodePtr right;

    public:
    ExpressionNode(NodePtr _left, NodePtr _right){
        type = "expression node";
        left = _left;
        right = _right;
    }
    NodePtr GetLeft() const{
        return left;
    }
    NodePtr GetRight() const{
        return right;
    }
};

class AssignmentExprNode : public Tree
{
    protected:
    NodePtr left; // Target
    NodePtr right; // Value

    public:
    AssignmentExprNode(const std::string &_type, NodePtr _left, NodePtr _right){
        type = _type;
        left = _left;
        right = _right;
    }
    NodePtr GetLeft() const{
        return left;
    }
    NodePtr GetRight() const{
        return right;
    }
};

class ConditionalExprNode : public Tree
{
    protected:
    NodePtr condition;
    NodePtr truepath;
    NodePtr falsepath;

    public:
    ConditionalExprNode(NodePtr _condition, NodePtr _truepath, NodePtr _falsepath){
        type = "conditional expression";
        condition = _condition;
        truepath = _truepath;
        falsepath = _falsepath;
    }
    NodePtr GetCondition() const{
        return condition;
    }
    NodePtr GetTruePath() const{
        return truepath;
    }
    NodePtr GetFalsePath() const{
        return falsepath;
    }
};

class LogicalExprNode : public Tree
{
    protected:
    NodePtr left;
    NodePtr right;

    public:
    LogicalExprNode(const std::string &_type, NodePtr _left, NodePtr _right){
        type = _type;
        left = _left;
        right = _right;
    }
    NodePtr GetLeft() const{
        return left;
    }
    NodePtr GetRight() const{
        return right;
    }
};

class BitExprNode : public Tree
{
    protected:
    NodePtr left;
    NodePtr right;

    public:
    BitExprNode(const std::string &_type, NodePtr _left, NodePtr _right){
        type = _type;
        left = _left;
        right = _right;
    }
    NodePtr GetLeft() const{
        return left;
    }
    NodePtr GetRight() const{
        return right;
    }
};

class ShiftExprNode : public Tree
{
    protected:
    NodePtr left;
    NodePtr right;

    public:
    ShiftExprNode(const std::string &_type, NodePtr _left, NodePtr _right){
        type = _type;
        left = _left;
        right = _right;
    }
    NodePtr GetLeft() const{
        return left;
    }
    NodePtr GetRight() const{
        return right;
    }
};

class AlgebraExprNode : public Tree
{
    protected:
    NodePtr left;
    NodePtr right;

    public:
    AlgebraExprNode(const std::string &_type, NodePtr _left, NodePtr _right){
        type = _type;
        left = _left;
        right = _right;
    }
    NodePtr GetLeft() const{
        return left;
    }
    NodePtr GetRight() const{
        return right;
    }
};

class CastExprNode : public Tree
{
    protected:
    NodePtr left;
    NodePtr right;

    public:
    CastExprNode(NodePtr _left, NodePtr _right){
        type = "cast expression";
        left = _left;
        right = _right;
    }
    NodePtr GetLeft() const{
        return left;
    }
    NodePtr GetRight() const{
        return right;
    }
};

class UnaryExprNode : public Tree
{
    protected:
    NodePtr next;

    public:
    UnaryExprNode(const std::string &_type, NodePtr _next){
        type = _type;
        next = _next;
    }
    NodePtr GetNext() const{
        return next;
    }
};

class PostFixExprNode: public Tree
{
    protected:
    NodePtr identifier;
    NodePtr index;
    NodePtr arguments;

    public:
    PostFixExprNode(const std::string &_type, NodePtr _identifier, NodePtr _index, NodePtr _arguments){
        type = _type;
        identifier = _identifier;
        index = _index;
        arguments = _arguments;
    }
    NodePtr GetIdentifier() const{
        return identifier;
    }
    NodePtr GetIndex() const{
        return index;
    }
    NodePtr GetArguments() const{
        return arguments;
    }
};

class ArgumentExprNode : public Tree
{
    protected:
    NodePtr left;
    NodePtr right;

    public:
    ArgumentExprNode(NodePtr _left, NodePtr _right){
        type = "argument expression";
        left = _left;
        right = _right;
    }
    NodePtr GetLeft() const{
        return left;
    }
    NodePtr GetRight() const{
        return right;
    }
};

class PrimaryExprNode : public Tree
{
    protected:
    NodePtr next;

    public:
    PrimaryExprNode(NodePtr _next){
        type = "primary expression";
        next = _next;
    }
    NodePtr GetNext() const{
        return next;
    }
};

class EnumeratorNode : public Tree {
	
    private:
    std::string id;

    protected:
    NodePtr next;

    public:
    EnumeratorNode(const std::string &_id, NodePtr _next){
        type = "enumerator";
        id = _id;
        next = _next;
    }
    const std::string GetId() const{
        return id;
    }
    NodePtr GetNext() const{
        return next;
    }
};



class EnumeratorListNode : public Tree {
    
    protected:
    NodePtr left;
    NodePtr right;

    public:
    EnumeratorListNode(NodePtr _left, NodePtr _right){
        type = "enumerator list";
        left = _left;
        right = _right;
    }
    NodePtr GetLeft() const{
        return left;
    }
    NodePtr GetRight() const{
        return right;
    }
};


class EnumSpecifierNode : public Tree {

    private:
    std::string id;

    protected:
    NodePtr statements;

    public:
    EnumSpecifierNode(NodePtr _statements, const std::string &_id){
        type = "enumerator specifier";
        id = _id;
        statements = _statements;
    }
    const std::string GetId() const{
        return id;
    }
    NodePtr GetStatements() const{
        return statements;
    }

};
 

class TypeNameNode : public Tree
{
    protected:
    NodePtr specifiers;
    NodePtr declarator;

    public:
    TypeNameNode(NodePtr _specifiers, NodePtr _declarator){
        type = "type name";
        specifiers = _specifiers;
        declarator = _declarator;
    }
    NodePtr GetSpecifiers() const{
        return specifiers;
    }
    NodePtr GetDeclarator() const{
        return declarator;
    }
};

class SpecifierQualifierListNode : public Tree
{
    protected:
    NodePtr left;
    NodePtr right;

    public:
    SpecifierQualifierListNode(NodePtr _left, NodePtr _right){
        type = "specifier qualifier list";
        left = _left;
        right = _right;
    }
    NodePtr GetLeft() const{
        return left;
    }
    NodePtr GetRight() const{
        return right;
    }
};

class AbstractDeclaratorNode : public Tree
{
    protected:
    NodePtr pointer;
    NodePtr declarator;

    public:
    AbstractDeclaratorNode(NodePtr _pointer, NodePtr _declarator){
        type = "abstract declarator";
        pointer = _pointer;
        declarator = _declarator;
    }
    NodePtr GetPointer() const{
        return pointer;
    }
    NodePtr GetDeclarator() const{
        return declarator;
    }
};

class DirectAbstractDeclaratorNode : public Tree
{
    protected:
    NodePtr left;
    NodePtr right;

    public:
    DirectAbstractDeclaratorNode(const std::string& _type, NodePtr _left, NodePtr _right){
        type = _type;
        left = _left;
        right = _right;
    }
    NodePtr GetLeft() const{
        return left;
    }
    NodePtr GetRight() const{
        return right;
    }
};

class AbstractDeclaratorParameterNode : public Tree
{
    protected:
    NodePtr next;

    public:
    AbstractDeclaratorParameterNode(const std::string& _type, NodePtr _next){
        type = _type;
        next = _next;
    }
    NodePtr GetNext() const{
        return next;
    }
};

class Variable : public Tree
{
    private:
    std::string id;

    public:
    Variable(const std::string &_id){
        type = "variable";
        id = _id;
    }
    const std::string GetId() const{
        return id;
    }
    // Still to add stuff for bindings (Maybe?)
};

class Number : public Tree
{
    private:
    double value;

    public:
    Number(double _value){
        type = "number";
        value = _value;
    }
    const double GetValue() const{
        return value;
    }
};

class String : public Tree
{
    private:
    std::string str;

    public:
    String(std::string _str){
        type = "string literal";
        str = _str;
    }
    const std::string GetID() const{
        return str;
    }
};

struct VariableContext
{
    std::vector<int32_t> address;
    std::vector<int32_t> scope;
    std::vector<std::string> type;
};

struct FunctionContext
{
    int32_t scope;
    std::string type;
    std::vector<std::string> parameters;
};

struct EnumContext
{
    std::map<std::string,int> bindings;
    int counter = 0;
};

struct EnumValues{

	std::string id;
	double value;
};

struct Enumeration{

	std::string ScopeID;
	std::string id;
    std::vector<EnumValues> EnumList;
	double value;
};

struct typedefs{

	int Scope=0;
	std::string TypeSpec;
	std::string DummyName;

};


struct binding {
		std::string id = "";		//name of variable
		double value = 0;
        std::string scope = "";		//name of scope the variable is in

		std::string DataType;
		std::string StorageClass;
		
        int param_offset = 0;
		bool Pointer=false;
		int PointerLevels=0;
		int PointerLevelsTemp=0;
		bool initialized = false;
};



struct InterpretContext
{
    std::vector<int32_t> params;

    // Stuff for translator
    std::vector<std::string> globalVars;

    // Stuff for code generator
    int frameNum = 0; // The stack frame of the current function/scope
    std::vector<int> frameSizes; // Frame size
    std::vector<int> varCount; // Number of variables in each frame
    std::vector<std::string> allVars; // List of all variable names expected in program
    int globalCount = 0; // Number of global variables declared
    std::string global_start; // Start of program global scope
    std::string global_end; // End of program global scope
    std::string program_end; // End of the entire program code
    std::map<std::string,VariableContext> bindings; // Pointers to variable locations on stack
    std::string identifier;
    std::string specifier;
    std::string qualifier;
    int assignState = 0; // State for variable node: 
    // 0 = no-assign, 
    // 1 = variable declaration, 
    // 2 = function declaration, 
    // 3 = variable assign expr,
    // 4 = function call,
    // 5 = forward declaration,
    // 6 = sized array declaration,
    // 7 = unsized array declaration,
    std::map<std::string,FunctionContext> functions; // Map of functions and properties
    std::vector<std::string> totalFuncts; // List of function keys
    std::vector<std::string> allFuncts; // List of all functions expected in program
    std::vector<std::string> functionEnds; // List of function end labels
    std::vector<int32_t> argSum = {44}; // Stores additive components of address in $a0 during nested function calls
    std::vector<int> argCount = {0}; // Stores the number argument the parameter storage is up to
    int infRegNum = 1; // Variable to assign for use of infinite registers
    int labelCount = 0; // Marker for creating labels
    std::vector<std::string> scopeStart = {"main"}; // List of labels that mark the start of the current level of scope
    std::vector<std::string> scopeEnd = {"end"}; // List of labels that mark the end of the current scope
    std::vector<std::string> switchLabel; // List of labels that mark the condition skipping jumps for a switch-case statement
    std::vector<int32_t> switchReg; // Register address that contains evaluation of switch expression
    int scopeLabel = 0; // Keeps track of which index of the lists corresponding to the current scope
    int indexOffset = 0; // Address offset imposed by arrays
    std::vector<std::string> forwardDecs; // List of forward declarations
    std::map<std::string,EnumContext> enumList; // List of declared enum types

    // Stuff for both
    int scope = 0;
    std::vector<std::string> totalVars; // List of variable keys

    
    //for enumeration
    int EnumCounter=0;

    std::vector<Enumeration> Enum; // List of Enum variable keys

	Enumeration EnumTemp;
	EnumValues EnumValuesTemp;
	
	bool EnumExists = false;
	bool enum_constant=false;
	std::vector<int> EnumOperands;
	int newScope=0;

    //for TypeDef
    std::vector<typedefs> TypeAssoc;
	typedefs TypeDef;
	bool typedefs_=false;
    std::string funct_id = "";

    //for storage class variables
	std::vector<binding> Variables;
	binding variable;

    //for type casted variables
    bool Cast=false;
	std::string CastType = "";


};


int32_t Interpret(
    std::ostream* output,
    InterpretContext &context,
    NodePtr program
);

void Compile(
    std::ostream* output,
    InterpretContext& contxt,
    NodePtr program
);


#endif
