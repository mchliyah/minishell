#include<stdio.h>
#include<sys/wait.h>
# include <signal.h>
# include <fcntl.h>
#include <unistd.h>
#include <signal.h>
// int main()
// {
//     int stat;
//     pid_t pid;
//     if ((pid = fork()) == 0)
//         while(1) ;
//     else
//     {
//         kill(pid, SIGINT);
//         wait(&stat);
//         if (WIFSIGNALED(stat))
//             psignal(WTERMSIG(stat), "Child term due to");
//     }
// }
void handle_sigint(int sig)
{
    printf("Caught signal %d\n", sig);
}
  
int main()
{
    signal(SIGINT, handle_sigint);
    while (1) ;
    return 0;
}