int fmain(){
    int x = 0;
    int y = 0;
    while(x < 4){
        x += 1;
        if(x == 2){
            continue;
        }
        y += x;
    }
    return y;
}