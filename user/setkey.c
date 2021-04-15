#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"


char buf[512];


char help[6]={'-','-','h','e','l','p'};
char sekret[8]={'-','-','s','e','c','r','e','t'};

void ispis(){

printf("\nUse this program to set current active key.\n"
"After setting the key, you can use encr and decr with that key\n"
"Usage: setkey [OPTION]... [KEY]\n"
"\nCommand line options:\n"
"   -h,  --help: Show help prompt.\n"
"   -s,  --secret: Enter the key via STDIN. Hide key when entering it\n");

return;
}


int setka(char *var){

int n;
int i,ii;
if((n= atoi(var))>0 || var[0]=='0'){
	if((ii=setkey(n))==0)
		return 1;
	//printf("postavljen kluc %d \n",n );
	printf("setkey: key cant be negarive number\n");
	return 0;
}

char *p=&help[1];
char *p1=help;
//printf("p= %s a p1= %s var= %s \n",p,p1,var);
if( (strcmpp(p1,var,6)==0  && strlen(var) == 6) || (strcmpp(p,var,2)==0 && strlen(var) == 2 ) ){
	//printf("usao u setket za %s\n",var );
	ispis();	
	return 1;
}
	
p1=sekret;
p=&sekret[1];
if( (strcmpp(p1,var,8)==0 && strlen(var) == 8 ) || (strcmpp(p,var,2)==0 && strlen(var) == 2 ) ){
	int flag=0;
	setecho(0);
	printf("Enter the key: ");
	if((i=read(0,buf,sizeof(buf)))>0){
		i=0;
		
		for(int j=0; j<512;j++){
			if(!(buf[j]>= '0' && buf[j]<='9') && buf[j]!=' '){
				if(buf[j]!='\n')
					flag=0;
				break;
				};
			if(buf[j]==' ')continue;
			
			i= i*10+(buf[j]-48);
			if(!flag)
				flag=1;
		
		}
		setecho(1);
		if(flag){
			
			//printf("upisana vrednost kljuca %d \n",i);
			if((ii=setkey(i))==0)
				return 1;
		
		}	
		
		printf("setkey: Entered value cant be a key!\n");
		return 0;
		
		
	}
}


printf("setkey: params not entered correctly, try -h for help\n");
return 0;
}







int
main(int argc, char *argv[])
{
	
	if(argc==1)
		printf("setkey: insufficient params, write -h for help\n");
	for(int i=1;i<argc;i++){
			setka(argv[i]);
		}
	exit();
}
