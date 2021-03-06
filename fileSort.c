#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#define LESSTHAN 1
#define GREATERTHAN 2

//linked lists for characters and pointers
typedef struct llChar_{char data; struct llChar_* next;} llChar;
typedef struct llPntr_{void* data; struct llPntr_* next;} llPntr;


llPntr* load(const char* pathname);//Needs to be tested (1) (Important)
                                   //(might need to test everything else first)

void pushChar(char c, llChar** head);//works
void pushPntr(void* p, llPntr** head);//works

void printCharList(llChar data);//works
void printPntrList(llPntr data);//works
llPntr* makeSmallPList();

void freeCharList(llChar* data);//Needs to be tested (7)
void freePntrList(llPntr* data);//Needs to be tested (8)

int charLen(llChar list);//works
char* cListToString(llChar list);//works
int cListToInt(llChar list);//seems to work
void swapPntr(llPntr* x, llPntr* y);//Needs to be tested (4)//this just probably works

llPntr getPntr(llPntr data, int x);//works, note 0 equals the first element
llPntr* getPntrAdd(llPntr data, int x);
llPntr getNextP(llPntr x);
llChar getCList(llPntr x);
llPntr getLastP(llPntr current);
llPntr* getLastPAdd(llPntr current);
char* pListToString(llPntr list, int index);
void* setData(llChar x);

void orderedInsert(llPntr** head, llPntr* newNode, int (*comparator) (void*, void*));
int intComp(void* p, void* q);//seems to work
int strComp(void* p, void* q); //seems to work

int insertionSort(void* toSort, int (*comparator)(void*, void*));
int quickSort(void* toSort, int (*comparator)(void*, void*));
void qsPartition(void* toSort,int (*comparator)(void*, void*));

char* getCurrentString(llPntr* node);

int main(int argc,char* argv[]){

  //printf("%s",argv[1]);

  llPntr* data = load((char*)argv[1]);
  printPntrList(*data);

  quickSort(data, strComp);

  printf("sorting of the data - \n");

  printPntrList(*data);

  //Insert sorting functions here

  //freePntrList(data);

  //Testing Code

  //commented out code can be used to make a small list
  /*
  llPntr* pHead;
  pHead = makeSmallPList();
  */

  //End of testing Code

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
  llPntr* pntrEnd = (llPntr*) malloc(sizeof(llPntr));
  pntrEnd->data = NULL;
  pntrEnd->next = NULL;
  llPntr* pHead = pntrEnd;

  int count=1;            //because I am using these lists as stacks,
  char charTemp;          //there will be nothing coming after these two elements
  llChar* charEnd = (llChar*) malloc(sizeof(llChar));         // (pntrEnd and charEnd)
  charEnd->data = '\0';
  charEnd->next = NULL;

  llChar* cHead = charEnd;

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
      pushPntr(cHead, &pHead);
      cHead = charEnd;//reset the head to be the string terminator
                       //makes it so that all data pointers end with the same llChar struct
    }
    else{
      pushChar(charTemp, &cHead);
    }
  }
  if(cHead != charEnd){//makes it so the last element gets appended
    pushPntr(cHead, &pHead);
  }


  close(fd);
  return pHead;
}

//makeSmallPList()
//usefull for debugging and testing
//makes a list of letters as a llPntr from a - j in
//reverse order
llPntr* makeSmallPList(){
  llChar* charHead;
  llChar* cElement0 = malloc(sizeof(llChar));
  cElement0->data = '\0';
  cElement0->next = NULL;
  charHead = cElement0;

  llPntr* pHead;
  llPntr* pElement0 = malloc(sizeof(llPntr));
  pElement0->data = NULL;
  pElement0->data = NULL;
  pHead = pElement0;
  //


  int i;
  for(i = 0;i < 10;i++){
    pushChar(i+'a', &charHead);
    pushPntr(charHead, &pHead);
    charHead = cElement0;
  }
  return pHead;
}

