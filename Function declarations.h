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
void* setData(llChar);

int intComp(void* p, void* q);//seems to work
int strComp(void* p, void* q); //seems to work

int insertionSort(void* toSort, int (*comparator)(void*, void*));
int quickSort(void* toSort, int (*comparator)(void*, void*));
void qsPartition(void* toSort,int (*comparator)(void*, void*));

char* getCurrentString(llPntr* node);
