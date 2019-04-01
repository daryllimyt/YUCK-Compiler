#include "../ast_node.hpp"

#include "stdint.h"
#include <string>
#include <regex>

bool InTotalVars(InterpretContext &context, std::string id);
std::vector<std::string> CleanBindings(InterpretContext &context);
int32_t LookupVariableAddress(InterpretContext &context, std::string id);
std::string LookupOffsetRegister(InterpretContext &context, std::string id);
int EstimateSpace(NodePtr program);
std::string NewLabel(InterpretContext &context);
int32_t GetArgSum(InterpretContext &context);
bool InForwardDecs(InterpretContext &context, std::string id);
bool InAllFunctions(InterpretContext &context, std::string id);
bool InAllVars(InterpretContext &context, std::string id);
std::vector<std::string> CountAllFunctions(NodePtr program);
void CountAllVars(std::vector<std::string>& list, NodePtr program);
void GetAllNumbers(std::vector<int>& list, NodePtr program);
void SearchSpecifiers(InterpretContext &context, NodePtr program);
int CountGlobalVars(NodePtr program);
std::string EndInstr(bool No_op);
void NoImplementError(NodePtr program);

void Compile(
    std::ostream* output,
    InterpretContext& context,// The name of the register to put the result in
    NodePtr program
)
{
    if(program == NULL){
        throw std::runtime_error("Unhandled NULL-type ast node \n");
    }

    if(program->GetType() == "root"){
        // Calculate number of global variables for actual number, use CountGlobalVars(program->GetNext())
        context.frameSizes = {0}; // <- Using zero temporarily
        context.varCount = {0};
        context.allFuncts = CountAllFunctions(program->GetNext());
        CountAllVars(context.allVars, program->GetNext());
        // Push stack from by space needed for global variables

        // Set end label of program
        context.program_end = NewLabel(context);

        // Some flag for qemu
        *output << ".text" << std::endl;

        Compile(output, context, program->GetNext());
        
        // End label prevents glitching if run with initial $ra = 0x0
        *output << context.program_end << ":" << EndInstr(true);
        // Pad program with noops to clear pipeline
        *output <<  "sll $0, $0, 0" << std::endl;
        *output <<  "sll $0, $0, 0" << std::endl;
        *output <<  "sll $0, $0, 0" << std::endl;
        *output <<  "sll $0, $0, 0" << std::endl;
        *output <<  "sll $0, $0, 0" << std::endl;
    }
    else if(program->GetType() == "program"){
        Compile(output, context, program->GetLeft());
        Compile(output, context, program->GetRight());
    }
    else if(program->GetType() == "variable declaration"){
        // Gets type specifers and sets in context
        // Also sets qualifiers. Necessary (y/n)?
        Compile(output, context, program->GetLeft());
        // Continues to declarations of all variables in this type
        Compile(output, context, program->GetRight());
    }
    else if(program->GetType() == "declaration specifier"){
        // Check both branches for specifiers or qualifiers
        Compile(output, context, program->GetLeft());
        Compile(output, context, program->GetRight());
        // Still requires implementation of combination type specifiers
        // Eg: unsigned char
    }
    else if(program->GetType() == "void"){
        context.specifier = "void";
    }
    else if(program->GetType() == "bool"){
        context.specifier = "bool";
    }
    else if(program->GetType() == "int"){
        context.specifier = "int";
    }
    else if(program->GetType() == "char"){
        context.specifier = "char";
    }
    else if(program->GetType() == "float"){
        context.specifier = "float";
    }
    else if(program->GetType() == "double"){
        context.specifier = "double";
    }
    else if(program->GetType() == "short"){
        context.specifier = "short";
    }
    else if(program->GetType() == "long"){
        context.specifier = "long";
    }
    else if(program->GetType() == "unsigned"){
        context.specifier = "unsigned";
    }
    else if(program->GetType() == "signed"){
        context.specifier = "signed";
    }
    else if(program->GetType() == "const"){
        context.qualifier = "const";
    }
    else if(program->GetType() == "volatile"){
        context.qualifier = "volatile";
    }
    else if(program->GetType() == "initial declaration list"){
        // Type specifier is set in context by this point
        Compile(output, context, program->GetLeft());
        Compile(output, context, program->GetRight());
    }
    else if(program->GetType() == "init assign"){
        context.assignState = 1;
        // Get variable ID from left branch
        Compile(output, context, program->GetLeft());
        std::string id = context.identifier;
        // Variable now has place on stack and is paired with pointer in bindings

        if(program->GetRight() != NULL){
            // Evaluate right branch and store value in stack location
            context.assignState = 0;
            Compile(output, context, program->GetRight());
            int32_t address = LookupVariableAddress(context, id);
            std::string offsetReg = LookupOffsetRegister(context, id);
            *output << "sw $t0, " << address << offsetReg << EndInstr(true);
        }
    }
    else if(program->GetType() == "declaration identifier"){
        if(program->GetPointer() == NULL){
            Compile(output, context, program->GetIdentifier());
        }
        // Do something for pointer
    }
    else if(program->GetType() == "array declaration"){
        std::string qualifier = context.qualifier;
        std::string specifier = context.specifier;
        context.assignState = 0;
        // Get size of array if given
        if(program->GetRight() != NULL){
            Compile(output, context, program->GetRight());
            context.assignState = 6;
        }
        else{
            context.assignState = 7;
        }
        // Size is now in $t0

        // Store size in temporary infinite register
        int32_t infAddress = -4*context.infRegNum;
        context.infRegNum += 1;

        // Get variable id
        Compile(output, context, program->GetLeft());
        std::string id = context.identifier;

        // Declare array struct and bind to identifier

        // Release infinite register
        context.infRegNum -= 1;
    }
    else if(program->GetType() == "direct declaration"){
        // Get function identifier from left branch
        Compile(output, context, program->GetLeft());
        std::string id = context.identifier;
        // Function is now declared and keyed with FunctionContext in context.functions map

        // Set parameters on right branch
        if(program->GetRight() != NULL){
            // Set space and bindings for parameter variables
            Compile(output, context, program->GetRight());
            // Load input values from previous stack frame and store in current frame
        }
        // Assuming no parameters for now

        // Resetting context.identifier may be necessary
        context.identifier = id;

    }
    else if(program->GetType() == "array initialization"){ NoImplementError(program); }
    else if(program->GetType() == "initializer list"){ NoImplementError(program); }
    else if(program->GetType() == "function declaration"){
        if(program->GetStatements() == NULL){
            // Forward declaration
            Compile(output, context, program->GetIdentifier());
        }
        else{
            // Gets type specifiers and sets in context
            std::string return_type = "int";
            context.specifier = return_type;
            if(program->GetSpecifiers() != NULL){
                Compile(output, context, program->GetSpecifiers());
                return_type = context.specifier;
            }

            // Calculate how much space is needed (how??) (By counting through the tree recursively?)
            // Count number of variable declarations (+4 per variable) (+8 for double?)
            int space = EstimateSpace(program->GetStatements());
            // Count number of arguments needed for function calls (+4 per argument)
            space += EstimateSpace(program->GetIdentifier()) - 8; // Subtract function's own identifier
            // Space for saved registers (4*8 = 32)
            space += 32;
            // Space for return address, Copied in from $ra upon start (4)
            space += 4;
            // Space for previous frame address, Copied in from $fp upon start (4)
            space += 4;
            // Space for global address, Copied in from $fp upon start (4)
            space += 4;
            // Padding to ensure that variables are double-aligned (total%8 == 0)
            space += 8 - (space%8);

            context.frameNum += 1;
            if(context.frameNum >= context.frameSizes.size()){
                context.frameSizes.push_back(space);
                context.varCount.push_back(0);
            }
            else{
                context.frameSizes[context.frameNum] = space;
                context.varCount[context.frameNum] = 0;
            }
            // Get identifier
            context.assignState = 2;
            Compile(output, context, program->GetIdentifier());
            std::string id = context.identifier;
            // Declare functions as global if in global scope
            if(context.scope == 0){
                *output << ".globl " << id << EndInstr(false);
            }
            // Set function name as label
            *output << id << ":" << EndInstr(false);
            *output << ".ent " << id << EndInstr(false);
            // Storing $gp in $t5, because I don't know if something happens to $gp?
            *output << "addiu $t5, $gp, 0" << EndInstr(true);
            // These lines are so qemu doesn't complain
            // But it also means we can't use $t8
            *output << ".frame $sp, " << space << ", $ra" << EndInstr(false);
            *output << ".set noreorder" << EndInstr(false);
            *output << ".cpload $t8" << EndInstr(false);
            *output << ".set reorder" << EndInstr(false);
            // Push stack frame
            *output << "addiu $sp, $sp, " << -1*space << EndInstr(true);
            // Store address of previous frame on stack at 0($sp)
            *output << "sw $fp, 0($sp)" << EndInstr(true);
            *output << "add $fp, $sp, $0" << EndInstr(true);
            // Store return address in stack at 4($fp) also stores in $25/$t9
            *output << "sw $ra, 4($sp)" << EndInstr(true);
            *output << "addiu $t9, $ra, 0" << EndInstr(true);
            // Store saved register values ($s0 - $s7) on stack at 8($fp) - 36($fp)
            *output << "sw $s0, 8($sp)" << EndInstr(true);
            *output << "sw $s1, 12($sp)" << EndInstr(true);
            *output << "sw $s2, 16($sp)" << EndInstr(true);
            *output << "sw $s3, 20($sp)" << EndInstr(true);
            *output << "sw $s4, 24($sp)" << EndInstr(true);
            *output << "sw $s5, 28($sp)" << EndInstr(true);
            *output << "sw $s6, 32($sp)" << EndInstr(true);
            *output << "sw $s7, 36($sp)" << EndInstr(true);
            // Store value of $gp on stack
            *output << "sw $gp, 40($gp)" << EndInstr(true);
            *output << ".cprestore 44" << EndInstr(false);
            // Restore $gp at this point
            *output  << "addiu $gp, $t5, 0" << EndInstr(true);
            // Store input arguments on stack
            auto itr = context.functions.find(id);
            for(int i = 0; i < itr->second.parameters.size(); i++){
                int32_t address = LookupVariableAddress(context, itr->second.parameters[i]);
                if(i < 4){
                    *output << "addiu $t0, $a" << i << ", 0" << EndInstr(true);
                }
                else{
                    *output << "lw $t0, " << -8*(i+1) << "($t3)" << EndInstr(true);
                }
                *output << "sw $t0, " << address << "($fp)" << EndInstr(true);
            }

            // Zero all temporary/saved registers
            *output << "addiu $t0, $0, 0" << EndInstr(true);
            *output << "addiu $t1, $0, 0" << EndInstr(true);
            *output << "addiu $t2, $0, 0" << EndInstr(true);
            *output << "addiu $t3, $0, 0" << EndInstr(true);
            *output << "addiu $t4, $0, 0" << EndInstr(true);
            *output << "addiu $t5, $0, 0" << EndInstr(true);
            *output << "addiu $t6, $0, 0" << EndInstr(true);
            *output << "addiu $t7, $0, 0" << EndInstr(true);
            *output << "addiu $t8, $0, 0" << EndInstr(true);
            *output << "addiu $s0, $0, 0" << EndInstr(true);
            *output << "addiu $s1, $0, 0" << EndInstr(true);
            *output << "addiu $s2, $0, 0" << EndInstr(true);
            *output << "addiu $s3, $0, 0" << EndInstr(true);
            *output << "addiu $s4, $0, 0" << EndInstr(true);
            *output << "addiu $s5, $0, 0" << EndInstr(true);
            *output << "addiu $s6, $0, 0" << EndInstr(true);
            *output << "addiu $s7, $0, 0" << EndInstr(true);
            *output << "addiu $v0, $0, 0" << EndInstr(true);
            *output << "addiu $v1, $0, 0" << EndInstr(true);

            // Create target jump for potential return statements
            std::string end_label = NewLabel(context);
            context.functionEnds.push_back(end_label);
            
            // Do stuff
            Compile(output, context, program->GetStatements());

            // Return statement will skip rest of function body to reach here
            *output << end_label << ":" << EndInstr(false);
            context.functionEnds.pop_back();

            // Zero all temporary/saved registers
            *output << "addiu $t0, $0, 0" << EndInstr(true);
            *output << "addiu $t1, $0, 0" << EndInstr(true);
            *output << "addiu $t2, $0, 0" << EndInstr(true);
            *output << "addiu $t3, $0, 0" << EndInstr(true);
            *output << "addiu $t4, $0, 0" << EndInstr(true);
            *output << "addiu $t5, $0, 0" << EndInstr(true);
            *output << "addiu $t6, $0, 0" << EndInstr(true);
            *output << "addiu $t7, $0, 0" << EndInstr(true);
            *output << "addiu $t8, $0, 0" << EndInstr(true);
            *output << "addiu $s0, $0, 0" << EndInstr(true);
            *output << "addiu $s1, $0, 0" << EndInstr(true);
            *output << "addiu $s2, $0, 0" << EndInstr(true);
            *output << "addiu $s3, $0, 0" << EndInstr(true);
            *output << "addiu $s4, $0, 0" << EndInstr(true);
            *output << "addiu $s5, $0, 0" << EndInstr(true);
            *output << "addiu $s6, $0, 0" << EndInstr(true);
            *output << "addiu $s7, $0, 0" << EndInstr(true);
            *output << "addiu $a0, $0, 0" << EndInstr(true);
            *output << "addiu $a1, $0, 0" << EndInstr(true);
            *output << "addiu $a2, $0, 0" << EndInstr(true);
            *output << "addiu $a3, $0, 0" << EndInstr(true);

            // At this point, ($sp) may be different to ($fp)
            // Load saved register values into ($s0 - $s7)
            *output << "lw $s0, 8($fp)" << EndInstr(true);
            *output << "lw $s1, 12($fp)" << EndInstr(true);
            *output << "lw $s2, 16($fp)" << EndInstr(true);
            *output << "lw $s3, 20($fp)" << EndInstr(true);
            *output << "lw $s4, 24($fp)" << EndInstr(true);
            *output << "lw $s5, 28($fp)" << EndInstr(true);
            *output << "lw $s6, 32($fp)" << EndInstr(true);
            *output << "lw $s7, 36($fp)" << EndInstr(true);
            // Load return address into $ra
            *output << "lw $ra, 4($fp)" << EndInstr(true);
            // Load previous frame into $fp
            *output << "lw $fp, 0($fp)" << EndInstr(true);
            // Pop stack frame
            *output << "addiu $sp, $sp, " << space << EndInstr(true);
            context.frameNum -= 1;
            
            // If $ra contains 0x0, jump to end label
            *output << "beq $ra, $0, " << context.program_end << EndInstr(true);
            // Otherwise jump to previous context
            *output << "jr $ra" << EndInstr(true);
            *output << ".end " << id << EndInstr(false);
        }
    }
    else if(program->GetType() == "forward declaration"){
        context.assignState = 5;
        Compile(output, context, program->GetLeft());
    }
    else if(program->GetType() == "parameter list"){
        // Take id of function
        std::string id = context.identifier;

        // Add both branches to parameter list
        Compile(output, context, program->GetLeft());
        // context.identifier must be reset in each case
        context.identifier = id;

        Compile(output, context, program->GetRight());
        context.identifier = id;
    }
    else if(program->GetType() == "parameter declaration"){
        std::string function_id = context.identifier;
        auto itr = context.functions.find(function_id);

        // Set type in context
        Compile(output, context, program->GetSpecifiers());
        std::string type = context.specifier;

        context.assignState = 1;
        context.scope += 1;
        Compile(output, context, program->GetIdentifier());
        itr->second.parameters.push_back(context.identifier);
        context.scope -= 1;
        context.assignState = 2;
    }
    else if(program->GetType() == "identifier list"){ NoImplementError(program); }
    else if(program->GetType() == "compound statement"){
        // Maybe put function body prologue/epilogue here instead?
        context.scope += 1;
        if(program->GetNext() != NULL){
            Compile(output, context, program->GetNext());
        }
        context.scope -= 1;
        // Work out if this will override function parameters ??
        context.totalVars = CleanBindings(context);
    }
    else if(program->GetType() == "compound list"){
        Compile(output, context, program->GetLeft());
        Compile(output, context, program->GetRight());
    }
    else if(program->GetType() == "declaration list"){
        Compile(output, context, program->GetLeft());
        Compile(output, context, program->GetRight());
    }
    else if(program->GetType() == "statement list"){
        Compile(output, context, program->GetLeft());
        Compile(output, context, program->GetRight());
    }
    else if(program->GetType() == "labelled statement"){
        // Get entry label
        // If using enter label, statements are skipped
        // Block begins at condition evaluation
        std::string entry_label = context.switchLabel.back();
        context.switchLabel.pop_back();

        // Jump here if condition true to evaluate statements
        std::string statement_label = NewLabel(context);
        *output << statement_label << ":" << EndInstr(false);
        if(program->GetStatements() != NULL){
            Compile(output, context, program->GetStatements());
        }

        // Once statement is evaluated, condition block is skipped
        std::string skip_label = NewLabel(context);
        *output << "j " << skip_label << EndInstr(true);

        // Entry_label leads here, start here if no case yet to return true
        *output << entry_label << ":" << EndInstr(false);
        if(program->GetCondition() == NULL){
            // If condition NULL -> default to true
            *output << "addiu $t0, $0, 1" << EndInstr(true);
        }
        else{
            // Evaluate condition into $t0
            Compile(output, context, program->GetCondition());
            // Compare with value in infinite register
            int32_t address = context.switchReg.back();
            *output << "lw $t1, " << address << "($fp)" << EndInstr(true);
            std::string true_label = NewLabel(context);
            std::string end_label = NewLabel(context);
            *output << "beq $t1, $t0, " << true_label << EndInstr(true);
            *output << "addiu $t0, $0, 0" << EndInstr(true);
            *output << "j " << end_label << EndInstr(true);
            *output << true_label << ":" << EndInstr(false);
            *output << "addiu $t0, $0, 1" << EndInstr(true);
            *output << end_label << ":" << EndInstr(false);
        }
        // If condition is true, begin evaluating statements
        *output << "bne $t0, $0, " << statement_label << EndInstr(true);
        // Jump to condition evaluation of next case block
        std::string next_label = NewLabel(context);
        context.switchLabel.push_back(next_label);
        *output << "j " << next_label << EndInstr(true);

        // Label to skip conditions leads here
        *output << skip_label << ":" << EndInstr(false);
    }
    else if(program->GetType() == "expression statement"){
        if(program->GetNext() != NULL){
            Compile(output, context, program->GetNext());
        }
    }
    else if(program->GetType() == "if"){
        std::string end_label = NewLabel(context);

        // Evaluate condition and store in $t0
        Compile(output, context, program->GetCondition());

        // If condition is false ($t0 = 0), skip to end_label
        *output << "beq $t0, $0, " << end_label << EndInstr(true);

        // Otherwise, assembly continues on to body of if statement
        Compile(output, context, program->GetTruePath());

        // Label for skipping statement body
        *output << end_label << ":" << EndInstr(false);
    }
    else if(program->GetType() == "if else"){
        std::string false_label = NewLabel(context);
        std::string end_label = NewLabel(context);

        Compile(output, context, program->GetCondition());
        // This time $t0 false only skips as far as the else statement
        *output << "beq $t0, $0, " << false_label << EndInstr(true);

        // If evaluating if statement ($t0 true), skip else statement
        Compile(output, context, program->GetTruePath());
        *output << "j " << end_label << EndInstr(true);

        *output << false_label << ":" << EndInstr(false);
        Compile(output, context, program->GetFalsePath());
        *output << end_label << ":" << EndInstr(false);
    }
    else if(program->GetType() == "switch"){
        // Get label target for breaks in case statements
        std::string end_label = NewLabel(context);
        context.scopeEnd.push_back(end_label);
        context.scope += 1;
        // Save number of switch skip labels at start
        int init_labelCount = context.switchLabel.size();

        // Get condition result (into $t0)
        Compile(output, context, program->GetCondition());
        // Store result in infinite register
        int32_t address = -4*context.infRegNum;
        context.infRegNum += 1;
        context.switchReg.push_back(address);
        *output << "sw $t0, " << address << "($fp)" << EndInstr(true);
        // Start label to jump straight to first condition
        std::string start_label = NewLabel(context);
        context.switchLabel.push_back(start_label);
        *output << "j " << start_label << EndInstr(true);

        // Evaluate statements
        if(program->GetTruePath() != NULL){
            Compile(output, context, program->GetTruePath());
        }
        // If label left over from internal statements, place here
        while(context.switchLabel.size() > init_labelCount){
            *output << context.switchLabel.back() << ":" << EndInstr(false);
            context.switchLabel.pop_back();
        }
        // Break keyword within labelled statements leads here
        *output << end_label << ":" << EndInstr(false);

        // Clean up
        context.scope -= 1;
        context.scopeEnd.pop_back();
        context.infRegNum -= 1;
        context.switchReg.pop_back();
    }
    else if(program->GetType() == "while"){
        std::string start_label = NewLabel(context);
        std::string end_label = NewLabel(context);
        // Labels are stored for use by break/continue keywords
        context.scopeStart.push_back(start_label);
        context.scopeEnd.push_back(end_label);
        // Condition parameters are in same scope as loop body
        context.scope += 1;
        
        // Check condition
        *output << start_label << ":" << EndInstr(false);
        // Check is re-executed every loop iteration
        Compile(output, context, program->GetConditionOne());
        // Condition evaluation is now in $t0

        // Jump to end if condition is false
        *output << "beq $t0, $0, " << end_label << EndInstr(true);

        // Perform statements
        Compile(output, context, program->GetStatements());

        // Return to start_label
        *output << "j " << start_label << EndInstr(true);
        *output << end_label << ":" << EndInstr(false);
        
        // Labels no longer needed
        context.scopeStart.pop_back();
        context.scopeEnd.pop_back();
        context.scope -= 1;
        context.totalVars = CleanBindings(context);
    }
    else if(program->GetType() == "do"){
        std::string start_label = NewLabel(context);
        std::string end_label = NewLabel(context);
        std::string check_label = NewLabel(context);
        // Continue proceeds to condition check
        context.scopeStart.push_back(check_label);
        context.scopeEnd.push_back(end_label);
        context.scope += 1;

        // Loop enters first iteration without checking condition
        *output << start_label << ":" << EndInstr(false);
        Compile(output, context, program->GetStatements());

        // Target jump label for continue keyword
        *output << check_label << ":" << EndInstr(false);
        // Condition is now checked at end
        Compile(output, context, program->GetConditionOne());
        *output << "bne $t0, $0, " << start_label << EndInstr(true);
        *output << end_label << ":" << EndInstr(false);
        
        context.scopeStart.pop_back();
        context.scopeEnd.pop_back();
        context.scope -= 1;
        context.totalVars = CleanBindings(context);
    }
    else if(program->GetType() == "for"){
        // Condition1 = Init_Statement
        // Condition2 = Condition
        // Condition3 = Iteration_Expression
        std::string start_label = NewLabel(context);
        std::string end_label = NewLabel(context);
        std::string continue_label = NewLabel(context);
        context.scopeStart.push_back(continue_label);
        context.scopeEnd.push_back(end_label);

        // Init_Statement is is executed before loop begins
        // Scope of compound statement is nested within scope of init_statement
        // But this behaviour differs between C and C++, so cannot be tested
        context.scope += 1;
        Compile(output, context, program->GetConditionOne());

        // Loop begins here
        *output << start_label << ":" << EndInstr(false);
        // Check condition
        if(program->GetConditionTwo() != NULL){
            Compile(output, context, program->GetConditionTwo());
        }
        else{
            // If not condition, default to true
            *output << "addiu $t0, $0, 1" << EndInstr(true);
        }
        *output << "beq $t0, $0, " << end_label << EndInstr(true);

        // Statements are performed first
        if(program->GetStatements() != NULL){
            Compile(output, context, program->GetStatements());
        }
        // Continue keyword jumps to here
        *output << continue_label << ":" << EndInstr(false);
        // Then Iteration_Expression
        if(program->GetConditionThree() != NULL){
            Compile(output, context, program->GetConditionThree());
        }
        // Branch back to beginning of loop cycle
        *output << "j " << start_label << EndInstr(true);
        *output << end_label << ":" << EndInstr(false);
        context.scope -= 1;
        context.totalVars = CleanBindings(context);
    }
    else if(program->GetType() == "return"){
        // Get return target
        std::string end_label = context.functionEnds.back();
        if(program->GetReturnValue() != NULL){
            context.assignState = 0;
            // Get return value (in $t0)
            Compile(output, context, program->GetReturnValue());
            // Store return value in $v0
            *output << "add $v0, $t0, $0" << EndInstr(true);
        }

        // Jump to return target
        *output << "j " << end_label << EndInstr(true);
    }
    else if(program->GetType() == "continue"){
        // Get last label in context, as this is current scope
        // Keyword continue returns to start of loop
        int labelNum = context.scopeStart.size() - 1;
        std::string start_label = context.scopeStart[labelNum];

        // Branch to this label
        *output << "j " << start_label << EndInstr(true);
    }
    else if(program->GetType() == "break"){
        // Keyword break jumps to end of loop
        int labelNum = context.scopeEnd.size() - 1;
        std::string end_label = context.scopeEnd[labelNum];

        *output << "j " << end_label << EndInstr(true);
    }
    else if(program->GetType() == "expression node"){
        Compile(output, context, program->GetLeft());
        // Left side result $t0 is discarded (overwritten)
        Compile(output, context, program->GetRight());
    }
    else if(program->GetType() == "assign"){
        context.assignState = 3;
        // Get variable identifier from left branch
        Compile(output, context, program->GetLeft());
        std::string id = context.identifier;
        int32_t address = LookupVariableAddress(context, id);
        std::string offsetReg = LookupOffsetRegister(context, id);
        
        // Get assignment value from right branch
        // Expression result is in $t0 (Will function returns be in $v0?)
        // Assign state should be 0 in case branch contains variable read
        context.assignState = 0;
        Compile(output, context, program->GetRight());
        *output << "sw $t0, " << address << offsetReg << EndInstr(true);
    }
    else if(program->GetType() == "+="){
        context.assignState = 3;
        Compile(output, context, program->GetLeft());
        std::string id = context.identifier;
        int32_t address = LookupVariableAddress(context, id);
        std::string offsetReg = LookupOffsetRegister(context, id);

        context.assignState = 0;
        Compile(output, context, program->GetRight());
        // Expression evaluation should be finished by this stage
        // -> All registers other than $t0 are free ($v0 ???)
        // Existing value stored in $t1 to add to $t0 expression result
        *output << "lw $t1, " << address << offsetReg << EndInstr(true);
        *output << "add $t0, $t0, $t1" << EndInstr(true);
        *output << "sw $t0, " << address << offsetReg << EndInstr(true);
    }
    else if(program->GetType() == "-="){
        context.assignState = 3;
        Compile(output, context, program->GetLeft());
        std::string id = context.identifier;
        int32_t address = LookupVariableAddress(context, id);
        std::string offsetReg = LookupOffsetRegister(context, id);

        context.assignState = 0;
        Compile(output, context, program->GetRight());
        *output << "lw $t1, " << address << offsetReg << EndInstr(true);
        *output << "sub $t0, $t1, $t0" << EndInstr(true);
        *output << "sw $t0, " << address << offsetReg << EndInstr(true);
    }
    else if(program->GetType() == "*="){
        context.assignState = 3;
        Compile(output, context, program->GetLeft());
        std::string id = context.identifier;
        int32_t address = LookupVariableAddress(context, id);
        std::string offsetReg = LookupOffsetRegister(context, id);

        context.assignState = 0;
        Compile(output, context, program->GetRight());
        *output << "lw $t1, " << address << offsetReg << EndInstr(true);
        *output << "mult $t0, $t1" << EndInstr(true);
        *output << "mflo $t0" << EndInstr(true);
        *output << "sw $t0, " << address << offsetReg << EndInstr(true);
    }
    else if(program->GetType() == "/="){
        context.assignState = 3;
        Compile(output, context, program->GetLeft());
        std::string id = context.identifier;
        int32_t address = LookupVariableAddress(context, id);
        std::string offsetReg = LookupOffsetRegister(context, id);

        context.assignState = 0;
        Compile(output, context, program->GetRight());
        *output << "lw $t1, " << address << offsetReg << EndInstr(true);
        *output << "div $t1, $t0" << EndInstr(true);
        *output << "mflo $t0" << EndInstr(true);
        *output << "sw $t0, " << address << offsetReg << EndInstr(true);
    }
    else if(program->GetType() == "%="){
        context.assignState = 3;
        Compile(output, context, program->GetLeft());
        std::string id = context.identifier;
        int32_t address = LookupVariableAddress(context, id);
        std::string offsetReg = LookupOffsetRegister(context, id);

        context.assignState = 0;
        Compile(output, context, program->GetRight());
        *output << "lw $t1, " << address << offsetReg << EndInstr(true);
        *output << "div $t1, $t0" << EndInstr(true);
        *output << "mfhi $t0" << EndInstr(true);
        *output << "sw $t0, " << address << offsetReg << EndInstr(true);
    }
    else if(program->GetType() == "<<="){
        context.assignState = 3;
        Compile(output, context, program->GetLeft());
        std::string id = context.identifier;
        int32_t address = LookupVariableAddress(context, id);
        std::string offsetReg = LookupOffsetRegister(context, id);

        context.assignState = 0;
        Compile(output, context, program->GetRight());
        *output << "lw $t1, " << address << offsetReg << EndInstr(true);
        *output << "sllv $t0, $t1, $t0" << EndInstr(true);
        *output << "sw $t0, " << address << offsetReg << EndInstr(true);
    }
    else if(program->GetType() == ">>="){
        context.assignState = 3;
        Compile(output, context, program->GetLeft());
        std::string id = context.identifier;
        int32_t address = LookupVariableAddress(context, id);
        std::string offsetReg = LookupOffsetRegister(context, id);

        context.assignState = 0;
        Compile(output, context, program->GetRight());
        *output << "lw $t1, " << address << offsetReg << EndInstr(true);
        // Using arithmetic shift
        // Can check type for logical shift?
        // Is this undefined behaviour?
        // Is there a srav instruction?
        *output << "srlv $t0, $t1, $t0" << EndInstr(true);
        *output << "sw $t0, " << address << offsetReg << EndInstr(true);
    }
    else if(program->GetType() == "&="){
        context.assignState = 3;
        Compile(output, context, program->GetLeft());
        std::string id = context.identifier;
        int32_t address = LookupVariableAddress(context, id);
        std::string offsetReg = LookupOffsetRegister(context, id);

        context.assignState = 0;
        Compile(output, context, program->GetRight());
        *output << "lw $t1, " << address << offsetReg << EndInstr(true);
        *output << "and $t0, $t1, $t0" << EndInstr(true);
        *output << "sw $t0, " << address << offsetReg << EndInstr(true);
    }
    else if(program->GetType() == "^="){
        context.assignState = 3;
        Compile(output, context, program->GetLeft());
        std::string id = context.identifier;
        int32_t address = LookupVariableAddress(context, id);
        std::string offsetReg = LookupOffsetRegister(context, id);

        context.assignState = 0;
        Compile(output, context, program->GetRight());
        *output << "lw $t1, " << address << offsetReg << EndInstr(true);
        *output << "xor $t0, $t1, $t0" << EndInstr(true);
        *output << "sw $t0, " << address << offsetReg << EndInstr(true);
    }
    else if(program->GetType() == "|="){
        context.assignState = 3;
        Compile(output, context, program->GetLeft());
        std::string id = context.identifier;
        int32_t address = LookupVariableAddress(context, id);
        std::string offsetReg = LookupOffsetRegister(context, id);

        context.assignState = 0;
        Compile(output, context, program->GetRight());
        *output << "lw $t1, " << address << offsetReg << EndInstr(true);
        *output << "or $t0, $t1, $t0" << EndInstr(true);
        *output << "sw $t0, " << address << offsetReg << EndInstr(true);
    }
    else if(program->GetType() == "conditional expression"){
        std::string false_label = NewLabel(context);
        std::string end_label = NewLabel(context);

        // Evaluate expression into $t0
        Compile(output, context, program->GetCondition());

        // If false ($t0 == 0) branch to false_label
        *output << "beq $t0, $0, " << false_label << EndInstr(true);
        // Otherwise execute true statement
        if(program->GetTruePath() != NULL){
            Compile(output, context, program->GetTruePath());
        }
        *output << "j " << end_label << EndInstr(true);

        *output << false_label << ":" << EndInstr(false);
        Compile(output, context, program->GetFalsePath());

        *output << end_label << ":" << EndInstr(false);
    }
    else if(program->GetType() == "||"){
        context.assignState = 0;
        std::string true_label = NewLabel(context);
        std::string end_label = NewLabel(context);

        // Output of left branch evaluated into $t0
        Compile(output, context, program->GetLeft());
        // Any !0 evaluates as true
        *output << "bne $t0, $0, " << true_label << EndInstr(true);

        // Assembly will jump out before this point if left branch is true
        // Right branch evaluated into $t0
        Compile(output, context, program->GetRight());
        *output << "bne $t0, $0, " << true_label << EndInstr(true);

        // Assembly will jump out before this point if either branch is true
        *output << "addiu $t0, $0, 0" << EndInstr(true);
        *output << "j " << end_label << EndInstr(true);
        *output << true_label << ":" << EndInstr(false);
        *output << "addiu $t0, $0, 1" << EndInstr(true);
        *output << end_label << ":" << EndInstr(false);
    }
    else if(program->GetType() == "&&"){
        context.assignState = 0;
        std::string false_label = NewLabel(context);
        std::string end_label = NewLabel(context);

        // Assembly now jumps to false_label if either branch is false
        Compile(output, context, program->GetLeft());
        *output << "beq $t0, $0, " << false_label << EndInstr(true);

        Compile(output, context, program->GetRight());
        *output << "beq $t0, $0, " << false_label << EndInstr(true);

        // Assembly will reach this point without jumping out if both branches are true
        *output << "addiu $t0, $0, 1" << EndInstr(true);
        *output << "j " << end_label << EndInstr(true);
        *output << false_label << ":" << EndInstr(false);
        *output << "addiu $t0, $0, 0" << EndInstr(true);
        *output << end_label << ":" << EndInstr(false);
    }
    else if(program->GetType() == "|"){
        context.assignState = 0;
        int32_t address = -4*context.infRegNum;
        context.infRegNum += 1;
        *output << "addiu $sp, $sp, -4" << EndInstr(true);
        
        Compile(output, context, program->GetLeft());
        *output << "sw $t0, " << address << "($fp)" << EndInstr(true);

        Compile(output, context, program->GetRight());
        *output << "lw $t1, " << address << "($fp)" << EndInstr(true);
        *output << "or $t0, $t0, $t1" << EndInstr(true);

        context.infRegNum -= 1;
        *output << "addiu $sp, $sp, 4" << EndInstr(true);
    }
    else if(program->GetType() == "^"){
        context.assignState = 0;
        int32_t address = -4*context.infRegNum;
        context.infRegNum += 1;
        *output << "addiu $sp, $sp, -4" << EndInstr(true);

        Compile(output, context, program->GetLeft());
        *output << "sw $t0, " << address << "($fp)" << EndInstr(true);

        Compile(output, context, program->GetRight());
        *output << "lw $t1, " << address << "($fp)" << EndInstr(true);
        *output << "xor $t0, $t0, $t1" << EndInstr(true);

        context.infRegNum -= 1;
        *output << "addiu $sp, $sp, 4" << EndInstr(true);
    }
    else if(program->GetType() == "&"){
        context.assignState = 0;
        int32_t address = -4*context.infRegNum;
        context.infRegNum += 1;
        *output << "addiu $sp, $sp, -4" << EndInstr(true);
        
        Compile(output,context, program->GetLeft());
        *output << "sw $t0, " << address << "($fp)" << EndInstr(true);

        Compile(output, context, program->GetRight());
        *output << "lw $t1, " << address << "($fp)" << EndInstr(true);
        *output << "and $t0, $t0, $t1" << EndInstr(true);

        context.infRegNum -= 1;
        *output << "addiu $sp, $sp, 4" << EndInstr(true);
    }
    else if(program->GetType() == "=="){
        // Set assign state in case of reading variables
        context.assignState = 0;
        // Request register from infinite pool to store result of left branch
        int32_t address = -4*context.infRegNum;
        context.infRegNum += 1;
        // Push register to stack
        *output << "addiu $sp, $sp, -4" << EndInstr(true);

        // Label to branch to if beq evaluates true
        std::string true_label = NewLabel(context);
        // Label to end of statement, for when beq evaluates false
        std::string end_label = NewLabel(context);

        // Evaluate left branch and store in reserved register
        Compile(output, context, program->GetLeft());
        *output << "sw $t0, " << address << "($fp)" << EndInstr(true);

        // Evaluate right branch, result ends up in $t0
        Compile(output, context, program->GetRight());
        // Retrieve result of left branch from register, store in $t1
        *output << "lw $t1, " << address << "($fp)" << EndInstr(true);

        // Simulate if else statement to write logical result into $t0
        *output << "beq $t0, $t1, " << true_label << EndInstr(true);
        *output << "addiu $t0, $0, 0" << EndInstr(true);
        *output << "j " << end_label << EndInstr(true);
        *output << true_label << ":" << EndInstr(false);
        *output << "addiu $t0, $0, 1" << EndInstr(true);
        *output << end_label << ":" << EndInstr(false);

        // Release register back to infinite pool
        context.infRegNum -= 1;
        // Released register popped from stack
        *output << "addiu $sp, $sp, 4" << EndInstr(true);
    }
    else if(program->GetType() == "!="){
        context.assignState = 0;
        int32_t address = -4*context.infRegNum;
        context.infRegNum += 1;
        *output << "addiu $sp, $sp, -4" << EndInstr(true);
        std::string true_label = NewLabel(context);
        std::string end_label = NewLabel(context);

        Compile(output, context, program->GetLeft());
        *output << "sw $t0, " << address << "($fp)" << EndInstr(true);

        Compile(output, context, program->GetRight());
        *output << "lw $t1, " << address << "($fp)" << EndInstr(true);

        *output << "bne $t0, $t1, " << true_label << EndInstr(true);
        *output << "addiu $t0, $0, 0" << EndInstr(true);
        *output << "j " << end_label << EndInstr(true);
        *output << true_label << ":" << EndInstr(false);
        *output << "addiu $t0, $0, 1" << EndInstr(true);
        *output << end_label << ":" << EndInstr(false);

        context.infRegNum -= 1;
        *output << "addiu $sp, $sp, 4" << EndInstr(true);
    }
    else if(program->GetType() == ">"){
        context. assignState = 0;
        int32_t address = -4*context.infRegNum;
        context.infRegNum += 1;
        *output << "addiu $sp, $sp, -4" << EndInstr(true);
        std::string true_label = NewLabel(context);
        std::string end_label = NewLabel(context);

        Compile(output, context, program->GetLeft());
        *output << "sw $t0, " << address << "($fp)" << EndInstr(true);

        Compile(output, context, program->GetRight());
        *output << "lw $t1, " << address << "($fp)" << EndInstr(true);

        *output << "sub $t0, $t1, $t0" << EndInstr(true);
        *output << "bgtz $t0, " << true_label << EndInstr(true);
        *output << "addiu $t0, $0, 0" << EndInstr(true);
        *output << "j " << end_label << EndInstr(true);
        *output << true_label << ":" << EndInstr(false);
        *output << "addiu $t0, $0, 1" << EndInstr(true);
        *output << end_label << ":" << EndInstr(false);

        context.infRegNum -= 1;
        *output << "addiu $sp, $sp, 4" << EndInstr(true);
    }
    else if(program->GetType() == "<"){
        context. assignState = 0;
        int32_t address = -4*context.infRegNum;
        context.infRegNum += 1;
        *output << "addiu $sp, $sp, -4" << EndInstr(true);
        std::string true_label = NewLabel(context);
        std::string end_label = NewLabel(context);

        Compile(output, context, program->GetLeft());
        *output << "sw $t0, " << address << "($fp)" << EndInstr(true);

        Compile(output, context, program->GetRight());
        *output << "lw $t1, " << address << "($fp)" << EndInstr(true);

        *output << "sub $t0, $t1, $t0" << EndInstr(true);
        *output << "bltz $t0, " << true_label << EndInstr(true);
        *output << "addiu $t0, $0, 0" << EndInstr(true);
        *output << "j " << end_label << EndInstr(true);
        *output << true_label << ":" << EndInstr(false);
        *output << "addiu $t0, $0, 1" << EndInstr(true);
        *output << end_label << ":" << EndInstr(false);

        context.infRegNum -= 1;
        *output << "addiu $sp, $sp, 4" << EndInstr(true);
    }
    else if(program->GetType() == ">="){
        context.assignState = 0;
        int32_t address = -4*context.infRegNum;
        context.infRegNum += 1;
        *output << "addiu $sp, $sp, -4" << EndInstr(true);
        std::string true_label = NewLabel(context);
        std::string end_label = NewLabel(context);

        Compile(output, context, program->GetLeft());
        *output << "sw $t0, " << address << "($fp)" << EndInstr(true);

        Compile(output, context, program->GetRight());
        *output << "lw $t1, " << address << "($fp)" << EndInstr(true);

        *output << "sub $t0, $t1, $t0" << EndInstr(true);
        *output << "bgez $t0, " << true_label << EndInstr(true);
        *output << "addiu $t0, $0, 0" << EndInstr(true);
        *output << "j " << end_label << EndInstr(true);
        *output << true_label << ":" << EndInstr(false);
        *output << "addiu $t0, $0, 1" << EndInstr(true);
        *output << end_label << ":" << EndInstr(false);

        context.infRegNum -= 1;
        *output << "addiu $sp, $sp, 4" << EndInstr(true);
    }
    else if(program->GetType() == "<="){
        context. assignState = 0;
        int32_t address = -4*context.infRegNum;
        context.infRegNum += 1;
        *output << "addiu $sp, $sp, -4" << EndInstr(true);
        std::string true_label = NewLabel(context);
        std::string end_label = NewLabel(context);

        Compile(output, context, program->GetLeft());
        *output << "sw $t0, " << address << "($fp)" << EndInstr(true);

        Compile(output, context, program->GetRight());
        *output << "lw $t1, " << address << "($fp)" << EndInstr(true);

        *output << "sub $t0, $t1, $t0" << EndInstr(true);
        *output << "blez $t0, " << true_label << EndInstr(true);
        *output << "addiu $t0, $0, 0" << EndInstr(true);
        *output << "j " << end_label << EndInstr(true);
        *output << true_label << ":" << EndInstr(false);
        *output << "addiu $t0, $0, 1" << EndInstr(true);
        *output << end_label << ":" << EndInstr(false);

        context.infRegNum -= 1;
        *output << "addiu $sp, $sp, 4" << EndInstr(true);
    }
    else if(program->GetType() == "<<"){
        context.assignState = 0;
        int32_t address = -4*context.infRegNum;
        context.infRegNum += 1;
        *output << "addiu $sp, $sp, -4" << EndInstr(true);

        Compile(output, context, program->GetLeft());
        *output << "sw $t0, " << address << "($fp)" << EndInstr(true);

        Compile(output, context, program->GetRight());
        *output << "lw $t1, " << address << "($fp)" << EndInstr(true);
        *output << "sllv $t0, $t1, $t0" << EndInstr(true);

        context.infRegNum -= 1;
        *output << "addiu $sp, $sp, 4" << EndInstr(true);
    }
    else if(program->GetType() == ">>"){
        context.assignState = 0;
        int32_t address = -4*context.infRegNum;
        context.infRegNum += 1;
        *output << "addiu $sp, $sp, -4" << EndInstr(true);

        Compile(output, context, program->GetLeft());
        *output << "sw $t0, " << address << "($fp)" << EndInstr(true);

        Compile(output, context, program->GetRight());
        *output << "lw $t1, " << address << "($fp)" << EndInstr(true);
        *output << "srlv $t0, $t1, $t0" << EndInstr(true);

        context.infRegNum -= 1;
        *output << "addiu $sp, $sp, 4" << EndInstr(true);
    }
    else if(program->GetType() == "+"){
        // Set assignState to prepare for reading variables
        context.assignState = 0;
        // Request register to store branch results
        int32_t address = -4*context.infRegNum;
        // Registers from infinite pool are pushed into stack
        context.infRegNum += 1;
        *output << "addiu $sp, $sp, -4" << EndInstr(true);
        // Address of register (relative to $fp) reserved as positive to stack pointer

        // Evaluate left branch
        Compile(output, context, program->GetLeft());
        // Result of left branch is now in $t0

        // Store left branch result in register
        *output << "sw $t0, " << address << "($fp)" << EndInstr(true);
        
        // Evaluate right branch
        Compile(output, context, program->GetRight());
        // Result of right branch is now in $t0

        *output << "lw $t1, " << address << "($fp)" << EndInstr(true);
        *output << "add $t0, $t0, $t1" << EndInstr(true);
        // Leaves result in $t0

        // Release register back to infinite pool 
        context.infRegNum -= 1;
        // Register location popped from stack
        *output << "addiu $sp, $sp, 4" << EndInstr(true);
    }
    else if(program->GetType() == "-"){
        context.assignState = 0;
        int32_t address = -4*context.infRegNum;
        context.infRegNum += 1;
        *output << "addiu $sp, $sp, -4" << EndInstr(true);

        Compile(output, context, program->GetLeft());
        *output << "sw $t0, " << address << "($fp)" << EndInstr(true);

        Compile(output, context, program->GetRight());
        *output << "lw $t1, " << address << "($fp)" << EndInstr(true);
        *output << "sub $t0, $t1, $t0" << EndInstr(true);

        context.infRegNum -= 1;
        *output << "addiu $sp, $sp, 4" << EndInstr(true);
    }
    else if(program->GetType() == "*"){
        context.assignState = 0;
        int32_t address = -4*context.infRegNum;
        context.infRegNum += 1;
        *output << "addiu $sp, $sp, -4" << EndInstr(true);
        
        Compile(output, context, program->GetLeft());
        *output << "sw $t0, " << address << "($fp)" << EndInstr(true);

        Compile(output, context, program->GetRight());
        *output << "lw $t1, " << address << "($fp)" << EndInstr(true);
        *output << "mult $t0, $t1" << EndInstr(true);
        *output << "mflo $t0" << EndInstr(true);
        
        context.infRegNum -= 1;
        *output << "addiu $sp, $sp, 4" << EndInstr(true);
    }
    else if(program->GetType() == "/"){
        context.assignState = 0;
        int32_t address = -4*context.infRegNum;
        context.infRegNum += 1;
        *output << "addiu $sp, $sp, -4" << EndInstr(true);

        Compile(output, context, program->GetLeft());
        *output << "sw $t0, " << address << "($fp)" << EndInstr(true);

        Compile(output, context, program->GetRight());
        *output << "lw $t1, " << address << "($fp)" << EndInstr(true);
        *output << "div $t1, $t0" << EndInstr(true);
        *output << "mflo $t0" << EndInstr(true);
        
        context.infRegNum -= 1;
        *output << "addiu $sp, $sp, 4" << EndInstr(true);
    }
    else if(program->GetType() == "%"){
        context.assignState = 0;
        int32_t address = -4*context.infRegNum;
        context.infRegNum += 1;
        *output << "addiu $sp, $sp, -4" << EndInstr(true);

        Compile(output, context, program->GetLeft());
        *output << "sw $t0, " << address << "($fp)" << EndInstr(true);

        Compile(output, context, program->GetRight());
        *output << "lw $t1, " << address << "($fp)" << EndInstr(true);
        *output << "div $t1, $t0" << EndInstr(true);
        *output << "mfhi $t0" << EndInstr(true);
        
        context.infRegNum -= 1;
        *output << "addiu $sp, $sp, 4" << EndInstr(true);
    }
    else if(program->GetType() == "cast expression"){ NoImplementError(program); }
    else if(program->GetType() == "++_"){
        context.assignState = 0;
        Compile(output, context, program->GetNext());
        std::string id = context.identifier;
        int32_t address = LookupVariableAddress(context, id);

        // Increment value in $t0, and also store it into variable location
        *output << "addi $t0, $t0, 1" << EndInstr(true);
        *output << "sw $t0, " << address << "($fp)" << EndInstr(true);
    }
    else if(program->GetType() == "--_"){
        context.assignState = 0;
        Compile(output, context, program->GetNext());
        std::string id = context.identifier;
        int32_t address = LookupVariableAddress(context, id); 

        // No sub immediate: hence 1 is loaded into $t1
        *output << "addiu $t1, $0, 1" << EndInstr(true);
        *output << "sub $t0, $t0, $t1" << EndInstr(true);
        *output << "sw $t0, " << address << "($fp)" << EndInstr(true);
    }
    else if(program->GetType() == "+_"){
        // No changes needed here
        Compile(output, context, program->GetNext());
    }
    else if(program->GetType() == "-_"){
        Compile(output, context, program->GetNext());
        // Result of operations lower down the branch are in $t0
        // Load -1 into $t1
        *output << "lui $t1, 0xFFFF" << EndInstr(true);
        *output << "addi $t1, $t1, 0xFFFF" << EndInstr(true);
        // Multiply $t0 by -1
        *output << "mult $t0, $t1" << EndInstr(true);
        *output << "mflo $t0" << EndInstr(true);
        // Result is placed in $t0
    }
    else if(program->GetType() == "&_"){ NoImplementError(program); }
    else if(program->GetType() == "*_"){ NoImplementError(program); }
    else if(program->GetType() == "~_"){
        Compile(output, context, program->GetNext());
        // Invert all bits using XOR with -1
        *output << "lui $t1, 0xFFFF" << EndInstr(true);
        *output << "addi $t1, $t1, 0xFFFF" << EndInstr(true);
        *output << "xor $t0, $t0, $t1" << EndInstr(true);
    }
    else if(program->GetType() == "!"){
        std::string true_label = NewLabel(context);
        std::string end_label = NewLabel(context);

        Compile(output, context, program->GetNext());
        // Anything other than zero is interpreted as true
        *output << "beq $t0, $0, " << true_label << EndInstr(true);
        *output << "addiu $t0, $0, 0" << EndInstr(true);
        *output << "j " << end_label << EndInstr(true);
        *output << true_label << ":" << EndInstr(false);
        *output << "addiu $t0, $0, 1" << EndInstr(true);
        *output << end_label << ":" << EndInstr(false);
    }
    else if(program->GetType() == "sizeof"){
        std::string specifier;
        context.specifier = std::string();
        SearchSpecifiers(context, program->GetNext());
        if(!context.specifier.empty()){
            specifier = context.specifier;
            if(specifier == "bool"){
                *output << "addiu $t0, $0, 1" << EndInstr(true);
            }
            else if(specifier == "char"){
                *output << "addiu $t0, $0, 1" << EndInstr(true);
            }
            else if(specifier == "float"){
                *output << "addiu $t0, $0, 4" << EndInstr(true);
            }
            else if(specifier == "int"){
                *output << "addiu $t0, $0, 4" << EndInstr(true);
            }
            else if(specifier == "double"){
                *output << "addiu $t0, $0, 8" << EndInstr(true);
            }
            else if(specifier == "short"){
                *output << "addiu $t0, $0, 2" << EndInstr(true);
            }
            else if(specifier == "long"){
                *output << "addiu $t0, $0, 4" << EndInstr(true);
            }
            else{
                *output << "addiu $t0, $0, 1" << EndInstr(true);
            }
        }
        else{
            std::vector<int> nums;
            GetAllNumbers(nums, program->GetNext());
            int total = 0;
            for(int i = 0; i < nums.size(); i++){
                int power = 0;
                while(pow(2,power)-1 < nums[i]){
                    power += 1;
                }
                total += power;
            }
            int upper_16 = (total & 0xFFFF0000);
            int lower_16 = (total & 0xFFFF);
            *output << "lui $t0, " << upper_16 << EndInstr(true);
            *output << "addi $t0, $t0, " << lower_16 << EndInstr(true);
        }
    }
    else if(program->GetType() == "array element call"){ NoImplementError(program); }
    else if(program->GetType() == "direct function call"){
        // Get identifier
        context.assignState = 4;
        Compile(output, context, program->GetIdentifier());
        std::string id = context.identifier;

        // Place start address of arguments in $t4
        context.argSum.push_back(0);
        int init_a0_pos = GetArgSum(context);
        // Get arguments
        context.assignState = 0;
        if(program->GetArguments() != NULL){
            // Start at argument number 0
            context.argCount.push_back(0);
            // Load arguments into stack in corresponding positions
            Compile(output, context, program->GetArguments());
            // Last argument is now in $t0
            // Get address offset from context.argSum with GetArgSum(context)
            int32_t address = GetArgSum(context);
            *output << "sw $t0, " << address << "($fp)" << EndInstr(true);
            context.argCount[context.argCount.size() - 1] += 1;
        
            // Store address of beginning of arguments in $t4
            *output << "addiu $t4, $fp, " << init_a0_pos << EndInstr(true);
            // $t3 holds beginning of argument variables in next frame
            *output << "addiu $t3, $sp, 0" << EndInstr(true);
            // Load argument values into next frame positions
            for(int i = 0; i < context.argCount.back(); i++){
                *output << "lw $t0, " << 8*i << "($t4)" << EndInstr(true);
                if(i < 4){
                    // First four arguments also go in $a0 - $a3
                    *output << "addiu $a" << i << ", $t0, 0" << EndInstr(true);
                }
                else{
                    // Otherwise store on stack
                    *output << "sw $t0, " << -8*(i+1) << "($t3)" << EndInstr(true);
                }
            }
            context.argCount.pop_back();
        }
        context.argSum.pop_back();

        // Branch to function code
        *output << "jal " << id << EndInstr(true);
        // Move result to $t0
        *output << "add $t0, $v0, $0" << EndInstr(true);
    }
    else if(program->GetType() == "_++"){
        context.assignState = 0;
        Compile(output, context, program->GetIdentifier());
        std::string id = context.identifier;
        int32_t address = LookupVariableAddress(context, id);

        // Old value is left in $t0
        // Increment takes place in $t1, and is then stored on stack
        *output << "addi $t1, $t0, 1" << EndInstr(true);
        *output << "sw $t1, " << address << "($fp)" << EndInstr(true);
        // Non-incremented value is still ready for use in $t0
    }
    else if(program->GetType() == "_--"){
        context.assignState = 0;
        Compile(output, context, program->GetIdentifier());
        std::string id = context.identifier;
        int32_t address = LookupVariableAddress(context, id);

        *output << "addiu $t1, $0, 1" << EndInstr(true);
        *output << "sub $t1, $t0, $t1" << EndInstr(true);
        *output << "sw $t1, " << address << "($fp)" << EndInstr(true);
    }
    else if(program->GetType() == "argument expression"){
        // Evaluate left branch expression into $t0
        Compile(output, context, program->GetLeft());
        // Store left branch in proper location
        // Location will correspond to variable location in next stack frame
        int32_t address = GetArgSum(context);
        *output << "sw $t0, " << address << "($fp)" << EndInstr(true);
        context.argSum[context.argSum.size()-1] += 8;
        context.argCount[context.argCount.size() - 1] += 1;

        // Right branch expression is passed back up to direct function call node in $t0
        Compile(output, context, program->GetRight());
    }
    else if(program->GetType() == "primary expression"){
        Compile(output, context, program->GetNext());
    }
    else if(program->GetType() == "enumerator"){
        std::string enum_id = context.identifier;
        std::string var_id = program->GetId();
        auto itr = context.enumList.find(enum_id);
        int value = itr->second.counter;
        itr->second.counter += 1;
        if(program->GetNext() == NULL){
            // Evaluate constant expression ... Somehow...
        }
        itr->second.bindings.insert(std::make_pair(var_id,value));
    }
    else if(program->GetType() == "enumerator list"){
        std::string id = context.identifier;
        Compile(output, context, program->GetLeft());
        context.identifier = id;
        Compile(output, context, program->GetRight());
        context.identifier = id;
    }
    else if(program->GetType() == "enumerator specifier"){
        if(!program->GetId().empty()){
            std::string id = program->GetId();
            context.identifier = id;
            EnumContext properties;
            context.enumList.insert(std::make_pair(id, properties));
            if(program->GetNext() != NULL){
                Compile(output, context, program->GetNext());
            }
        }
    }
    else if(program->GetType() == "type name"){ NoImplementError(program); }
    else if(program->GetType() == "specifier qualifier list"){ NoImplementError(program); }
    else if(program->GetType() == "abstract declarator"){ NoImplementError(program); }
    else if(program->GetType() == "bracketed abstract declarator"){ NoImplementError(program); }
    else if(program->GetType() == "direct abstract declarator"){ NoImplementError(program); }
    else if(program->GetType() == "square abstract parameter"){ NoImplementError(program); }
    else if(program->GetType() == "round abstract parameter"){ NoImplementError(program); }
    else if(program->GetType() == "variable"){
        // Take variable ID
        std::string id = program->GetId();
        context.identifier = id;
        if(context.assignState == 0){ // Reading from existing variable
            int32_t address = LookupVariableAddress(context, id);
            std::string offsetReg = LookupOffsetRegister(context, id);
            *output << "lw $t0, " << address << offsetReg << EndInstr(true);
        }
        else if(context.assignState == 1){ // Declaring new variable
            if(context.bindings.count(id) == 0){ // Not shadowing
                int32_t address;
                if(context.scope == 0){ // Global variable
                    // Allocate space at $gp for variable value
                    context.globalCount += 1;
                    // $gp points to middle of data segment, Offset can be positive or negative
                    // Chose positive to avoid triggering error in LookupVariableAddress
                    address = 8*context.globalCount;
                }
                else{ // Local variable
                    // Allocate space on the stack for variable value
                    context.varCount[context.frameNum] += 1;
                    // Address of stack location taken as offset from stack pointer
                    address = context.frameSizes[context.frameNum] - 8*context.varCount[context.frameNum];
                }
                // ID key is paired with address and stored in bindings
                VariableContext properties;
                properties.address.push_back(address);
                properties.scope.push_back(context.scope);
                properties.type.push_back(context.specifier);
                context.bindings.insert(std::make_pair(id,properties));
                if(!InTotalVars(context, id)){
                    context.totalVars.push_back(id);
                }
            }
            else{ // Shadowing
                auto itr = context.bindings.find(id);
                if(itr->second.scope.back() == context.scope){
                    std::cerr << "Error: Variable \"" << id << "\" has already been ";
                    std::cerr << "declared in this scope" << EndInstr(false);
                    exit(1);
                }
                itr->second.scope.push_back(context.scope);
                itr->second.type.push_back(context.specifier);
                context.varCount[context.frameNum] += 1;
                // Address of stack location taken as offset from stack pointer
                int32_t address = context.frameSizes[context.frameNum] - 8*context.varCount[context.frameNum];
                itr->second.address.push_back(address);
            }
            context.assignState = 0;
        }
        else if(context.assignState == 2){ // Declaring new function
            if(context.functions.count(id) > 0){
                std::cerr << "Warning: Function overloading detected for function \"";
                std::cerr << id << "\" of type \"" << context.specifier << "\"" << EndInstr(false);
            }
            FunctionContext properties;
            properties.scope = context.scope;
            properties.type = context.specifier;
            context.functions.insert(std::make_pair(id,properties));
            context.totalFuncts.push_back(id);
            // Implement function cleaning with regards to scope?
        }
        else if(context.assignState == 3){ // Writing to existing variable
            // Return of variable id in context is done already
            if(context.bindings.count(id) == 0){
                std::cerr << "Error: Assignment to undeclared variable \"";
                std::cerr << id << "\"" << EndInstr(false);
            }
        }
        else if(context.assignState == 4){ // Get identifier for function call
            // Return of function identifier in context is done already
            if(context.functions.count(id) == 0){
                if(!InForwardDecs(context, id)){
                    if(!InAllFunctions(context, id)){
                        std::cerr << "Error: Call for undeclared function \"";
                        std::cerr << id << "\"" << EndInstr(false);
                    }
                    else{
                        std::cerr << "Warning: Call to function \"";
                        std::cerr << id << "\" prior to definition ";
                        std::cerr << "without forward declaration" << EndInstr(false);
                    }
                }
            }
        }
        else if(context.assignState == 5){ // Forward declaration
            if(context.functions.count(id) == 0){
                context.forwardDecs.push_back(id);
            }
        }
        else if(context.assignState == 6){ // Sized array declaration
            // Check that there is no conflicting identifier
            // Identifier is already returned in context
        }
    }
    else if(program->GetType() == "number"){
        // Load immediate into $t0
        int val = program->GetValue();
        int upper_16 = (val & 0xFFFF0000);
        int lower_16 = (val & 0xFFFF);
        *output << "lui $t0, " << upper_16 << EndInstr(true);
        *output << "addi $t0, $t0, " << lower_16 << EndInstr(true);
    }
    else if(program->GetType() == "string literal"){ NoImplementError(program); }
    else{
        throw std::runtime_error("Unknown ast type: \"" + program->GetType() + "\"\n");
    }
}

