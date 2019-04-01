int x = 15;

int f(){
    x = 3;
    return x;
}

int y = 2;

int fmain(){
    y = x/3;
    return y + f();
}