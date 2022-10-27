#include"mygrep.h"

static int command_lineno=0;
static int command_insensitivity=0;
static int command_wordcnt=0;
static int word=0; 
static int getlineno=0;
static int word_type=0;

void findInFile(FILE* ptr , char* keyword ,char* path){
	char ch;
	long currentlength;
	int cnt=0,i=0,wordlength,lineno=1,wordoccur=0;

	wordlength = strlen(keyword);

	//printf("wordlength is %d",wordlength);
	while((ch=fgetc(ptr))!=EOF){
		if(ch>='A' && ch<='Z' && command_insensitivity )
			ch=ch+32;

		if(ch=='\n')
			lineno++;		

		if(ch==keyword[i]){
			cnt++;
			i++;
			if(cnt==wordlength){
				
				currentlength=ftell(ptr);
				ch=fgetc(ptr);
				
				if(ch==' '||ch=='.'||ch=='\n'||ch=='\t'||ch==','||ch==EOF)
					word=20;
				else 
					word=40;
				
				chktypeofword(ptr,wordlength);
				currentlength=ftell(ptr);
				
				fseek(ptr,0,SEEK_SET);
				//printf("%d",word);//written fir trial
				if(word_type==0){
					wordoccur++;

					if(wordoccur==1)
						printf("\n%s : \n",path);
					writeline(lineno,ptr);
					}
				else if(word_type==word){
					wordoccur++;
					if(wordoccur==1)
						printf("\n%s : \n",path);
					writeline(lineno,ptr);
					}
				fseek(ptr,currentlength+1,SEEK_SET);
				//printf("word is ---%d---",word);
				//ch=fgetc(ptr);
				//printf("char is %c",ch);
			}		
		}
		else{
			cnt=0;
			i=0;
		}		
	}

	if(command_wordcnt)
		if(wordoccur)
			printf("%d\n" , wordoccur);
	return ;	
}

void chktypeofword(FILE* fptr, int wordlength ){
	long currentlength=ftell(fptr);
	char ch;
	currentlength=currentlength-wordlength-2;
	fseek(fptr,currentlength,SEEK_SET);
	ch=fgetc(fptr);
	//printf("char is --%c\n",ch);

	if(word==20){
		if(ch=='\n'||ch==' '||ch==','||ch=='\t')
			word=1;
		else if((ch>='a'&& ch<='z')||(ch>='A' && ch<='Z' ))
			word=2;
	}
	if(word==40){
		if(ch==' '||ch=='\n'||ch=='\t'||ch==',')
			word=3;
		else if((ch>='a'&& ch<='z')||(ch>='A' && ch<='Z' ))
			word=4;
	}
	currentlength=currentlength+wordlength;
	fseek(fptr,0,SEEK_SET);
	fseek(fptr,currentlength,SEEK_SET);
	return;
}

void writeline(int lineno , FILE* ptr ){

	if(getlineno==lineno)
		return;

	int cnt=1;
	char ch=' ';
	getlineno=lineno;

	while(cnt<lineno){
		if(ch=='\n')
			cnt++;
		ch=fgetc(ptr);				
	}
	
	if(command_lineno==1)
		printf("%d :",lineno);	
	while(ch!=EOF && ch!='\n'){
		printf("%c",ch);
		ch=fgetc(ptr);
	}
	//printf("word is %d",word);
	printf("\n");
	return;
}

int findinfolder(char* dir_path ,char* keyword ){
	reqtypeofword(keyword);
	DIR *d;FILE* fptr;
	struct dirent *dir;
	char* file_name;int a;
	char req_path[500],reqfolder_path[500];
	
	d=opendir(dir_path);

	if(d){
		while((dir=readdir(d))){
			file_name=dir->d_name;
			int s = strlen(dir->d_name);
	
			if((s>2) && (file_name[s-1]!='~')){
				strcpy(req_path,dir_path);
				strcat(req_path,file_name);
	
				if(dir->d_type==DT_DIR){
					strcpy(reqfolder_path,req_path);
					strcat(reqfolder_path,"/");
					findinfolder(reqfolder_path,keyword);
				}
				//printf("%s  ---%d\n",req_path,s);
				fptr=fopen(req_path,"r");
				findInFile(fptr,keyword,req_path);
				fclose(fptr);
				getlineno=0;
				strcpy(req_path,"");						
			}
		}
		closedir(d);
	}
	return 0;
}

int chkcommand(char* given_comm , char* keyword){
	//reqtypeofword(keyword);
	
	char command[10];
	char key_ch;
	int key_loc=0,i=0;
	
	strcpy(command,given_comm);
	
	if(command[0]=='-'){
		i++;
		
		while(command[i]!='\0'){
		
		if(command[i]=='-'){
			i++;
			continue;
		}
		
		switch(command[i]){
		
			case 'n':
				command_lineno=1;
				break;
			case 'c' :
				command_wordcnt=1;
				break;
			case 'w':
				word_type=1;
				break;	
			case 'i':
				command_insensitivity=1;
				key_ch=keyword[key_loc];
				
				while(key_ch!='\0'){
					if(key_ch>='A'&& key_ch<='Z')
						keyword[key_loc]=keyword[key_loc]+32;
					key_loc++;
					key_ch=keyword[key_loc];
				}
				break;
			default :
				printf("command not found.\n");
				return 0;	
			}
		i++;
		}
	}
	return 1;
}

void reqtypeofword(char* key){
	int i=1,chk=0;
	int len =strlen(key);
	
	if(key[0]=='*'){
		chk++;
		word_type=2;
		
		while(key[i]!='\0'){
			key[i-1]=key[i];
			i++;
			}
		key[i-1]=key[i];
		}
		
	len=strlen(key);
	
	if(key[len-1]=='*'){
		chk++;
		word_type=3;
		len=strlen(key);
		key[len-1]='\0';
		}
		
	if(chk==2)	
		word_type=4;

}


