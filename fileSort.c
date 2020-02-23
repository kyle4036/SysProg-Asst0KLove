#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

void* load(const char* pathname);
Typedef struct LinkedList_{char data, Struct Node* next} LinkedList;

int main(int argc,char* argv){

  return 0;
}

void* load(const char* pathname){
  int fd = open(pathname, O_RDONLY);

  if(fd == -1){//checks if the file couldn't be opened
    printf("Cannot Access File: ");
    switch(errno){
      case EACCES:  printf("File does not exist!"); exit(1);
      case EOVERFLOW: printf("File is to large!"); exit(1);
      default : printf("Kernal or program error."); exit(1);
    }
  }

  char temp = read(fd,&temp,sizeof(char));
  if(temp == ","){

  }

  close(fd);
  return data;
}
