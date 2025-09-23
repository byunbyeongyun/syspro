#include <stdio.h>
#include <string.h>
#include "copy.h"

char line[MAXLINE];
char arr[5][MAXLINE];

int main(){
	int len;
	int n=0;
	
	while(gets(line) != NULL&&n<5) {
		copy(line, arr[n++]);
	}

	for (int i=0;i<4;i++){
		for(int j=0;j<4-i;j++){
			if (strlen(arr[j])<strlen(arr[j+1])) {
				strcpy(line, arr[j]);
				strcpy(arr[j], arr[j+1]);
				strcpy(arr[j+1],line);
			}
		}
	}
	for (int i=0;i<5;i++) {
		printf("%s\n", arr[i]);
	}
	return 0;
}
