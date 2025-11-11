#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "book.h"

int main(int argc, char *argv[])
{
	int fd;
	char c[100];
	struct book record;
	int b_b,b_n;
	if (argc<2) {
		fprintf(stderr, "How to use : %s file\n",argv[0]);
		exit(1);
	}
	if ((fd = open(argv[1], O_RDWR)) ==-1) {
		perror(argv[1]);
		exit(2);
	}
	printf("--bookupdate--\n");
	printf("0 book Id: borrow book, 1 bookId : return book  ) ");
	scanf("%d %d",&b_b,&b_n);
	lseek(fd, (b_b + START_ID) * sizeof(record), SEEK_SET);
	if ((read(fd, (char *) &record, sizeof(record)) >0) &&(record.id!=0))
	{
		if(b_b==0)
		{
			if(strcmp(record.borrow,"False")==0)
			{
				printf("You've got bollow book..\n");
				strcyp(record.borrow,"True");
				record.numofborrow+=1;
				lseek(fd, (long) -sizeof(record), SEEK_CUR);
				write(fd,(char *) &record, sizeof(record));
			}
			else
			{
				printf("You cannot borrow below book since it has been booked.\n");
			}
			printf("%-3s %-10s %-10s %-6s %-12s %-6s\n","id","bookname","author","year","numofborrow","borrow");
			printf("%3d %10s %10s %6s %12d %6s\n",record.id,record.bookname,record.author,record.year,record.numofborrow,record.borrow);
		
	}
	else printf("Input Error");
}
