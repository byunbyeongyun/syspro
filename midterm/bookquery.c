#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "book.h"
int main(int argc, char *argv[])
{
   int fd,in,i=2;
   struct book record;
   if (argc < 2) {
      fprintf(stderr, "How to use: %s file\n", argv[0]);
      exit(1);
   }
   if((fd = open(argv[1],O_RDONLY)) ==-1){
	   perror(argv[1]);
	   exit(2);
   }
   printf("--bookquery--\n");
   printf("0: list of all books, 1: list of available books ) ");
   scanf("%d",&in);
   printf("%-3s %-10s %-10s %-6s %-12s %-6s\n","id","bookname","author","year","numofborrow","borrow");
  
   while((read(fd, &record, sizeof(record))>0) && (record.id !=0))
   {
		if(in==1)
		{
			if(record.borrow[0]=='F')
				continue;
		}

	   printf("%3d %10s %10s %6d %12d %6s\n",record.id,record.bookname,record.author,record.year,record.numofborrow,record.borrow);
   }
   close(fd);
   exit(0);
}
