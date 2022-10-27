#include"mygrep.h"
int main(int argc ,char *argv[]){
	char str[200];
	strcpy(str,"./");
	char* keyword ;
	char* command;
	int command_chk=0;
	int command_value=1;
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
	if(command_chk)
		command_value=chkcommand(command , keyword);
	if(command_value )
		findinfolder(str , keyword);
	
	return 0;
}
