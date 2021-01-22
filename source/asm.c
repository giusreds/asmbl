#include<stdlib.h> 
#include<stdio.h> 
#include "asmlib.h"

void Help(){
	// asm erjh.s -o dio.exe -l -help
	puts(" asm filename.s [-o outputname.exe] [-l] \r\n -help");
	puts(" -o lets you decide the output name \r\n -l gets you an outputname.lis file with infos");
}
int main(int argc, char *argv[]) {
	char * toCompile = argv[1];
	char toprint [500];

	if (argc < 2){
		puts(" sup, 'm workin fine \r\n use me to compile .s files  \r\n asm -help if you need help");
		return 0;
	}
	if(strncmp(toCompile,"-help",10) == 0){
		Help();
		return 0;
	}
	char * output = 0; 	//output name
	int l = 0;			//write assembled code
	int od = 0;			//tells you if you've finded -o
	int i;
	for (i = 2; i < argc; i++){
		int param = argv[i][0] == '-'; 
		if(od){
			if(param){
				puts("you must specify a filename after -o");
				return 0;
			}
			else{
				output = (char *) malloc(strlen(argv[i]) + 1);
				strcpy(output,argv[i]);
			}
		}
		if(param || od){ //is a parameter
			l = strncmp(argv[i],"-l",5) == 0 || l;
			od = strncmp(argv[i],"-o",5) == 0;
		}else{
			sprintf(toprint,"%s is not a valid parameter",argv[i]);
			puts(toprint);
		}
	}
	// if the last thing that you find is a -o there are some probs
	if(od){
		puts("you must specify a filename after -o");
		return 0;
	}
	//files check
	if(!checkExtS(toCompile)) {
		puts("error this file is not supported, use *.s");
		return 1;
	}
	char * noext = getName(toCompile);
	if(output && Len(getName(output))>8){ //check the output if it was specified
		puts("the output name is too long");
		return 1;
	}
	//if the output is not specified, output = noext + ".exe"
	if(!output){
		output = (char *) malloc(strlen(noext) + 1 + 4);
		sprintf(output,"%s.exe",noext);
	}
	// add .exe in the output name in case it doesn't have it
	if(!checkExtExe(output)){
		int strl = strlen(output);
		char * tmp = (char *) malloc(strl + 1 + 4);
		strcpy(tmp, output);
		strcat(tmp, ".exe");
		free(output);
		output = tmp;
	}
	char * list = (char *) malloc(strlen(output) + 10);		// e che cazzo me ne fotto
	if(l)
		sprintf(list,">>%s.lis",getName(output));
	else
		strcpy(list,">NUL");
	sprintf(toprint,"gcc %s -o %s -Wa,-a -g %s",toCompile,output,list);
	puts(toprint);
	system(toprint);
    return 0; 
}
