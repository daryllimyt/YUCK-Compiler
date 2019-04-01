int f1(int a, int b, int c, int d, int e, int f){
    return a + b + c + d + e + f;
}

int f2(int a, int b, int c, int d, int e){
    return a + b + c + d + e;
}

int fmain(){
    int a = 1;
    int b = 2;
    int c = 3;
    int d = 4;
    int e = 5;
    int x = 16;
    int y = 32;
    int z = 48;
    return f2(x,y,f1(a,b,c,d,e),z,f1(a,b,c,d,e));
}