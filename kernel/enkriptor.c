#include "types.h"
#include "defs.h"
#include "fs.h"
#include "spinlock.h"
#include "sleeplock.h"
#include "file.h"
#include "enkriptor.h"


int keyflag=0;
int key=0;
char buf[512];

int encript(char *buf){

	char *a=buf;
	uint i=0;
	
	while(*a!='\0'){
		*a= (char) ( ( ( (int) *a ) + key ) % 255);		
		a++;
		i++;
	}
return i;
}
int decript(char *buf){
	char *a=buf;
	uint i=0;
	
	while(*a!='\0'){
		int flag= ( (int) *a ) - key;
		if(flag<0)
			flag+=256;
		*a= (char) ( flag % 255);		
		a++;
		i++;
	}
return i;

}

//problem je bio deadlock...
int fileencr(struct file *f){
	
	
	
	if(f->readable == 0)
		return -1;
		
	if((f->ip)->major!=0)
		return -1;			
	
	int r;
	uint re=f->off, wr=f->off;;

	
	while((r=fileread(f,buf,sizeof(buf)))> 0){
		encript(buf);

		re=f->off;;
		f->off=wr;
	
		if (filewrite(f, buf, r) != r) 
			return -1;
			

			
		wr=f->off;
		f->off=re;
		
	}

	begin_op();
	ilock(f->ip);
	(f->ip)->major=1;

	iupdate(f->ip);
	iunlock(f->ip);
	end_op();
	return 0;
}

int filedecr(struct file *f){
	
	
	if(f->readable == 0)
		return -1;
	
		
	if((f->ip)->major!=1)
		return -1;	
	
	int r;
	uint re=f->off, wr=f->off;;
	
	while((r=fileread(f,buf,sizeof(buf)))> 0){
		decript(buf);
		
		re=f->off;;
		f->off=wr;
		
		if (filewrite(f, buf, r) != r) {
			return -1;
		}
		
		wr=f->off;
		f->off=re;
	}
	begin_op();
	ilock(f->ip);
	
	(f->ip)->major=0;

	iupdate(f->ip);
	iunlock(f->ip);
	end_op();
	return 0;
}



