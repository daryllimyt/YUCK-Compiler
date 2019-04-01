int f(){
    return 10;
}

int main(){
    int x = 5*f();
    int y = f()*f() + f();
    int z = f()/12;
    int a = x*f() + f()/(y + 7) - f()*z;
    return f() - 10;
}