void f(int x){
    int y = x + 15;
}

int g(int a, int b, int c, int d){
    int x = a + 12;
    x = x*b;
    int y = c + a;
    y = d + 14;
    return x - y;
}

int main(){
    int a = 21;
    int b = 42;
    int c = 33;
    int d = 90;
    f(a);
    f(0);
    int e = g(a,b,c,d);
    e = g(1,2,3,4);
    return 0;
}