#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void* load(const char* pathname);

int main(int argc,char* argv){

  return 0;
}

void* load(const char* pathname){
  int fd = open(pathname, O_RDONLY);

  if(fd == -1){//checks if the file couldn't be opened
    printf("Cannot Access File: ")
    switch(errno){
      case EACCES:  printf("File does not exist!"); return 1;
      case EOVERFLOW: printf("File is to large!"); return 1;
      default : printf("Kernal or program error."); return 1;
    }
  }

  char temp;
  read(fd,&temp,sizeof(char))
  if
}
