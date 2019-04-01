double atof(const char* str);

double ATOF(){

	char str[4] = { '1', '2', '.', '3','\000'};
	return atof(str);
}
