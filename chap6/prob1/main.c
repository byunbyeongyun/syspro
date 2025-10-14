#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int i;
	struct stat buf;
	for(i = 1;i<argc;i++) {
		printf("%s: ",argv[i]);
		if(lstat(argv[i],&buf)<0) {
			perror("lstat()");
			continue;
		}
	if(S_ISREG(buf.st_mode)) printf("%s \n","general file");
	else if(S_ISDIR(buf.st_mode)) printf("%s \n","Directory");
	else if(S_ISLNK(buf.st_mode)) printf("%s \n","Symbolic Link");
	else printf("\n");
	}
	exit(0);
}
