int x = 2;

int f(){
    int x = 5;
    x += 31;
    x = 12;
    return x;
}

int fmain(){
    f();
    return x;
}