int IF_ELSE_F(){
	int i = 0;

	if(0){ //force branch
		i = i + 5;
	}
	else{
		i = i + 10; 
	}

	return i;
}