std::vector<std::string> CleanBindings(InterpretContext &context){
    std::vector<std::string> remainingVars;
    for(int i = 0; i < context.totalVars.size(); i++){
        std::string id = context.totalVars[i];
        auto itr = context.bindings.find(id);
        if(itr->second.scope.back() > context.scope){
            itr->second.scope.pop_back();
            itr->second.address.pop_back();
            itr->second.type.pop_back();
        }

        // Remove from list if no more variables in that scope
        if(itr->second.scope.size() == 0){
            context.bindings.erase(id);
        }
        else{
            remainingVars.push_back(id);
        }
    }
    return remainingVars;
}

int32_t LookupVariableAddress(InterpretContext &context, std::string id){
    if(context.bindings.count(id) == 0){
        std::cerr << "Error: Could not find address for variable \"" << id << "\" on stack\n";
        std::cerr << "Current frame (" << context.frameNum << ") has size ";
        std::cerr << context.frameSizes[context.frameNum] << " with ";
        std::cerr << context.totalVars.size() << " total variables recognised" << std::endl;
        exit(1);
    }
    int32_t address = context.bindings.find(id)->second.address.back();
    if(address < 0){
        std::cerr << "Error: Address of variable \"" << id;
        std::cerr << "\" is outside of stack frame" << std::endl;
        std::cerr << "Address value: " << address << std::endl;
        std::cerr << "Current frame (" << context.frameNum << ") has size ";
        std::cerr << context.frameSizes[context.frameNum] << " with ";
        std::cerr << context.totalVars.size() << " total variables recognised" << std::endl;
        exit(1);
    }
    return address;
}

