#include <dirent.h>
#include <stdio.h>
#include<string.h>
#include <stdlib.h>

int chkcommand(char* given_comm , char* keyword);
int findinfolder(char* dir_path ,char* keyword );

/*

	*** WARNING : PLEASE DO NOT USE IT IN DRIVER CODE *** 
	other helping functions which are written in mygrep.c

	void findInFile(FILE* ptr , char* keyword ,char* path);
	void chktypeofword(FILE* fptr, int wordlength );
	void writeline(int lineno , FILE* ptr );
	void reqtypeofword(char* key);

*/
