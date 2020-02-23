#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

typedef struct llChar_{char data, Struct llChar_* next} llChar;
typedef struct llPntr_{char data, Struct llPntr_* next} llPntr;
void* load(const char* pathname);

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
      default : printf("Kernal or program error."); exit(1);
    }
  }

  int count;
  char temp;

  count = read(fd,&temp,sizeof(char));
  if(count == -1){
    printf("Cannot Read File: ");
    switch(errno){
      case EINVAL: printf(" Unsuitable for reading."); exit(1);
      default : printf("Kernal or program error."); exit(1);
    }
  }


  close(fd);
  return data;
}