std::string LookupOffsetRegister(InterpretContext &context, std::string id){
    if(context.bindings.count(id) == 0){
        std::cerr << "Error: Could not find address for variable \"" << id << "\" on stack\n";
        std::cerr << "Current frame (" << context.frameNum << ") has size ";
        std::cerr << context.frameSizes[context.frameNum] << " with ";
        std::cerr << context.totalVars.size() << " total variables recognised" << std::endl;
        exit(1);
    }

    int32_t scope = context.bindings.find(id)->second.scope.back();
    if(scope < 0){
        std::cerr << "Error: Variable \"" << id << "\" has negative scope" << std::endl;
        exit(1);
    }
    
    if(scope == 0){ // Global variable
        return "($gp)";
    }
    else{ // Local variable
        return "($fp)";
    }
}

int EstimateSpace(NodePtr program){
    if(program == NULL){
        return 0;
    }
    int space = 0;
    if((program->GetType() == "variable") || (program->GetType() == "number")){
        space += 8;
    }
    else{
        space += EstimateSpace(program->GetLeft());
        space += EstimateSpace(program->GetRight());
        space += EstimateSpace(program->GetNext());
        space += EstimateSpace(program->GetPointer());
        space += EstimateSpace(program->GetIdentifier());
        space += EstimateSpace(program->GetArguments());
        space += EstimateSpace(program->GetCondition());
        space += EstimateSpace(program->GetConditionOne());
        space += EstimateSpace(program->GetConditionTwo());
        space += EstimateSpace(program->GetConditionThree());
        space += EstimateSpace(program->GetTruePath());
        space += EstimateSpace(program->GetFalsePath());
        space += EstimateSpace(program->GetReturnValue());
        space += EstimateSpace(program->GetIndex());
        space += EstimateSpace(program->GetSpecifiers());
        space += EstimateSpace(program->GetQualifiers());
        space += EstimateSpace(program->GetStatements());
        space += EstimateSpace(program->GetDeclarator());
    }
    return space;
}

