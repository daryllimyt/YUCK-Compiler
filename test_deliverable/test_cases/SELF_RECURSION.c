int SELF_RECURSION(int i){
    
    if (i > 1){
        return SELF_RECURSION(i-1);
    }
    else{
        return i;
    }

}
