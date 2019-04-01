int main(){
    int x = 15;
    int y = 3*x;
    while(x > 0){
        if(y >= x){
            y -= x;
        }
        else{
            x -= 1;
        }
    }
    return 0;
}