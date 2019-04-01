int f1(int x){
    return x;
}

int f2(int a, int b, int c, int d, int e){
    return a + b + c + d + e;
}

int main(){
    int a = 1;
    int b = 2;
    int c = 3;
    int d = 4;
    int e = 5;
    return f2(a,f1(b),f1(c),d,e);
}