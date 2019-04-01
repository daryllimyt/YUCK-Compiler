int fmain(){
    int x = 0;
    for(int i = 1;;i++){
        x += 1;
        if(x >= 0x100){
            break;
        }
    }
    return x;
}