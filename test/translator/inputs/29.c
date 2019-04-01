int main(){
    int x = 15;
    int y = 20;
    int z = 0;
    while(y > 0){
        y -= 1;
        if((x+y)%2 == 0){
            continue;
        }
        z += 1;
    }
    return 0;
}