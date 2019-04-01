int main(){
    int a = 1;
    int b = 1;
    int c = 1;
    if(a){
        b += 2;
    }
    else if(c > 5){
        c -= 5;
    }
    else{
        a = 4 - a;
    }
    return 0;
}