std::string NewLabel(InterpretContext &context){
    int num = context.labelCount;
    context.labelCount += 1;
    return "label_" + std::to_string(num);
}

int32_t GetArgSum(InterpretContext &context){
    int size = context.argSum.size();
    int32_t sum = 0;
    for(int i = 0; i < size; i++){
        sum += context.argSum[i];
    }
    return sum;
}

bool InForwardDecs(InterpretContext &context, std::string id){
    for(int i = 0; i < context.forwardDecs.size(); i++){
        if(context.forwardDecs[i] == id){
            return true;
        }
    }
    return false;
}

bool InAllFunctions(InterpretContext &context, std::string id){
    for(int i = 0; i < context.allFuncts.size(); i++){
        if(context.allFuncts[i] == id){
            return true;
        }
    }
    return false;
}

bool InAllVars(InterpretContext &context, std::string id){
    for(int i = 0; i < context.allVars.size(); i++){
        if(context.allVars[i] == id){
            return true;
        }
    }
    return false;
}

std::vector<std::string> CountAllFunctions(NodePtr program){
    if(program->GetType() == "program"){
        std::vector<std::string> left = CountAllFunctions(program->GetLeft());
        std::vector<std::string> right = CountAllFunctions(program->GetRight());
        std::vector<std::string> total;
        total.reserve(left.size() + right.size());
        total.insert(total.end(), left.begin(), left.end());
        total.insert(total.end(), right.begin(), right.end());
        return total;
    }
    else if(program->GetType() == "function declaration"){
        return CountAllFunctions(program->GetIdentifier());
    }
    else if(program->GetType() == "declaration identifier"){
        return CountAllFunctions(program->GetIdentifier());
    }
    else if(program->GetType() == "direct declaration"){
        return CountAllFunctions(program->GetLeft());
    }
    else if(program->GetType() == "variable"){
        std::vector<std::string> id = {program->GetId()};
        return id;
    }
    else{
        return {};
    }
}

