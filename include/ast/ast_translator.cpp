#include "ast_node.hpp"

#include <regex> // Is this necessary ???

void AddToGlobalVars(InterpretContext &context, std::string id);
void AddToTotalVars(InterpretContext &context, std::string id);
bool InTotalVars(InterpretContext &context, std::string id);

bool InEnum(InterpretContext &context, std::string id);
bool InEnumList(InterpretContext &context, std::string id);

// Test translator with bin\c_compiler --translate [input filename] -o [output filename]

int32_t Interpret(
    std::ostream* output,
    InterpretContext &context, // Contains the parameters and variable bindings
    NodePtr program
){
    if(program == NULL){
        throw std::runtime_error("Unhandled NULL-type ast node \n");
    }

    if(program->GetType() == "root"){
        Interpret(output, context, program->GetNext());
    }
    else if(program->GetType() == "program"){
        Interpret(output, context, program->GetLeft());
        Interpret(output, context, program->GetRight());
    }
    else if(program->GetType() == "variable declaration"){
        Interpret(output, context, program->GetLeft());
        Interpret(output, context, program->GetRight());
        *output << "\n";
        for(int i = 0; i < context.scope; i++){
            *output << "\t";
        }
    }
    else if(program->GetType() == "declaration specifier"){
        
        //storage class for typedef speciifers
        if(program->GetLeft()->GetType() == "typedef" ) {
			if(context.typedefs_){
				context.TypeAssoc.push_back(context.TypeDef);
				context.typedefs_ = false;
			}		
		}
        
        Interpret(output, context, program->GetLeft());
        Interpret(output, context, program->GetRight());
    }
    else if(program->GetType() == "typedef"){ context.typedefs_ = true; }
    else if(program->GetType() == "extern"){ context.variable.StorageClass = "extern"; }
    else if(program->GetType() == "static"){ context.variable.StorageClass = "static"; }
    else if(program->GetType() == "auto"){ context.variable.StorageClass = "auto"; }
    else if(program->GetType() == "void"){ /* Do Nothing */ }
    else if(program->GetType() == "bool"){ 
    
        if( !context.typedefs_  && !context.Cast ){ //if NOT typedef or Cast
            context.variable.DataType = "bool";
        }
        else if( context.typedefs_  && !context.Cast){ //if typedef
            context.TypeDef.TypeSpec = "bool";
        }
        else if(!context.typedefs_  && context.Cast){ //if Cast
            context.CastType = "bool"; 
        }
    }
    else if(program->GetType() == "char"){ 
        
        if( !context.typedefs_  && !context.Cast ){ //if NOT typedef or Cast
            context.variable.DataType = "char";
        }
        else if( context.typedefs_  && !context.Cast){ //if typedef
            context.TypeDef.TypeSpec = "char";
        }
        else if(!context.typedefs_  && context.Cast){ //if Cast
            context.CastType = "char"; 
        }
    }
    else if(program->GetType() == "float"){ 
        
        if( !context.typedefs_  && !context.Cast ){ //if NOT typedef or Cast
            context.variable.DataType = "float";
        }
        else if( context.typedefs_  && !context.Cast){ //if typedef
            context.TypeDef.TypeSpec = "float";
        }
        else if(!context.typedefs_  && context.Cast){ //if Cast
            context.CastType = "float"; 
        } 
    
    }
    else if(program->GetType() == "int"){ 
        
        if( !context.typedefs_  && !context.Cast ){ //if NOT typedef or Cast
            context.variable.DataType = "int";
        }
        else if( context.typedefs_  && !context.Cast){ //if typedef
            context.TypeDef.TypeSpec = "int";
        }
        else if(!context.typedefs_  && context.Cast){ //if Cast
            context.CastType = "int"; 
        }
        
    }
    else if(program->GetType() == "double"){ 
        
        if( !context.typedefs_  && !context.Cast ){ //if NOT typedef or Cast
            context.variable.DataType = "double";
        }
        else if( context.typedefs_  && !context.Cast){ //if typedef
            context.TypeDef.TypeSpec = "double";
        }
        else if(!context.typedefs_  && context.Cast){ //if Cast
            context.CastType = "double"; 
        } 
        
    }
    else if(program->GetType() == "short"){ 
        
        if( !context.typedefs_  && !context.Cast ){ //if NOT typedef or Cast
            context.variable.DataType = "short";
        }
        else if( context.typedefs_  && !context.Cast){ //if typedef
            context.TypeDef.TypeSpec = "short";
        }
        else if(!context.typedefs_  && context.Cast){ //if Cast
            context.CastType = "short"; 
        }
    }
    else if(program->GetType() == "long"){ 
        
        if( !context.typedefs_  && !context.Cast ){ //if NOT typedef or Cast
            context.variable.DataType = "long";
        }
        else if( context.typedefs_  && !context.Cast){ //if typedef
            context.TypeDef.TypeSpec = "long";
        }
        else if(!context.typedefs_  && context.Cast){ //if Cast
            context.CastType = "long"; 
        }
    
    }
    else if(program->GetType() == "unsigned"){ 
        
        if( !context.typedefs_  && !context.Cast ){ //if NOT typedef or Cast
            context.variable.DataType = "unsigned";
        }
        else if( context.typedefs_  && !context.Cast){ //if typedef
            context.TypeDef.TypeSpec = "unsigned";
        }
        else if(!context.typedefs_  && context.Cast){ //if Cast
            context.CastType = "unsigned"; 
        }
        
    }
    else if(program->GetType() == "signed" ){ 
        
        if( !context.typedefs_  && !context.Cast ){ //if NOT typedef or Cast
            context.variable.DataType = "signed";
        }
        else if( context.typedefs_  && !context.Cast){ //if typedef
            context.TypeDef.TypeSpec = "signed";
        }
        else if(!context.typedefs_  && context.Cast){ //if Cast
            context.CastType = "signed"; 
        } 
        
    }
    else if(program->GetType() == "const"){ /* Do Nothing */ }
    else if(program->GetType() == "volatile"){ /* Do Nothing */ }
    else if(program->GetType() == "initial declaration list"){
        Interpret(output, context, program->GetLeft());
        Interpret(output, context, program->GetRight());
    }
    else if(program->GetType() == "init assign"){
        Interpret(output, context, program->GetLeft());
        *output << " = ";
        if(program->GetRight() == NULL){
            *output << "0";
        }
        else{
            Interpret(output, context, program->GetRight());
        }
    }
    else if(program->GetType() == "declaration identifier"){
        // Pointers not supported in python?
        Interpret(output, context, program->GetIdentifier());
    }
    else if(program->GetType() == "array declaration"){
        Interpret(output, context, program->GetLeft());
    }
    else if(program->GetType() == "direct declaration"){
        Interpret(output, context, program->GetLeft());
        *output << "(";
        if(program->GetRight() != NULL){
            Interpret(output, context, program->GetRight());
        }
        *output << ")";
    }
    else if(program->GetType() == "array initialization"){
        *output << "[";
        if(program->GetNext() != NULL){
            Interpret(output, context, program->GetNext());
        }
        *output << "]";
    }
    else if(program->GetType() == "initializer list"){
        Interpret(output, context, program->GetLeft());
        *output << ",";
        Interpret(output, context, program->GetRight());
    }
    else if(program->GetType() == "function declaration"){
        if(program->GetStatements() != NULL){
            context.scope += 1;
            *output << "def ";
            Interpret(output, context, program->GetIdentifier());
            *output << ":\n";
            for(int i = 0; i < context.scope; i++){
                *output << "\t";
            }
            for(int v = 0; v < context.globalVars.size(); v++){
                *output << "global " << context.globalVars[v] << "\n";
                for(int i = 0; i < context.scope; i++){
                    *output << "\t";
                }
            }
            Interpret(output, context, program->GetStatements());
            context.scope -= 1;
            *output << "\n";
            for(int i = 0; i < context.scope; i++){
                *output << "\t";
            }
        }
    }
    else if(program->GetType() == "forward declaration"){ /* Forward declarations not supported in python? */ }
    else if(program->GetType() == "parameter type list"){
        Interpret(output, context, program->GetLeft());
        if(program->GetRight() != NULL){
            Interpret(output, context, program->GetRight());
        }
    }
    else if(program->GetType() == "parameter list"){
        Interpret(output, context, program->GetLeft());
        if(program->GetRight() != NULL){
            *output << ",";
            Interpret(output, context, program->GetRight());
        }
    }
    else if(program->GetType() == "parameter declaration"){
        if(program->GetIdentifier() != NULL){
            Interpret(output, context, program->GetIdentifier());
        }
    }
    else if(program->GetType() == "identifier list"){
        Interpret(output, context, program->GetLeft());
        *output << ",";
        Interpret(output, context, program->GetRight());
    }
    else if(program->GetType() == "compound statement"){
        if(program->GetNext() != NULL){
            Interpret(output, context, program->GetNext());
        }
        else{
            *output<<"pass";
        }
    }
    else if(program->GetType() == "compound list"){
        if(program->GetLeft() != NULL){
            Interpret(output, context, program->GetLeft());
        }
        if(program->GetRight() != NULL){
            Interpret(output, context, program->GetRight());
        }
    }
    else if(program->GetType() == "declaration list"){
        if(program->GetLeft() != NULL){
            Interpret(output, context, program->GetLeft());
        }
        if(program->GetRight() != NULL){
            Interpret(output, context, program->GetRight());
        }
    }
    else if(program->GetType() == "statement list"){
        if(program->GetLeft() != NULL){
            Interpret(output, context, program->GetLeft());
        }
        if(program->GetRight() != NULL){
            Interpret(output, context, program->GetRight());
        }
    }
    else if(program->GetType() == "labelled statement"){
        // ??? Is this in the spec?
    }
    else if(program->GetType() == "expression statement"){
        if(program->GetNext() != NULL){
            Interpret(output, context, program->GetNext());
        }
        *output << "\n";
        for(int i = 0; i < context.scope; i++){
            *output << "\t";
        }
    }
    else if(program->GetType() == "if"){
        *output << "if(";
        Interpret(output, context, program->GetCondition());
        *output << "):\n";
        context.scope += 1;
        for(int i = 0; i < context.scope; i++){
            *output << "\t";
        }
        Interpret(output, context, program->GetTruePath());
        context.scope -= 1;
        *output << "\n";
        for(int i = 0; i < context.scope; i++){
            *output << "\t";
        }
    }
    else if(program->GetType() == "if else"){
        *output << "if(";
        Interpret(output, context, program->GetCondition());
        *output << "):\n";
        context.scope += 1;
        for(int i = 0; i < context.scope; i++){
            *output << "\t";
        }
        Interpret(output, context, program->GetTruePath());
        *output << "\n";
        for(int i = 0; i < context.scope - 1; i++){
            *output << "\t";
        }
        *output << "else:\n";
        for(int i = 0; i < context.scope; i++){
            *output << "\t";
        }
        Interpret(output, context, program->GetFalsePath());
        context.scope -= 1;
        *output << "\n";
        for(int i = 0; i < context.scope; i++){
            *output << "\t";
        }
    }
    else if(program->GetType() == "switch"){}
    else if(program->GetType() == "while"){
        *output << "while(";
        Interpret(output, context, program->GetConditionOne());
        *output << "):\n";
        context.scope += 1;
        for(int i = 0; i < context.scope; i++){
            *output << "\t";
        }
        Interpret(output, context, program->GetStatements());
        context.scope -= 1;
        *output << "\n";
        for(int i = 0; i < context.scope; i++){
            *output << "\t";
        }
    }
    else if(program->GetType() == "do"){
        *output << "while True:\n";
        context.scope += 1;
        for(int i = 0; i < context.scope; i++){
            *output << "\t";
        }
        Interpret(output, context, program->GetStatements());
        *output << "if(";
        Interpret(output, context, program->GetConditionOne());
        *output << "):\n";
        context.scope += 1;
        for(int i = 0; i < context.scope; i++){
            *output << "\t";
        }
        *output << "pass\n";
        for(int i = 0; i < context.scope - 1; i++){
            *output << "\t";
        }
        *output << "else:\n";
        for(int i = 0; i < context.scope; i++){
            *output << "\t";
        }
        *output << "break\n";
        context.scope -= 1;
        *output << "\n";
        for(int i = 0; i < context.scope; i++){
            *output << "\t";
        }
        context.scope -= 1;
        *output << "\n";
        for(int i = 0; i < context.scope; i++){
            *output << "\t";
        }

    }
    else if(program->GetType() == "for"){
        
        Interpret(output, context, program->GetConditionOne());

        *output << "while(";
        Interpret(output, context, program->GetConditionTwo());
        *output << "):\n";
        context.scope += 1;
        for(int i = 0; i < context.scope; i++){
            *output << "\t";
        }
        Interpret(output, context, program->GetStatements());

        Interpret(output, context, program->GetConditionThree());
        
        context.scope -= 1;
        *output << "\n";
        for(int i = 0; i < context.scope; i++){
            *output << "\t";
        }

    }
    else if(program->GetType() == "return"){
        *output << "return ";
        if(program->GetReturnValue() != NULL){
            Interpret(output, context, program->GetReturnValue());
        }
        *output << "\n";
        for(int i = 0; i < context.scope; i++){
            *output << "\t";
        }
    }
    else if(program->GetType() == "continue"){
        *output << "continue\n";
        for(int i = 0; i < context.scope; i++){
            *output << "\t";
        }
    }
    else if(program->GetType() == "break"){
        *output << "break\n";
        for(int i = 0; i < context.scope; i++){
            *output << "\t";
        }
    }
    else if(program->GetType() == "constant expression"){ /* Necessary (y/n)? */ }
    else if(program->GetType() == "expression node"){
        Interpret(output, context, program->GetLeft());
        *output << ",";
        Interpret(output, context, program->GetRight());
    }
    else if(program->GetType() == "assign"){
        Interpret(output, context, program->GetLeft());
        *output << " = ";
        Interpret(output, context, program->GetRight());
    }
    else if(program->GetType() == "+="){
        // Are these types of assignments required in the spec?
        Interpret(output, context, program->GetLeft());
        *output << " += ";
        Interpret(output, context, program->GetRight());
    }
    else if(program->GetType() == "-="){
        Interpret(output, context, program->GetLeft());
        *output << " -= ";
        Interpret(output, context, program->GetRight());
    }
    else if(program->GetType() == "*="){
        Interpret(output, context, program->GetLeft());
        *output << " *= ";
        Interpret(output, context, program->GetRight());
    }
    else if(program->GetType() == "/="){
        Interpret(output, context, program->GetLeft());
        *output << " /= ";
        Interpret(output, context, program->GetRight());
    }
    else if(program->GetType() == "%="){
        Interpret(output, context, program->GetLeft());
        *output << " %= ";
        Interpret(output, context, program->GetRight());
    }
    else if(program->GetType() == "<<="){
        Interpret(output, context, program->GetLeft());
        *output << " <<= ";
        Interpret(output, context, program->GetRight());
    }
    else if(program->GetType() == ">>="){
        Interpret(output, context, program->GetLeft());
        *output << " >>= ";
        Interpret(output, context, program->GetRight());
    }
    else if(program->GetType() == "&="){
        Interpret(output, context, program->GetLeft());
        *output << " &= ";
        Interpret(output, context, program->GetRight());
    }
    else if(program->GetType() == "^="){
        Interpret(output, context, program->GetLeft());
        *output << " ^= ";
        Interpret(output, context, program->GetRight());
    }
    else if(program->GetType() == "|="){
        Interpret(output, context, program->GetLeft());
        *output << " |= ";
        Interpret(output, context, program->GetRight());
    }
    else if(program->GetType() == "conditional expression"){}
    else if(program->GetType() == "||"){
        Interpret(output, context, program->GetLeft());
        *output << " or ";
        Interpret(output, context, program->GetRight());
    }
    else if(program->GetType() == "&&"){
        Interpret(output, context, program->GetLeft());
        *output << " and ";
        Interpret(output, context, program->GetRight());
    }
    else if(program->GetType() == "|"){
        Interpret(output, context, program->GetLeft());
        *output << "|";
        Interpret(output, context, program->GetRight());
    }
    else if(program->GetType() == "^"){
        Interpret(output, context, program->GetLeft());
        *output << "^";
        Interpret(output, context, program->GetRight());
    }
    else if(program->GetType() == "&"){
        Interpret(output, context, program->GetLeft());
        *output << "&";
        Interpret(output, context, program->GetRight());
    }
    else if(program->GetType() == "=="){
        Interpret(output, context, program->GetLeft());
        *output << "==";
        Interpret(output, context, program->GetRight());
    }
    else if(program->GetType() == "!="){
        Interpret(output, context, program->GetLeft());
        *output << "!=";
        Interpret(output, context, program->GetRight());
    }
    else if(program->GetType() == ">"){
        Interpret(output, context, program->GetLeft());
        *output << ">";
        Interpret(output, context, program->GetRight());
    }
    else if(program->GetType() == "<"){
        Interpret(output, context, program->GetLeft());
        *output << "<";
        Interpret(output, context, program->GetRight());
    }
    else if(program->GetType() == ">="){
        Interpret(output, context, program->GetLeft());
        *output << ">=";
        Interpret(output, context, program->GetRight());
    }
    else if(program->GetType() == "<="){
        Interpret(output, context, program->GetLeft());
        *output << "<=";
        Interpret(output, context, program->GetRight());
    }
    else if(program->GetType() == "<<"){
        Interpret(output, context, program->GetLeft());
        *output << "<<";
        Interpret(output, context, program->GetRight());
    }
    else if(program->GetType() == ">>"){
        Interpret(output, context, program->GetLeft());
        *output << ">>";
        Interpret(output, context, program->GetRight());
    }
    else if(program->GetType() == "+"){
        Interpret(output, context, program->GetLeft());
        *output << "+";
        Interpret(output, context, program->GetRight());
    }
    else if(program->GetType() == "-"){
        Interpret(output, context, program->GetLeft());
        *output << "-";
        Interpret(output, context, program->GetRight());
    }
    else if(program->GetType() == "*"){
        Interpret(output, context, program->GetLeft());
        *output << "*";
        Interpret(output, context, program->GetRight());
    }
    else if(program->GetType() == "/"){
        Interpret(output, context, program->GetLeft());
        *output << "/";
        Interpret(output, context, program->GetRight());
    }
    else if(program->GetType() == "%"){
        Interpret(output, context, program->GetLeft());
        *output << "%";
        Interpret(output, context, program->GetRight());
    }
    else if(program->GetType() == "cast expression"){
        Interpret(output, context, program->GetRight());
    }
    else if(program->GetType() == "++_"){
        Interpret(output, context, program->GetNext());
        *output << "+=1 ";
    }
    else if(program->GetType() == "--_"){
        Interpret(output, context, program->GetNext());
        *output << "-=1 ";
    }
    else if(program->GetType() == "+_"){
        *output << "+";
        Interpret(output, context, program->GetNext());
    }
    else if(program->GetType() == "-_"){
        *output << "-";
        Interpret(output, context, program->GetNext());
    }
    else if(program->GetType() == "&_"){ /* Pointers not supported */ }
    else if(program->GetType() == "*_"){ /* Pointers not supported */ }
    else if(program->GetType() == "~_"){
        *output << " ~";
        Interpret(output, context, program->GetNext());
    }
    else if(program->GetType() == "!"){
        *output << " not ";
        Interpret(output, context, program->GetNext());
    }
    else if(program->GetType() == "sizeof"){}
    else if(program->GetType() == "array element call"){
        Interpret(output, context, program->GetIdentifier());
        *output << "[";
        if(program->GetIndex() != NULL){
            Interpret(output, context, program->GetIndex());
        }
        *output << "]";
    }
    else if(program->GetType() == "direct function call"){
        Interpret(output, context, program->GetIdentifier());
        *output << "(";
        if(program->GetArguments() != NULL){
            Interpret(output, context, program->GetArguments());
        }
        *output << ")";
    }
    else if(program->GetType() == "_++"){
        Interpret(output, context, program->GetIdentifier());
        *output << "+=1 ";
    }
    else if(program->GetType() == "_--"){
        Interpret(output, context, program->GetIdentifier());
        *output << "-=1 ";
    }
    else if(program->GetType() == "argument expression"){
        Interpret(output, context, program->GetLeft());
        *output << ",";
        Interpret(output, context, program->GetRight());
    }
    else if(program->GetType() == "primary expression"){
        *output << "(";
        Interpret(output, context, program->GetNext());
        *output << ")";
    }
    else if(program->GetType() == "enumerator"){
        
        *output << program->GetId();
            
        if(program->GetNext() == NULL ){

            context.EnumValuesTemp.id = program->GetId(); //record enumvalues
			context.EnumValuesTemp.value = context.EnumCounter;
			*output << " = " << context.EnumValuesTemp.value;
			//context.EnumCounter+=1;
			
            context.EnumTemp.EnumList.push_back(context.EnumValuesTemp); //record enum values in enum list 
            
        }
        else if (program->GetNext() != NULL){
            context.enum_constant = true;
            *output << " = ";
			Interpret(output, context, program->GetNext());
            context.EnumCounter-=1;

			context.enum_constant = false;
            if(context.EnumOperands.size())
			{
				context.EnumCounter = context.EnumOperands[context.EnumOperands.size()-1];
				context.EnumValuesTemp.value = context.EnumOperands[context.EnumOperands.size()-1];
				context.EnumValuesTemp.id = program->GetId();
                context.EnumTemp.EnumList.push_back(context.EnumValuesTemp);	
					
				//std::cout << "\n" << contxt.EnumCounter << "\n";
				//std::cout << contxt.EnumTemp.value << " " <<  contxt.EnumTemp.IDENTIFIER   << std::endl;
				for (int i=0; i<=context.EnumOperands.size(); i++){
					context.EnumOperands[i]=0;
				}
			}		
        }
        else{
            //do nothing
        }
    }
    else if(program->GetType() == "enumerator list"){

        
        Interpret(output, context, program->GetRight());
        *output << "\n";
        context.EnumCounter+=1;

        if(program->GetLeft() != NULL){
            for(int i = 0; i < context.scope; i++){
            *output << "\t";
            }
            Interpret(output, context, program->GetLeft());
        }
    }
    else if(program->GetType() == "enumerator specifier"){

        if( program->GetId() == ""){
    
                Interpret(output, context, program->GetStatements());
                
			//	contxt.Enum.push_back(contxt.EnumTemp);	
        }
        else if( program->GetId() != "" && program->GetStatements() == NULL){
            
            
            if( InEnum(context, program->GetId()) == true){
                *output << program->GetId();
                *output << ".";
            }

            if(context.scope == 0){
                AddToGlobalVars(context, program->GetId());
            }
            AddToTotalVars(context, program->GetId());

        }
        else if( program->GetId() != "" && program->GetStatements() != NULL){

            context.EnumTemp.ScopeID = "global";
            *output << "from enum import Enum\n\n";
            *output << "class ";
            *output << program->GetId();
            context.EnumTemp.id = program->GetId();  //record enum variable in vector
            context.Enum.push_back(context.EnumTemp);
            *output << "(Enum):";
            *output << "\n";
            
            context.scope+=1;
            for(int i = 0; i < context.scope; i++){
            *output << "\t";
            }
            Interpret(output, context, program->GetStatements());
            context.scope-=1;
            *output << "\n\n";

        }
        context.EnumCounter=0; //reset enum count
    }
    else if(program->GetType() == "type name"){
        Interpret(output, context, program->GetSpecifiers());
        if(program->GetDeclarator() != NULL){
            Interpret(output, context, program->GetDeclarator());
        }
    }
    else if(program->GetType() == "specifier qualifier list"){
        Interpret(output, context, program->GetLeft());
        Interpret(output, context, program->GetRight());
    }
    else if(program->GetType() == "abstract declarator"){
        // Pointers not supported in python?
        if(program->GetDeclarator() != NULL){
            Interpret(output, context, program->GetDeclarator());
        }
    }
    else if(program->GetType() == "bracketed abstract declarator"){
        *output << "(";
        Interpret(output, context, program->GetLeft());
        *output << ")";
    }
    else if(program->GetType() == "direct abstract declarator"){
        Interpret(output, context, program->GetLeft());
        Interpret(output, context, program->GetRight());
    }
    else if(program->GetType() == "square abstract parameter"){
        *output << "[";
        if(program->GetNext() != NULL){
            Interpret(output, context, program->GetNext());
        }
        *output << "]";
    }
    else if(program->GetType() == "round abstract parameter"){
        *output << "(";
        if(program->GetNext() != NULL){
            Interpret(output, context, program->GetNext());
        }
        *output << ")";
    }
    else if(program->GetType() == "variable"){
        
        
        if( InEnumList(context, program->GetId()) == true){
            *output << context.EnumTemp.id;
            *output << ".";
        }

        if( context.typedefs_ ){
			context.TypeDef.DummyName = program->GetId();
		}	
        

        *output << program->GetId();
        if(context.scope == 0){
            AddToGlobalVars(context, program->GetId());
        }
        AddToTotalVars(context, program->GetId());
    }
    else if(program->GetType() == "number"){
        *output << program->GetValue();
    }
    else if(program->GetType() == "string literal"){
        *output << "\"" << program->GetId() << "\"";
    }
    else{
        throw std::runtime_error("Unknown ast type: \"" + program->GetType() + "\"\n");
    }
}

void AddToGlobalVars(InterpretContext &context, std::string id){
    for(int i = 0; i < context.globalVars.size(); i++){
        if(context.globalVars[i] == id){
            return;
        }
    }
    context.globalVars.push_back(id);
}

void AddToTotalVars(InterpretContext &context, std::string id){
    for(int i = 0; i < context.totalVars.size(); i++){
        if(context.totalVars[i] == id){
            return;
        }
    }
    context.totalVars.push_back(id);
}


bool InTotalVars(InterpretContext &context, std::string id){
    for(int i = 0; i< context.totalVars.size(); i++){
        if(context.totalVars[i] == id){
            return true;
        }
    }
    return false;
}


//for all enum variables
bool InEnum(InterpretContext &context, std::string id){
    for(int i = 0; i< context.Enum.size(); i++){
        if(context.Enum[i].id == id){
            return true;
        }
    }
    return false;
}

//for all enum values in enum
bool InEnumList(InterpretContext &context, std::string id){
    for(int i = 0; i< context.EnumTemp.EnumList.size(); i++){
        if(context.EnumTemp.EnumList[i].id == id){
            return true;
        }
    }
    return false;
}

