#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"



void ispis();




void printerino(char *path){
	char buf[512];
	int fd;
	if((fd=bwopen(path, O_CREATE | O_RDWR))<0){
		fprintf(2, "blockwriter: cannot create %s\n", path);
		return;
	}
	
	int bl=getnm(),a=97,flag=0;

	for(int i=0;i<bl;i++){
		if(i==0)
			printf("Writing block: 0 \n");
		 else   printf("Writing block: %d\n",i);
		memset(buf,(char)a,sizeof(buf));
		if((flag=write(fd,buf,sizeof(buf)))>0){	
			a++;
					
		}else{
			printf("blockwriter: cannot write %d\n",i);
			break;
			
		}
			
		if(!(a>=97 && a<=122))
			a=a%122+ 96;
	}
	
	close(fd);
		
}



void namechanger(char *var){

	if(setdnama(var)<0){
		printf("blockwriter: Name can only be 14 chars long");	
		exit();
	}

}


void blockchanger(char *var){

	int flag=atoi(var);
	if(*var!='0' && flag ==0){
		printf("blockwriter: only numbers are allowed try help\n");
		exit();
	}
	//initnm sys_call za setovanje br bloks
	if(initnm(flag)<0){
		printf("blockwriter: only numbers are allowed try help\n");
		exit();		
	}	



}


char help[6]={'-','-','h','e','l','p'};
char output[13]={'-','-','o','u','t','p','u','t','-','f','i','l','e'};
char bl[8]={'-','-','b','l','o','c','k','s'};


int
main(int argc, char *argv[])
{
	
	
	char *p1,*p;
	short uflag=0;
	for(int i=1;i<argc;i++){
			
		p=&help[1];
		p1=help;
		
		if( (strcmpp(p1,argv[i],6)==0 && strlen(argv[i]) == 6 ) || ( strcmpp(p,argv[i],2)==0 && strlen(argv[i]) == 2 ) ){
			ispis();
			exit();	
		}

		p=&output[1];
		p1=output;
		if( (strcmpp(p1,argv[i],13)==0 && strlen(argv[i]) == 13 ) || (strcmpp(p,argv[i],2)==0 && strlen(argv[i]) == 2 ) ){
			if(i+1>argc && argv[i+1][0]=='-'){
				printf("blockwriter: params for %s are missing try help\n",argv[i]);
				exit();			
			}
			uflag++;
			namechanger(argv[i+1]);
			continue;	

		}

	
		p=&bl[1];
		p1=bl;

		if( (strcmpp(p1,argv[i],8)==0 && strlen(argv[i]) == 8 ) || (strcmpp(p,argv[i],2)==0 && strlen(argv[i]) == 2 ) ){
			if(i+1>argc && argv[i+1][0]=='-'){
				printf("blockwriter: params for %s are missing try help\n",argv[i]);
				exit();			
			}
			uflag++;
			blockchanger(argv[i+1]);
			continue;
			
		}
		
	}
	
	if(uflag<=0 && argc>1){
		printf("blockwriter: params not entered correctly -h for help\n");
		exit();
	}

	char *tren;
	tren="./";
	printerino(tren);

	exit();
}


void ispis(){


printf("\nUse this program to create a big file filled with a-z characters.\n"
	"Default filename: long.txt\n"
	"Default blocks: 150\n"
	"Usage: blockwriter [OPTION]...\n"
"\nCommand line options:\n"
"  -h,  --help: Show help prompt.\n"
"  -o,  --output-file: Set output filename .\n"
"  -b,  --blocks: Number of blocks to write.\n");

return;
}



