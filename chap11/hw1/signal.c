#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

int mysignal(int signum, void (*handler)(int)) {
    struct sigaction sa;
    
    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0; 
    
    if (sigaction(signum, &sa, NULL) == -1) {
        return -1;
    }
    return 0;
}

void alarmHandler(int signo);

int main( )
{
    if (mysignal(SIGALRM, alarmHandler) == -1) {
        fprintf(stderr, "Failed to set SIGALRM handler.\n");
        return 1;
    }
    
    alarm(5);
    short i = 0;
    
    while (1) {
        sleep(1);
        i++;
        printf("%d second\n", i);
    }
    
    return 0;
}

void alarmHandler(int signo)
{
    printf("Wake up\n");
    exit(0);
}
