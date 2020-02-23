#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

//linked lists for characters and pointers
typedef struct llChar_{char data; struct llChar_* next} llChar;
typedef struct llPntr_{void* data; struct llPntr_* next} llPntr;


void* load(const char* pathname);

void pushChar(char c, llChar charList);
void pushPntr(void* p, llPntr pntrList);

int main(int argc,char* argv){

  return 0;
}

void* load(const char* pathname){
  void* data;
  int fd = open(pathname, O_RDONLY);

  if(fd == -1){//checks if the file couldn't be opened
    printf("Cannot Access File: ");
    switch(errno){
      case EACCES:  printf("File does not exist!"); exit(1);
      case EOVERFLOW: printf("File is to large!"); exit(1);
      default : printf("Kernel or program error."); exit(1);
    }
  }

  int count=1;
  char charTemp;
  llChar charList;

  while(count != 0){//load in all the data into linked lists
    count = read(fd,&temp,sizeof(char));
    if(count == -1){
      printf("Cannot Read File: ");
      switch(errno){
        case EINVAL: printf("Unsuitable for reading."); exit(1);
        default : printf("Kernel or program error."); exit(1);
      }
    }
    else if(temp == ','){

    }
  }


  close(fd);
  return data;
}
void pushChar(char c, llChar charList){
  
}
void pushPntr(char c, llPntr pntrList){

}
