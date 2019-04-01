int fmain(){
    int y = 2;
    int x = 25;
    {
        int y = 1;
        x = y;
    }
    return x + y;
}