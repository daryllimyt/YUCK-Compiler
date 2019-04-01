int fmain(){
    int x = 0;
    for(int i = 0; i < 10; i++){
        if(i == 4){
            break;
        }
        x += i;
    }
    return x;
}