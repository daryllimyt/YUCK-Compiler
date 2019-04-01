int main(){
    int x = 0;
    int y = 1;
    for(;x < 5; y = x){
        x += 1;
    }
    return x;
}