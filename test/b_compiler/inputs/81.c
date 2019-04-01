int fmain(){
    int x = 0;
    int y = 0;
    do{
        x += 1;
        if(x == 4){
            continue;
        }
        y += x;
    }while(x < 4);
    return y;
}