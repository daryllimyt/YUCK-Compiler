int f(){
    int x = 15;
    int y = 16;
    return x*y;
}

int main(){
    int a = 35;
    int b = 15*f();
    a = 5;
    b = f();
    return 0;
}