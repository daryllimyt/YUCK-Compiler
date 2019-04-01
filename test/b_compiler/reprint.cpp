#include<iostream>
#include<fstream>
#include<string>
#include<vector>

std::vector<char> FileFeed(std::string filename);
void FlushBuffer(std::vector<char>& buffer, std::vector<char>& content);
void FilePrint(std::string filename, const std::vector<char>& text);

int main(int argc, char* argv[]){
    std::string in_filename = argv[1];
    std::string out_filename = argv[2];

    std::vector<char> text = FileFeed(in_filename);

    FilePrint(out_filename, text);

    return 0;
}

std::vector<char> FileFeed(std::string filename){
    std::ifstream infile;
    infile.open(filename);
    if(!infile.is_open()){
        std::cerr << "Error: File \"" << filename << "\" could not be found" << std::endl;
        exit(1);
    }

    std::vector<char> content;
    std::vector<char> buffer;
    buffer.reserve(4);
    char token = infile.get(); 
    while(!infile.eof()){
        buffer.push_back(token);
        int size = buffer.size();
        if(size == 1){
            if(buffer[0] != 'm'){
                FlushBuffer(buffer,content);
            }
        }
        else if(size == 2){
            if(buffer[1] != 'a'){
                FlushBuffer(buffer,content);
            }
        }
        else if(size == 3){
            if(buffer[2] != 'i'){
                FlushBuffer(buffer,content);
            }
        }
        else if(size == 4){
            if(buffer[3] == 'n'){
                content.push_back('f');
            }
            FlushBuffer(buffer,content);
        }
        
        token = infile.get();
    }
    FlushBuffer(buffer,content);
    return content;
}

void FlushBuffer(std::vector<char>& buffer, std::vector<char>& content){
    for(int i = 0; i < buffer.size(); i++){
        content.push_back(buffer[i]);
    }
    buffer.clear();
}

void FilePrint(std::string filename, const std::vector<char>& text){
    std::ofstream outfile;
    outfile.open(filename);
    
    for(int i = 0; i < text.size(); i++){
        outfile << text[i];
    }
    outfile << std::flush;
    outfile.close();
}