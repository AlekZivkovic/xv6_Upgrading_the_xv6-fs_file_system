#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"
#include "kernel/fcntl.h"
#include "kernel/fs.h"


char*
fmtname(char *path)
{
	static char buf[DIRSIZ+1];
	char *p;

	// Find first character after last slash.
	for(p=path+strlen(path); p >= path && *p != '/' && *p!='-'; p--)
		;
	p++;

	// Return blank-padded name.
	if(strlen(p) >= DIRSIZ)
		return p;
	memmove(buf, p, strlen(p));
	memset(buf+strlen(p), '\0', 1);
	return buf;
}



int one(char *path){
	int fd,n;
	if((fd = open(path, O_RDWR)) < 0){
		printf("decr: cant decript dir %s\n",fmtname(path));
		return -1;
	}
	
	n=decr(fd);
	
			
	switch(n){

		case -1 :
			printf("decr: Failed to decrypt: %s [key not set]\n",fmtname(path));break;
		case -2:
			printf("decr: %s is Dir\n",fmtname(path));break;
		case -3:
			printf("decr: Failed to decrypt, file isnt encripted %s\n", fmtname(path));break;
	
		case 0:
			printf("decr: Sucessfully decripted %s \n", fmtname(path));break;	
		
		default:
			printf("something went wrong with %s \n", path);
	}


	close(fd);
	return n;

}

void
all(char *path)
{
	char buf[512], *p;
	int fd;
	struct dirent de;
	struct stat st;

	if((fd = open(path, 0)) < 0){
		fprintf(2, "decr: cannot open %s\n", path);
		return;
	}

	if(fstat(fd, &st) < 0){
		fprintf(2, "decr: cannot stat %s\n", path);
		close(fd);
		return;
	}

	

	strcpy(buf, path);
	p = buf+strlen(buf);
	*p++ = '/';
	while(read(fd, &de, sizeof(de)) == sizeof(de)){
		if(de.inum == 0)
			continue;
		memmove(p, de.name, DIRSIZ);
		p[DIRSIZ] = 0;
		if(stat(buf, &st) < 0){
			printf("decr: cannot stat %s\n", buf);
			continue;
		}
		one(buf);	
	}
	
	
	close(fd);
}



void ispis();
char help[6]={'-','-','h','e','l','p'};
char al[13]={'-','-','d','e','c','r','y','p','t','-','a','l','l'};
int
main(int argc, char *argv[])
{
	int  i;

	if(argc <= 1){
		printf("decr: not enough params\n");
		exit();
	}
	char *p,*p1;
	

	for(i = 1; i < argc; i++){
		if(argv[i][0]!='-'){
			one(argv[i]);
		}
				
		p=&help[1];
		p1=help;
	
		if( (strcmpp(p1,argv[i],6)==0 && strlen(argv[i]) == 6 ) || ( strcmpp(p,argv[i],2)==0 && strlen(argv[i]) == 2 ) ){
			ispis();
		}
		
		p=&al[9];
		p1=al;
	
		
		if((strcmpp(p1,argv[i],13)==0 && strlen(argv[i]) == 13  ) || (strcmpp(p,argv[i],2)==0 && strlen(argv[i]) == 2 ) ){
			all(".");
		}
		
		
		
	}
	exit();
}



void ispis(){

printf("\nUse this program to decrypt files written on a disk\n"
"Usage: decr [OPTION]... [FILE]...\n"
"\nCommand line options\n"
"  -h,  --help: Show help prompt.\n"
"  -a,  --decrypt-all: Decrypt all files in CWD with current key.\n");


return;
}
