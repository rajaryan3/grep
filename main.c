// driver code for grep implementation 

#include"mygrep.h"

int main(int argc ,char *argv[]){
	char str[200];		// to store the path of folder
	strcpy(str,"./");	// if no path given consider the working directory
	char* keyword ;	// to store word recived from user
	char* command;		// like -i,-n,-w etc.
	int command_chk=0;	// to check any command is given or not 
	int command_value=1;	// assign appropriate value according to command
	
	/*
		
		there are multiple ways to give input 
		argc==2	:	1) ./a.out "string_to_find"
		argc==3	:	2) ./a.out -"commands" "string_to_find"
		argc==3	:	3) ./a.out "string_to_find" "path_of_folder_over_which_user_want_to_search" 
		argc==4	:	4) ./a.out -"commands" "string_to_find" "path_of_folder_over_which_user_want_to_search"
	
	*/
	
	// checking format of input
	if(argc==2){		
		keyword=argv[1];
	}
	else if(argc==3){
		
		if(argv[1][0]=='-'){
			
			command=argv[1];
			command_chk++;
			keyword=argv[2];
		}
		else{
			
			keyword=argv[1];
			strcpy(str,"");
			strcpy(str,argv[2]);
		}
	}
	else if(argc==4){
	
		command=argv[1];
		command_chk++;
		keyword=argv[2];
		strcpy(str,"");
		strcpy(str,argv[3]);
	}
	
	//using chkcommand()
	if(command_chk)
		command_value=chkcommand(command , keyword);
	
	//if command_value is valid then proceed to grep implementation
	if(command_value )
		findinfolder(str , keyword);
	
	return 0;
}
