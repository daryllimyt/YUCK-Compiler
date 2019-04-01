int main(){
    int x = 0;
    int y = 0;
    while(x < 4){
        x += 1;
        y += x;
        if(x == 2){
            break;
        }
    }
    return y;
}