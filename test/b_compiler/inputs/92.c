int fmain(){
    int x = 1;
    {
        int x = 15;
        x += 5;
    }
    return x;
}