#include <stdio.h>

int main(int argc, char *argv[])
{
	char c;
	FILE *fp1,*fp2;
	if(argc !=4) {
		fprintf(stderr,"error");
		return 1;
	}
	fp1 = fopen(argv[2],"r");
	if (fp1 == NULL) {
		fprintf(stderr,"File %s Open Error\n",argv[1]);
		return 2;
	}
	fp2 = fopen(argv[3],"w");
	while ((c=fgetc(fp1))!=EOF)
	{
		if(argv[1][0]=='1')
		{
			if(c>='A'&&c<='Z')

				c += 'a'-'A';
		}
		if(argv[1][0]=='2')
		{
			if(c>='a'&&c<='z')
				c -= 'a'-'A';

		}
		fputc(c,fp2);
	}
	fclose(fp1);
	fclose(fp2);
	return 0;
}