void CountAllVars(std::vector<std::string>& list, NodePtr program){
    if(program != NULL){
        if(program->GetType() == "variable"){
            list.push_back(program->GetId());
        }
        else{
            CountAllVars(list, program->GetLeft());
            CountAllVars(list, program->GetRight());
            CountAllVars(list, program->GetNext());
            CountAllVars(list, program->GetPointer());
            CountAllVars(list, program->GetIdentifier());
            CountAllVars(list, program->GetArguments());
            CountAllVars(list, program->GetCondition());
            CountAllVars(list, program->GetConditionOne());
            CountAllVars(list, program->GetConditionTwo());
            CountAllVars(list, program->GetConditionThree());
            CountAllVars(list, program->GetTruePath());
            CountAllVars(list, program->GetFalsePath());
            CountAllVars(list, program->GetReturnValue());
            CountAllVars(list, program->GetIndex());
            CountAllVars(list, program->GetSpecifiers());
            CountAllVars(list, program->GetQualifiers());
            CountAllVars(list, program->GetStatements());
            CountAllVars(list, program->GetDeclarator());
        }
    }
}

void GetAllNumbers(std::vector<int>& list, NodePtr program){
    if(program != NULL){
        if(program->GetType() == "number"){
            list.push_back(program->GetValue());
        }
        else{
            GetAllNumbers(list, program->GetLeft());
            GetAllNumbers(list, program->GetRight());
            GetAllNumbers(list, program->GetNext());
            GetAllNumbers(list, program->GetPointer());
            GetAllNumbers(list, program->GetIdentifier());
            GetAllNumbers(list, program->GetArguments());
            GetAllNumbers(list, program->GetCondition());
            GetAllNumbers(list, program->GetConditionOne());
            GetAllNumbers(list, program->GetConditionTwo());
            GetAllNumbers(list, program->GetConditionThree());
            GetAllNumbers(list, program->GetTruePath());
            GetAllNumbers(list, program->GetFalsePath());
            GetAllNumbers(list, program->GetReturnValue());
            GetAllNumbers(list, program->GetIndex());
            GetAllNumbers(list, program->GetSpecifiers());
            GetAllNumbers(list, program->GetQualifiers());
            GetAllNumbers(list, program->GetStatements());
            GetAllNumbers(list, program->GetDeclarator());
        }
    }
}

