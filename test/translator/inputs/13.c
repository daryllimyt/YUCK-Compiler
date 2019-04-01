int f(){
    int x = 15;
    int y = 16;
    return x*y;
}

int main(){
    int a = 21;
    int b = 13;
    int c = f();
    a = 11;
    b = 24;
    int d = b+a;
    int e = 6 + 10;
    c = 15;
    d = 5*f();
    return 0;
}