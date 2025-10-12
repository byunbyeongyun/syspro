#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
char savedText[10][100];

int main(int argc, char *argv[]) {
	char buf;
	int fd;
	int i=0,j=0;
	int flag=0;
	int index,c=0;
	char * token;
	if ((fd = open(argv[1],O_RDONLY)) ==-1)
		perror(argv[1]);
	while(1) {
		if(read(fd,&buf,1)==0) break;
		savedText[i][j++]=buf;
		if(buf == '\n') 
		{
			i++;
			j=0;
			continue;
		}
	}
	for(int k=i-1;k>=0;k--){
		printf("%s",savedText[k]);
	}
	close(fd);
	return 0;
}
