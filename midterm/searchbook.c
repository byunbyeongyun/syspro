#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include "book.h"
int main(int argc, char *argv[])
{
   int fd;
   char c[100];
   int bookflag=0;
   struct book record;
   if (argc < 2) {
      fprintf(stderr, "How to use : %s file\n", argv[0]);
      exit(1);
   }
   if ((fd = open(argv[1], O_RDONLY)) == -1) {
      perror(argv[1]);
      exit(2);
   }
   printf("input name of book  )  ");
   if (scanf("%s", &c) >= 1) {
      while((read(fd,(char *) &record, sizeof(record))>0)&&(record.id !=0))
	  {
	      if( strcmp(c,record.bookname)==0) 
		  {
			  bookflag=1;
			  break;
		  }
	  }
	  if(bookflag==1)
	  {
		  printf("%3s %10s %10s %6s %12s %6s\n","id","bookname","author","year","numofborrow","borrow");
		  printf("%3d %10s %10s %6d %12d %6s\n",record.id,record.bookname,record.author,record.year,record.numofborrow,record.borrow);
	  }
	  else
		  printf("not found book name : '%s'\n",c);
	  
   }
   close(fd);
   exit(0);
}

