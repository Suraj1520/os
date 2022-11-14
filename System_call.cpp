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

       
       
       
       
       
       
       
       
       
       
 Stat:
 // #include <stdio.h> 
// #include <sys/stat.h>
// #include <stdlib.h> 
// #include <time.h>
// int main(int argc, char*argv[])
// {
// struct stat file; 
// int n;
// if (argc != 2)
// {
// printf("Usage: ./a.out fork.c \n"); 
// exit(-1);
// }
// if ((n = stat(argv[1], &file)) == -1)
// {
// perror(argv[1]);
// exit(-1);
// }
// printf("User id : %d\n", file.st_uid); 
// printf("Group id : %d\n",file.st_gid); 
// // printf("Block size : %d\n", file.st_blksize);
// // printf("Blocks allocated : %d\n", file.st_blocks); 
// // printf("Inode no. : %d\n", file.st_ino);
// printf("Last accessed : %s", ctime(&(file.st_atime))); 
// // printf("Last modified : %s", ctime(&(file.st_mtime))); 
// // printf("File size : %d bytes\n", file.st_size); 
// // printf("No. of links : %d\n", file.st_nlink);
// printf("Permissions : ");
// // printf( (S_ISDIR(file.st_mode)) ? "d" : "-"); 
// printf((file.st_mode & S_IRUSR) ? "r" : "-"); 
// printf( (file.st_mode & S_IWUSR) ? "w" : "-"); 
// printf( (file.st_mode & S_IXUSR) ? "x" : "-"); 
// printf( (file.st_mode & S_IRGRP) ?"r" : "-"); 
// printf( (file.st_mode & S_IWGRP) ? "w" : "-");
// printf( (file.st_mode & S_IXGRP) ? "x" : "-"); 
// printf((file.st_mode & S_IROTH) ? "r" : "-"); 
// printf( (file.st_mode & S_IWOTH) ? "w" : "-"); 
// printf( (file.st_mode & S_IXOTH) ? "x" : "-"); 
// printf("\n");
// // if(file.st_mode & S_ IFREG) 
// // printf("File type: Regular\n");
// // if(file.st_mode & S_ IFDIR) 
// // printf("File type :Directory\n");

// return 0;
// }

#include<stdio.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>

void sfile(char const filename[]);

int main(){
  ssize_t read;
  char* buffer = 0;
  size_t buf_size = 0;

  printf("Enter the name of a file to check: \n");
  read = getline(&buffer, &buf_size, stdin);

  if (read <=0 ){
    printf("getline failed\n");
    exit(1);
  }

  if (buffer[read-1] == '\n'){
    buffer[read-1] = 0;
  }

  int s=open(buffer,O_RDONLY);
  if(s==-1){
    printf("File doesn't exist\n");
    exit(1);
  }
  else{
    sfile(buffer);
  }
  free(buffer);
  return 0;
}

void sfile(char const filename[]){

  struct stat sfile;

  if(stat(filename,&sfile)==-1){
    printf("Error Occurred\n");
  }

  //Accessing data members of stat struct
  printf("\nFile st_uid %d \n",sfile.st_uid);
  printf("\nFile st_blksize %ld \n",sfile.st_blksize);
  printf("\nFile st_gid %d \n",sfile.st_gid);
  printf("\nFile st_blocks %ld \n",sfile.st_blocks);
  printf("\nFile st_size %ld \n",sfile.st_size);
  printf("\nFile st_nlink %u \n",(unsigned int)sfile.st_nlink);
//   printf("\nFile Permissions User\n");
//   printf((sfile.st_mode & S_IRUSR)? "r":"-");
//   printf((sfile.st_mode & S_IWUSR)? "w":"-");
//   printf((sfile.st_mode & S_IXUSR)? "x":"-");
//   printf("\n");
//   printf("\nFile Permissions Group\n");
//   printf((sfile.st_mode & S_IRGRP)? "r":"-");
//   printf((sfile.st_mode & S_IWGRP)? "w":"-");
//   printf((sfile.st_mode & S_IXGRP)? "x":"-");
//   printf("\n");
//   printf("\nFile Permissions Other\n");
//   printf((sfile.st_mode & S_IROTH)? "r":"-");
//   printf((sfile.st_mode & S_IWOTH)? "w":"-");
//   printf((sfile.st_mode & S_IXOTH)? "x":"-");
  printf("\n");
}
       
       
       
       
       
       
       
       
       
    Call:
    

#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <stdlib.h>
int main(int argc, char*argv[])
{
pid_t pid;
int i;
if (argc != 3)
{
printf("\nInsufficient arguments to load program");
printf("\nUsage: ./a.out <path> <cmd>\n"); exit(-1);
}
switch(pid = fork())
{
case -1:
printf("Fork failed"); 
exit(-1);
case 0:
printf("Child process\n");
i = execl(argv[1], argv[2], 0); 
if (i < 0)
{
printf("%s program not loaded using exec system call\n",argv[2]);
exit(-1);
}
default:
wait(NULL);
printf("Child Terminated\n");
exit(0);
}
return 0;
}
