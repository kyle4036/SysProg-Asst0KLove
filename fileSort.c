#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

//linked lists for characters and pointers
typedef struct llChar_{char data; struct llChar_* next;} llChar;
typedef struct llPntr_{void* data; struct llPntr_* next;} llPntr;


llPntr* load(const char* pathname);//Needs to be tested (1) 
                                   //(might need to test everything else first)

void pushChar(char c, llChar** head);
void pushPntr(void* p, llPntr** head);

void printCharList(llChar data);//Needs to be tested (5)
void printPntrList(llPntr data);//Needs to be tested (6)

void freeCharList(llChar* data);//Needs to be tested (7)
void freePntrList(llPntr* data);//Needs to be tested (8)

int charLen(llChar list);//Needs to be tested (2)
char[] cListToString(llChar list);//Needs to be tested (3)
void swapPntr(llPntr x, llPntr y);//Needs to be tested (4)

int main(int argc,char* argv){

  llPntr* data = load(argv[1]);

  printPntrList(&data);

  return 0;
}

llPntr* load(const char* pathname){
  int fd = open(pathname, O_RDONLY);

  if(fd == -1){//checks if the file couldn't be opened
    printf("Cannot Access File: ");
    switch(errno){
      case EACCES:  printf("File does not exist!\n"); exit(1);
      case EOVERFLOW: printf("File is to large!\n"); exit(1);
      default : printf("Kernel or program error.\n"); exit(1);
    }
  }

  //set up the last data points
  llPntr pntrEnd;
  pntrEnd.data = NULL;
  pntrEnd.next = NULL;
  llPntr* pHead = &pntrEnd;

  int count=1;
  char charTemp;
  llChar charEnd;
  charEnd.data = '\0';
  charEnd.next = NULL;//because I am using these lists as stacks,
                       //there will be nothing coming after these elements
  llChar* cHead = &charEnd;

  while(count != 0){//load in all the data into linked lists
    count = read(fd,&charTemp,sizeof(char));
    if(count == -1){
      printf("Cannot Read File: ");
      switch(errno){
        case EINVAL: printf("File unsuitable for reading.\n"); exit(1);
        default : printf("Kernel or program error.\n"); exit(1);
      }
    }
    else if(charTemp == ' ' || charTemp == '\n' || charTemp == '\t'){
      continue;//throws out any garbage data
    }
    else if(charTemp == ','){
      pushPntr(&cHead, &pHead);
      cHead = &charEnd;//reset the head to be the string terminator
                       //makes it so that all data pointers end with the same llChar struct
    }
    else{
      pushChar(charTemp, &cHead);
    }
  }


  close(fd);
  return pHead;
}

//pushChar()
//each time you push an element onto the stack,
//the new element becomes the new head of the stack
//how to use: send the address of the head of the linked list
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
  //printf("head address %x\n", head);
  //printf("newNode address %x\n", newNode);
}

//pushPntr()
//same as pushChar() but with pointers
void pushPntr(void* p, llPntr** head){
  llPntr* newNode = NULL;
  newNode = (llPntr*)malloc(sizeof(llPntr));
  if(newNode == NULL){
    printf("Couldn't malloc() space! Exiting...");
    exit(1);
  }
  newNode->data = p;
  newNode->next = *head;
  *head = newNode;
}

//get the length of the character linked lists
//note: I think that this will return 1 less than the total, but thats ok
int charLen(llChar list){
  llChar current = list;
  int i = 0;

  while(current.next != NULL){
    i++;
    current = *current.next;
  }
  return i;
}

//remember to free this data
char* cListToString(llChar list){
  llChar current = list;

  int len = charLen(list);
  char* s = (char*)malloc(len*sizeof(char));

  int i;
  for(i = 0;i<=len;i++){
    s[i] = current.data;
    current = *current.next;
  }
  return s;
}

void swapPntr(llPntr x, llPntr y){
  void* temp = x.data;
  x.data = y.data;
  y.data = temp;
}

void freeCharList(llChar* data){
  llChar* current = data;
  llChar* temp = current;
  do{
    current = (*current).next
    free(temp);
    temp = current;
  }while(curent.next != NULL)

  //note: the last data object (charEnd) was instantiated at compile time,
  //so we never need to touch it
}
void freePntrList(llPntr* data){
  llPntr* current = data;
  llPntr* temp = current;
  do{
    current = (*current).next
    freeCharList( (llChar*)(*temp).data );
    free(temp);
    temp = current;
  }while(curent.next != NULL)
}

void printCharList(llChar data){
  char* cString = cListToString(data);
  printf("%s\n",cString);
  free(cString);
}
void printPntrList(llPntr data){
  llPntr current = data;
  while(current.data != NULL){
    printCharList((llChar)current.data);
    current = *(current.next);
  }
}