//pushChar()
//each time you push an element onto the stack,
//the new element becomes the new head of the stack
//how to use: send the address of the head of the linked list
//note: make sure to free() this data
void pushChar(char c, llChar** head){
  llChar* newNode = NULL;
  newNode = (llChar*)malloc(sizeof(llChar));
  if(newNode == NULL){
    printf("pushChar(): Couldn't malloc() space! Exiting...");
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
//note: make sure to free() this data
void pushPntr(void* p, llPntr** head){
  llPntr* newNode = NULL;
  newNode = (llPntr*)malloc(sizeof(llPntr));
  if(newNode == NULL){
    printf("PushPntr(): Couldn't malloc() space! Exiting...");
    exit(1);
  }
  newNode->data = p;
  newNode->next = *head;
  *head = newNode;
}


void swapPntr(llPntr* x, llPntr* y){
  void* temp = (*x).data;
  (*x).data = (*y).data;
  (*y).data = temp;
}

void freeCharList(llChar* data){
  llChar* current = data;
  llChar* temp = current;
  do{
    current = (*current).next;
    free(temp);
    temp = current;
  }while((*current).next != NULL || (int)current == 0);

  //note: the last data object (charEnd) was instantiated at compile time,
  //so we never need to touch it
}

void freePntrList(llPntr* data){
  llPntr* current = data;
  llPntr* temp = current;
  do{
    current = (*current).next;
    if((*temp).data != NULL);{
      freeCharList( (llChar*)(*temp).data );
      free(temp);
    }
    temp = current;
  }while((*current).next != NULL);
}

//get the length of the character linked lists
//note: I think that this will return 1 less than the total, but thats ok
int charLen(llChar list){
  llChar current = list;
  int i = 0;

  while(current.next != NULL){
    i++;
    current = *(current.next);
  }
  return i;
}

//remember to free() this data
char* cListToString(llChar list){
  llChar current = list;

  int len = charLen(list);
  char* s = (char*)malloc(len*sizeof(char));
  if(s == NULL){
    printf("cListToString(): Couldn't malloc() space! Exiting...");
    exit(1);
  }

  int i;
  for(i = len-1;i >= 0;i--){//because the data is backwords, the string needs to be reversed
    s[i] = current.data;
    current = *current.next;
  }
  return s;
}

int cListToInt(llChar list){
  int value;
  char* str = cListToString(list);
  value = atoi(str);
  free(str);
  return value;
}
char* pListToString(llPntr list, int index){
  llPntr node = getPntr(list, index);
  llChar* str = node.data;
  char* s = cListToString(*str);
  return s;
}

llChar getCList(llPntr x){//used for debuging
  return *(llChar*)x.data;
}

llPntr getNextP(llPntr x){
  return *(llPntr*)x.next;
}

llPntr getLastP(llPntr current){
  while(current.next != NULL){
    current = *current.next;
  }
  return current;
}
llPntr* getLastPAdd(llPntr current){
  while(getNextP(current).next != NULL){
    current = *current.next;
  }
  return current.next;
}

void printCharList(llChar data){
  char* cString = cListToString(data);
  printf("%s\n",cString);
  free(cString);
}
void printPntrList(llPntr data){
  llPntr current = data;
  llChar cTemp;
  while(current.data != NULL){
    cTemp = *(llChar*)current.data;
    printCharList(cTemp);
    current = *current.next;
  }
  printf("\n");
}

llPntr getPntr(llPntr data, int x){
  llPntr current = data;
  if(current.data == NULL){
    printf("getPntr() - **WARNING** - Broken Pointers or Data");
  }
  int i;
  for(i = 0;i < x;i++){
    if(current.next == NULL){
      printf("getPntr(): Not enough elements in list");
      exit(1);
    }
    current = *current.next;
  }
  return current;
}

llPntr* getPntrAdd(llPntr data, int x){
  llPntr temp = getPntr(data,x-1);;
  return temp.next;
}

//remember to free this data
void* setData(llChar x){
  if(isdigit(x.data)){
    int* a = malloc(sizeof(int));
    *a = cListToInt(x);
    return a;
  }
  else if(isalpha(x.data)){
    char* a = malloc(sizeof(char));
    *a = cListToString(x);
    return a;
  }
}

char* getCurrentString(llPntr* node){
  llChar* strpntr = node->data;
  char* str = cListToString(*strpntr);
  printf("crnt String: %s\n", str);
  return str;
}
void orderedInsert(llPntr** head, llPntr* newNode, int (*comparator)(void*, void*)){
  llPntr* crnt;
  if(*head == NULL || comparator(getCurrentString(*head), getCurrentString(newNode)) == 2){
    newNode->next = *head;
    *head = newNode;
  }else{
    crnt = *head;
    while(crnt->next != NULL && comparator(getCurrentString(crnt->next), getCurrentString(newNode)) == 1){
      crnt = crnt->next;
    }
    newNode->next = crnt->next;
    crnt->next = newNode;
  }
}

//intComp() return values:
  // 0 -- values are equal
  // 1 -- first value is larger
  // 2 -- second value is larger
//--------------------------------
int intComp(void* p, void* q){
  int a = *(int*) p;
  int b = *(int*) q;

  int res = a-b;

  if(res == 0){ //Values are the same
    return 0;
  }else if(res > 0){// first value is larger
    return 2;
  }else if(res < 0){// Second value is larger
    return 1;
  }

  return -1; //If something went wrong
}

//strComp() return values:
  // 0 -- strings are equal
  // 1 -- First string is alphabetically superior
  // 2 -- Second string "    . . .     "
// ---------------------------------------
int strComp(void* p, void* q){
  char* str1 = (char*) p;
  char* str2 = (char*) q;

  //printf("String1: %s\nString2: %s\n", str1, str2);

  if(str1[0] == '\0' || str2[0] == '\0'){
    printf("*WARNING* -- One or more strings is empty. May have unexpected results!\n");
  }

  int i;
  for(i = 0; str1[i] == str2[i] && str1[i] != '\0'; i++){}

  //printf("char1: %c\tchar2: %c\n", str1[i], str2[i]);

  if(str1[i] > str2[i]){// Second string is superior
    return 2;
  }else if(str2[i] > str1[i]){ // First string is superior
    return 1;
  }

  //** NOTE: Lower in alphabetical order <==> LARGER ASCII value of character **

  return 0; // Strings are equal
}

int insertionSort(void* toSort, int (*comparator)(void*, void*)){
  printf("--- IN insertionSort() -----\n");

  llPntr *resList = NULL;
  llPntr *head = (llPntr*) toSort;
  llPntr* crnt = head;
  //char* str = getCurrentString(crnt);

  while(crnt != NULL){
    llPntr* next = crnt->next;


    //INSERT
    //NOTE: If comparator value == 2 then swap
    orderedInsert(&resList, crnt, comparator);

    //END INSERT
    crnt = next;
  }

  head = resList;

  //printPntrList(*crnt);

  printf("---- END insertionSort() ------\n");

  return 0;
}


int quickSort(void* toSort, int (*comparator)(void*, void*)){
  llPntr pivot = *(llPntr*)toSort;
  llPntr* temp = pivot.next;

  if(pivot.next==NULL){
    //last value, can return
    return 0;
  }

  qsPartition(toSort,comparator);
  quickSort(pivot.next,comparator); //sort all the elements after the pivot

  pivot.next = NULL;
  quickSort(&pivot,comparator);//temporarily breaks off elements after the pivot
                              //so that it can sort the first half of the elements
  pivot.next = temp;

  return 0;
}

void qsPartition(void* toSort,int (*comparator)(void*, void*)){
  llPntr* pivot = toSort;
  llPntr* current = (*pivot).next;
  llChar a, b;
  void* x;
  void* y;

  while((*current).next != NULL){
    a = getCList(*pivot);
    b = getCList(*current);
    x = setData(a);
    y = setData(b);

    if(comparator(x,y) == GREATERTHAN){
      swapPntr(pivot,current);
      current = (*current).next;
    }
  }
  swapPntr((llPntr*)toSort,getLastPAdd(*(llPntr*)toSort));
}
