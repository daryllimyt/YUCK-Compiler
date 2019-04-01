int x = 2;

int f(){
    int x = 5;
    x += 31;
    x = 12;
    return x;
}

int main(){
    f();
    return x;
}