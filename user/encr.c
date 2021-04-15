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
		printf("encr: Failed to open %s\n",fmtname(path));
		return -1;
	}
	
	n=encr(fd);
	
			
	switch(n){

		case -1 :
			printf("encr: Failed to encrypt: %s [key not set]\n",fmtname(path));break;
		case -2:
			printf("encr: Failed to encrypt: %s is Dir\n",fmtname(path));break;
		case -3:
			printf("encr: Failed to encrypt: already encrypted %s\n", fmtname(path));break;
	
		case 0:
			printf("encr: Sucessfully encripted %s \n", fmtname(path));break;	
		
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
		fprintf(2, "encr: cannot open %s\n", path);
		return;
	}

	if(fstat(fd, &st) < 0){
		fprintf(2, "encr: cannot stat %s\n", path);
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
			printf("encr: cannot stat %s\n", buf);
			continue;
		}
		//printf("%d\n",one(buf));
		one(buf);	
	}
	
	
	close(fd);
}



void ispis();
char help[6]={'-','-','h','e','l','p'};
char al[13]={'-','-','e','n','c','r','y','p','t','-','a','l','l'};
int
main(int argc, char *argv[])
{
	int  i;

	if(argc <= 1){
		printf("encr: not enough params\n");
		exit();
	}
	char *p,*p1;
	

	for(i = 1; i < argc; i++){
		if(argv[i][0]!='-'){
			one(argv[i]);
		}
				
		p=&help[1];
		p1=help;
	
		//printf("p= %s a p1= %s var= %s \n",p,p1,var);
		if( (strcmpp(p1,argv[i],6)==0 && strlen(argv[i]) == 6 ) || ( strcmpp(p,argv[i],2)==0 && strlen(argv[i]) == 2 ) ){
			ispis();
			exit();
		}
		
		p=&al[9];
		p1=al;
	
		
		if( (strcmpp(p1,argv[i],13)==0 && strlen(argv[i]) == 13 ) || ( strcmpp(p,argv[i],2)==0 && strlen(argv[i]) == 2 ) ){
			all(".");
		}
		continue;
		
		
		
	}
	exit();
}



void ispis(){

printf("\nUse this program to encrypt files written on a disk\n"
"Usage: encr [OPTION]... [FILE]...\n"
"\nCommand line options\n"
"  -h,  --help: Show help prompt.\n"
"  -a,  --encrypt-all: Encrypt all files in CWD with current key.\n");


return;
}
