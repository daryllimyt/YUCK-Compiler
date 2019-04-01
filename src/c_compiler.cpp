#include "../include/ast.hpp"

bool DeleteTree(NodePtr program);
bool DeleteBranch(NodePtr branch);

int main(int argc, char* argv[]){
    if (argc >= 3){

        std::string arg_id = argv[1];
        
        if( arg_id == "-S" ) {      //Compilation Function

            {
                std::ifstream in_program;
                std::string in_name(argv[2]);
                in_program.open(in_name);
                if(!in_program.is_open()){
                    std::cerr << "Error: Input file \"" << in_name << "\" was not found" << std::endl;
                    exit(1);
                }
                else{
                    in_program.close();
                }
            }

            const Tree *ast_compiler = parseAST(argv[2],argv[4]);
            std::ostream *output;
            std::ofstream file;

            if( argc > 3 ){
                arg_id = argv[3];
                if( arg_id == "-o" ) {
                    std::string filename = argv[4];
                    {
                        std::ifstream test_out;
                        test_out.open(filename);
                        if(!test_out.is_open()){
                            std::cerr << "Warning: Output file \"" << filename << "\" was not found\n";
                            std::cerr << "Creating new file \"" << filename << "\"" << std::endl;
                        }
                        else{
                            test_out.close();
                        }
                    }
                    output = &file;
                    file.open(filename);
                        
                    
                    char last_letter = filename[filename.size()-1];
                    if( (last_letter != 's') && (last_letter != 'm') && (last_letter != 'o') ){
                        std::cerr << "Warning: Output file is not of type .s or .asm or .o" << std::endl;
                    }
                }
                else{
                    std::cerr << "Warning: Unidentified flag \"" << arg_id << "\"" << std::endl;
                    std::cerr << "Redirecting translator output to command line\n" << std::endl;
                    output = &std::cout;
                }
            }
            else{
                std::cerr << "Warning: No output file specified" << std::endl;
                std::cerr << "Redirecting translator output to command line" << std::endl;
                std::cerr << std::endl;
                output = &std::cout;
            }

            // Create context for code generation
            InterpretContext context;
            
            Compile(output, context, ast_compiler);

            if(context.functions.count("main") == 0){
                std::cerr << "Warning: No main function detected!" << std::endl;
            }

            if( output != &std::cout ){
                file.close();
            }
            else{
                std::cerr << std::endl;
            }

            std::cerr << "Cleaning AST structure..." << std::endl;
            bool error_state = DeleteTree(ast_compiler);
            std::cerr << "Syntax tree deleted" << std::endl;
            if(error_state){
                std::cerr << "Warning: Some nodes in the tree might have been leaked!" << std::endl;
            }
            return 0;
            
        }
        else if( arg_id == "--translate" ) { //Translator Function
            {
                std::ifstream in_program;
                std::string in_name(argv[2]);
                in_program.open(in_name);
                if(!in_program.is_open()){
                    std::cerr << "Error: Input file \"" << in_name << "\" was not found" << std::endl;
                    exit(1);
                }
                else{
                    in_program.close();
                }
            }

            const Tree *ast_translator = parseAST(argv[2],argv[4]);
            std::ostream *output;
            std::ofstream file;

            if( argc > 3 ) {
                arg_id = argv[3];
                if(arg_id == "-o"){
                    std::string filename = argv[4];
                    {
                        std::ifstream test_out;
                        test_out.open(filename);
                        if(!test_out.is_open()){
                            std::cerr << "Warning: Output file \"" << filename << "\" was not found\n";
                            std::cerr << "Creating new file \"" << filename << "\"" << std::endl;
                        }
                        else{
                            test_out.close();
                        }
                    }
                    output = &file;
                    file.open(filename);
                    
                    char last_letter = filename[filename.size()-1];
                    if( last_letter != 'y' ){
                        std::cerr << "Warning: Output file is not of type .py" << std::endl;
                    }
                }
                else{
                    std::cerr << "Warning: Unidentified flag \"" << arg_id << "\"" << std::endl;
                    std::cerr << "Redirecting translator output to command line\n" << std::endl;
                    output = &std::cout;
                }
            }
            else{
                std::cerr << "Warning: No output file specified" << std::endl;
                std::cerr << "Redirecting translator output to command line\n" << std::endl;
                output = &std::cout;
            }

            InterpretContext context;
            context.scope = 0; // indentations for python

            Interpret(output, context, ast_translator); // calls recursive
            
            *output << "\n";
            *output << "if __name__ == \"__main__\":";
            *output << "\n\t" << "import sys";
            *output << "\n\t" << "ret=main()";
            *output << "\n\t" << "sys.exit(ret)";
            *output << std::endl;

            if( output != &std::cout ){
                file.close();
            }
            else{
                std::cerr << std::endl;
            }

            std::cerr << "Cleaning AST structure..." << std::endl;
            bool error_state = DeleteTree(ast_translator);
            std::cerr << "Syntax tree deleted" << std::endl;
            if(error_state){
                std::cerr << "Warning: Some nodes in the tree might have been leaked!" << std::endl;
            }

            return 0;
        }
        else{
            std::cerr << "Error : Unidentified flag \"" << arg_id << "\"" << std::endl;
            return -1;
        }
    }

    std::cerr << "Error : Minimum number of required arguments is 3" << std::endl;
    std::cerr << "Arguments received: " << argc << std::endl;
	return -1; //return an ERROR
}

bool DeleteTree(NodePtr program){
    bool error_state = (
           DeleteBranch(program->GetLeft())
        || DeleteBranch(program->GetRight())
        || DeleteBranch(program->GetNext())
        || DeleteBranch(program->GetPointer())
        || DeleteBranch(program->GetIdentifier())
        || DeleteBranch(program->GetArguments())
        || DeleteBranch(program->GetCondition())
        || DeleteBranch(program->GetConditionOne())
        || DeleteBranch(program->GetConditionTwo())
        || DeleteBranch(program->GetConditionThree())
        || DeleteBranch(program->GetTruePath())
        || DeleteBranch(program->GetReturnValue())
        || DeleteBranch(program->GetIndex())
        || DeleteBranch(program->GetSpecifiers())
        || DeleteBranch(program->GetQualifiers())
        || DeleteBranch(program->GetStatements())
        || DeleteBranch(program->GetDeclarator())
    );
    delete program;
    return error_state;
}

bool DeleteBranch(NodePtr branch){
    if(branch != NULL){
        return DeleteTree(branch);
    }
    else{
        return false;
    }
}