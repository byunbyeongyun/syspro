#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
   FILE *fp;
   int c;
   int index=1;
   if (argc < 2) 
      fp = stdin;
   for(int i=1; i<argc;i++) {
		if(strcmp(argv[i],"-n")==0) continue;
		fp = fopen(argv[i],"r");
		c = getc(fp);
  		 while (c != EOF) 
  		 {
	  		 if(strcmp(argv[1],"-n")==0) 
		  		 printf("%d ",index++);
	  		 while(c != '\n') {
				 putc(c, stdout);
				 c = getc(fp);
 	  		 }
	  		 putc(c,stdout);
	  		 c = getc(fp);
		 }
  		 fclose(fp);
	 }
   return 0;
}

