int f1(int x);
int f2(int x);

int f1(int x){
    return x + f2(x);
}

int f2(int x){
    if(x <= 0){
        return 0;
    }
    else{
        return f1(x-1);
    }
}

int fmain(){
    return f1(5);
}