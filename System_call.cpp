Fork




#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
main()
{
pid_t pid;
int x = 5;
pid =
fork(); x++;
if (pid < 0)
{
printf("Process creation
error"); exit(-1);
}
else if (pid == 0)
{
printf("Child process:");
printf("\nProcess id is %d", getpid());
printf("\nValue of x is %d", x);
printf("\nProcess id of parent is %d\n", getppid());
}
else
{
printf("\nParent process:");
printf("\nProcess id is %d", getpid());
printf("\nValue of x is %d", x);
printf("\nProcess id of shell is %d\n", getppid());
}
}

       
       
       
       
 Wait--
       
 #include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
main()
{
int i, status;
pid_t pid;
pid = fork();
if (pid < 0)
{
printf("\nProcess creation
failure\n"); exit(-1);
}
else if(pid > 0)
{
wait(NULL);
printf ("\nParent starts\nEven Nos:
"); for (i=2;i<=10;i+=2)
printf ("%3d",i); printf
("\nParent ends\n");
}
else if (pid == 0)
{
printf ("Child starts\nOdd Nos:
"); for (i=1;i<10;i+=2)
printf ("%3d",i);
printf ("\nChild ends\n");
}
}
        
        
        
        
        
 Exec--
        
 #include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
main(int argc, char*argv[])
{
pid_t pid;
int i;
if (argc != 3)
{
printf("\nInsufficient arguments to load program");
printf("\nUsage: ./a.out <path> <cmd>\n"); exit(-
1);
}
switch(pid = fork())
{
case -1:
printf("Fork
failed"); exit(-1);
case 0:
printf("Child process\n");
i = execl(argv[1], argv[2],
0); if (i < 0)
{
printf("%s program not loaded using exec
system call\n", argv[2]);
exit(-1);
}
default:
wait(NULL);
printf("Child
Terminated\n"); exit(0);
}
}
