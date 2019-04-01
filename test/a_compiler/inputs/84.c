int f(int i);

int main(){
    if(f(2) != 1){
        return 2;
    }
    
    return 1;
}

int f(int i){
    if(i > 1){
        return f(i-1);
    }
    else{
        return i;
    }
}