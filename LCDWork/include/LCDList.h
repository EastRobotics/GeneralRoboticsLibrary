typedef void (*buttonfunct)();

void InsertAtHead(char const * scrntitle, void (*action)(void * parameter));


void InsertAtTail(char const *scrntitle, void (*action)(void * parameter));


void initLCDLList();
