#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

//linked lists for characters and pointers
typedef struct llChar_{char data; struct llChar_* next;struct llChar_* prev;} llChar;
typedef struct llPntr_{void* data; struct llPntr_* next;struct llChar_* prev;} llPntr;


void* load(const char* pathname);

void pushChar(char c, llChar** head);
llPntr pushPntr(void* p, llPntr pntrList);

int main(int argc,char* argv){


//this is all temporary for testing purposes
  llChar charList;
  //llChar* head;
  charList.data = '0';
  //head = **charList;
  printf("character 0 :: %c ::\n",charList.data);
  pushChar('a', **charList);
  printf("charList address after pushChar %x\n", charList);
  printf("character a :: %c ::\n",charList.data);
  printf("next char :: %c :: \n", (*charList.next).data);
  pushChar('b', **charList);
  printf("head* address after pushChar %x\n", charList);
  printf("character b :: %c ::\n",charList.data);
  printf("next char :: %c :: \n", (*charList.next).data);
  printf("next, next char :: %c :: \n", (*(*charList.next).next).data);
  pushChar('c', **charList);
  printf("head* address after pushChar %x\n", charList);
  printf("character c :: %c ::\n",charList.data);
  printf("next char :: %c :: \n", (*charList.next).data);
  printf("next, next char :: %c :: \n", (*(*charList.next).next).data);
  pushChar('d', **charList);
  printf("charList address after pushChar %x\n", charList);
  printf("character d :: %c ::\n",charList.data);
  printf("next char :: %c :: \n", (*charList.next).data);
  printf("next, next char :: %c :: \n", (*(*charList.next).next).data);

  return 0;
}

void* load(const char* pathname){
  void* data;
  int fd = open(pathname, O_RDONLY);

  if(fd == -1){//checks if the file couldn't be opened
    printf("Cannot Access File: ");
    switch(errno){
      case EACCES:  printf("File does not exist!\n"); exit(1);
      case EOVERFLOW: printf("File is to large!\n"); exit(1);
      default : printf("Kernel or program error.\n"); exit(1);
    }
  }

  int count=1;
  char charTemp;
  llChar charList;
  charList.data = '\0';
  charList.next = NULL;//because I am using the lists as a stack,
                       //there will be nothing coming after the first element

  while(count != 0){//load in all the data into linked lists
    count = read(fd,&charTemp,sizeof(char));
    if(count == -1){
      printf("Cannot Read File: ");
      switch(errno){
        case EINVAL: printf("Unsuitable for reading.\n"); exit(1);
        default : printf("Kernel or program error.\n"); exit(1);
      }
    }
    else if(charTemp == ' ' || charTemp == '\n' || charTemp == '\t'){
      continue;
    }
    else if(charTemp == ','){

    }
  }


  close(fd);
  return data;
}

//pushChar()
//each time you push an element onto the stack
//the new element becomes the new head of the stack
//for some reason I can't create new nodes. uh oh
void pushChar(char c, llChar** head){
  llChar* newNode = NULL;
  newNode = (llChar*)malloc(sizeof(llChar));
  if(newNode == NULL){
    printf("Couldn't malloc() space! Exiting...");
    exit(1);
  }
  newNode->data = c;
  newNode->next = *head;
  *head = newNode;
  printf("charList address %x\n", charList);
  printf("newNode address %x\n", newNode);
}
//pushPntr()
//same as pushChar() but with pointers
llPntr pushPntr(void* p, llPntr pntrList){
  llPntr newNode;
  newNode.data = p;
  newNode.next = &pntrList;
  return newNode;
}
