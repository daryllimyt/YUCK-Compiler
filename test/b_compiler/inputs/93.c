int fmain(){
    int x = 5;
    {
        int x = 3;
        x += 5;
        return x;
    }
}