#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
char savedText[10][100];
char linenumb[10];
int fun[10];
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
	printf("File read success\n");
	printf("Total Line : %d\n",i);
	printf("Pls 'Enter' the line to select : ");
	scanf("%s",linenumb);
	fun[c]=atoi(&savedText[0])-1;
	for(int k=0;k<10;k++){
		if(linenumb[k]=='\0') break;
		if(linenumb[k]=='*'){
			flag =1;
			break;
		}
		if(linenumb[k]=='-'){
			flag =2;
			fun[0]=k+1;
			break;
		}
		if(linenumb[k]==','){
			flag =3;
		}
	}

	switch(flag){
		case 0: index = atoi(linenumb)-1; printf("%s",savedText[index]);break;
		case 1: for(int k=0;k<=i;k++)	printf("%s",savedText[k]);break;
		case 2:
			index = fun[0];
			for(int k=atoi(&linenumb[0])-1;k<=atoi(&linenumb[index])-1;k++)
				printf("%s",savedText[k]);
			break;
		case 3:
			token = strtok(linenumb,",");
			while(token != NULL) fun[c++]=atoi(token);
			for(int k=0;k<c;k++) printf("%s",savedText[fun[k]]);
	}
	close(fd);
	return 0;
}
