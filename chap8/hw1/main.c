#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>

void environh();

int main(int argc, char *argv[])
{
	if(argv[1][0]=='-')
	{
		if(argv[1][1]=='e')
		{
			if(argc==3)
			{
				char *ptr;
				ptr = getenv(argv[2]);
				printf("%s = %s \n",argv[2],ptr);
				return 0;
			}
			environh();
			return 0;
		}
		if(argv[1][1]=='u') 
		{
			printf("My Realistic User ID : %d(%s) \n", getuid(), getpwuid(getuid())->pw_name);
			printf("My Valid User ID : %d(%s) \n", geteuid(), getpwuid(geteuid())->pw_name);
		}
		if(argv[1][1]=='g') 
		{
			printf("My Realistic User ID : %d(%s) \n", getgid(), getgrgid(getgid())->gr_name);
			printf("My Valid User ID : %d(%s) \n", getegid(), getgrgid(getegid())->gr_name);

		}
		if(argv[1][1]=='i') printf("my process number : [%d] \n",getpid());
		if(argv[1][1]=='p') printf("my parent's process number : [%d] \n",getppid());
	}
	return 0;
}

void environh() 
{
	char **ptr;
	extern char **environ;

	for (ptr = environ; *ptr !=0;ptr++)
		printf("%s \n",*ptr);
}
