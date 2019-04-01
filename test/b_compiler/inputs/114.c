int fmain(){
    int x = 0;
    int y = 0;
    switch(3){
        case(1): {
            x += 1;
            break;
        }
        case(2):{
            x += 2;
            switch(1){
                case(1): y += 16; break;
                case(2): y += 32; break;
                case(3): y += 48; break;
            }
        }
        case(3):{
            x += 3;
            switch(2){
                case(1): y += 16; break;
                case(2): y += 32; break;
                case(3): y += 48; break;
            }
        }
        case(4):{
            x += 4;
            switch(3){
                case(1): y += 16; break;
                case(2): y += 32; break;
                case(3): y += 48; break;
            }
            break;
        }
        case(5): x += 5;
    }
    return x + y;
}