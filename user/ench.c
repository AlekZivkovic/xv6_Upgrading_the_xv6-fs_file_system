#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"
#include "kernel/fs.h"




char*
retparam(char *path)
{
	static char buf[DIRSIZ+1];
	char *p;

	// Find first character after last slash.
	for(p=path+strlen(path); p >= path && *p != '-'; p--)
		;
	p++;

	// Return blank-padded name.
	if(strlen(p) >= DIRSIZ)
		return p;
	memmove(buf, p, strlen(p));
	buf[buf+strlen(p)]='\0';
	//memset(buf+strlen(p), ' ', DIRSIZ-strlen(p));
	return buf;
}


int issame(char *param, char * var, int mflag){

if(mflag && strlen(param)!=strlen(var))
	return 0;

int i=2,j=0;
while(1){

if(param[i++]!=var[j++])
	return 0;
if(var[j]=='\0)break;

}

if(var[j]=='\0' &&( param[i]=='\0' || !(param[i]>='A' && param[i]<='Z') || (param[i]>='a' && param[i]<='z')))
	return 1;

return 0;
}
