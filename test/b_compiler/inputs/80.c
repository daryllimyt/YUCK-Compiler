int fmain(){
    int x = 0;
    int y = 0;
    do{
        x += 1;
        y += x;
        if(x == 2){
            break;
        }
    }while(x < 4);
    return y;
}