void SearchSpecifiers(InterpretContext &context, NodePtr program){
    if(program != NULL){
        if(program->GetType() == "variable"){
            std::string id = program->GetId();
            if(context.bindings.count(id) > 0){
                context.specifier = context.bindings.find(id)->second.type.back();
            }
        }
        else if(program->GetType() == "void"){
            context.specifier = "void";
        }
        else if(program->GetType() == "bool"){
            context.specifier = "bool";
        }
        else if(program->GetType() == "int"){
            context.specifier = "int";
        }
        else if(program->GetType() == "char"){
            context.specifier = "char";
        }
        else if(program->GetType() == "float"){
            context.specifier = "float";
        }
        else if(program->GetType() == "double"){
            context.specifier = "double";
        }
        else if(program->GetType() == "short"){
            context.specifier = "short";
        }
        else if(program->GetType() == "long"){
            context.specifier = "long";
        }
        else{
            SearchSpecifiers(context, program->GetLeft());
            SearchSpecifiers(context, program->GetRight());
            SearchSpecifiers(context, program->GetNext());
            SearchSpecifiers(context, program->GetPointer());
            SearchSpecifiers(context, program->GetIdentifier());
            SearchSpecifiers(context, program->GetArguments());
            SearchSpecifiers(context, program->GetCondition());
            SearchSpecifiers(context, program->GetConditionOne());
            SearchSpecifiers(context, program->GetConditionTwo());
            SearchSpecifiers(context, program->GetConditionThree());
            SearchSpecifiers(context, program->GetTruePath());
            SearchSpecifiers(context, program->GetFalsePath());
            SearchSpecifiers(context, program->GetReturnValue());
            SearchSpecifiers(context, program->GetIndex());
            SearchSpecifiers(context, program->GetSpecifiers());
            SearchSpecifiers(context, program->GetQualifiers());
            SearchSpecifiers(context, program->GetStatements());
            SearchSpecifiers(context, program->GetDeclarator());
        }
    }
}

int CountGlobalVars(NodePtr program){
    // To get number of global variables
    // Count number of InitDeclarationNodes in global scope
    if(program == NULL){
        return 0;
    }
    else{
        int total = 0;
        if(program->GetType() == "program"){
            total += CountGlobalVars(program->GetLeft());
            total += CountGlobalVars(program->GetRight());
        }
        else if(program->GetType() == "variable declaration"){
            total += CountGlobalVars(program->GetRight());
        }
        else if(program->GetType() == "initial declaration list"){
            total += CountGlobalVars(program->GetLeft());
            total += CountGlobalVars(program->GetRight());
        }
        else if(program->GetType() == "init declaration"){
            total += 1;
        }
        return total;
    }
}

std::string EndInstr(bool No_op){
    // End line and pad with five no-ops
    std::string str = "\n";
    if(No_op){
        str += "sll $0, $0, 0 \n";
        str += "sll $0, $0, 0 \n";
        str += "sll $0, $0, 0 \n";
        str += "sll $0, $0, 0 \n";
        str += "sll $0, $0, 0 \n";
    }
    return str;
}

void NoImplementError(NodePtr program){
    throw std::runtime_error("Node not implemented yet: \"" + program->GetType() + "\"\n");
}