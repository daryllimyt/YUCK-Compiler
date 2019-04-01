#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<cctype>

std::vector<char> FileFeed(std::string filename);
bool IsSpace(char token);
bool FileCompare(std::vector<char> text1, std::vector<char> text2);

int main(int argc, char* argv[]){
    std::string test_file = argv[1];
    std::string ref_file = argv[2];

    std::vector<char> test_text = FileFeed(test_file);
    std::vector<char> ref_text = FileFeed(ref_file);

    if(FileCompare(test_text, ref_text)){
        return 0;
    }
    else{
        return 1;
    }
}

std::vector<char> FileFeed(std::string filename){
    std::ifstream infile;
    infile.open(filename);
    if(!infile.is_open()){
        std::cerr << "Error: File \"" << filename << "\" could not be found" << std::endl;
        exit(2);
    }
    
    std::vector<char> content;
    std::vector<char> buffer;
    char token;
    bool readStart = false;
    while(infile >> token){
        if(!readStart){
            if(buffer.size() == 0){
                if(token == '$'){
                    buffer.push_back(token);
                }
                else{
                    buffer.clear();
                }
            }
            else if(buffer.size() == 1){
                if(token == 'v'){
                    buffer.push_back(token);
                }
                else{
                    buffer.clear();
                }
            }
            else if(buffer.size() == 2){
                if(token == '0'){
                    readStart = true;
                }
                else{
                    buffer.clear();
                }
            }
        }
        else{
            if(!IsSpace(token)){
                content.push_back(token);
            }
        }
    }
    infile.close();
    return content;
}

bool IsSpace(char token){
    return std::isspace(static_cast<unsigned char>(token));
}

bool FileCompare(std::vector<char> text1, std::vector<char> text2){
    if(text1.size() != text2.size()){
        return false;
    }
    for(int i = 0; i < text1.size(); i++){
        if(text1[i] != text2[i]){
            return false;
        }
    }
    return true;
}