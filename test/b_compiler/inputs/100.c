int fmain(){
    int x = 0;
    for(int i = 0; i <= 5; i++){
        if(i == 1){
            continue;
        }
        x += i;
    }
    return x;
}