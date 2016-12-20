
#include "string.h"
#include "main.h"


typedef void (*buttonfunct)();

typedef struct {
	char displayline[17];
  //char *displayline;
	void (*actionfuncPtr)(void * parameter);
}lcdOption;

typedef struct nd {
	 lcdOption* currScreen;
	 struct nd* nextScreen;
	 struct nd* prevScreen;
}node;

node* LCDList;

TaskHandle LCDTask;

char * strcenter(char * dest, const char * src, int len )
{
    char * str;
    char *dstr;
    int l = (len - strlen(src))/2;
    str = (char *)src;
    dstr = dest+l;
    printf("%s %s %i %i ",dest,src, len, l);
    memset(dest,' ',len);
    *(dest+len-1) = 0;
    while(*str != 0)
    {
        *dstr++=*str++;
    }
    return (dest);
}
/* Old String Center
char * strcenter (char * str, int len)
{
	char * tempstr = (char *)malloc(len+1 );
  for (int x=0; x<len-1;x++)
  {
    *(tempstr + x) = ' ' ;
  }
  *(tempstr + len-1) = 0;
	int sl = strlen(str);
	int l = (len - sl)/2;
  printf("Len - %d %d %d %s\n",l,sl,len,str);
  printf("Len - \n ");
	char * beg = tempstr+l;
	char * strc = str;
	while(*strc != '\0')
	{
		*beg++ = *strc++;
  //  printf("%c %c \n",*(beg-1),*strc);
  }
	return(tempstr);
}
*/

node* GetNewNode(char * scrntitle, void (*action)(void * parameter))
{
	node* newNode = (node*)malloc(sizeof(node));
	newNode->currScreen = (lcdOption *)malloc(sizeof(lcdOption));
//  newNode->currScreen->displayline = strcenter(scrntitle,16);
//  strncpy(newNode->currScreen->displayline, scrntitle,16);
	strcenter(newNode->currScreen->displayline, scrntitle,16);
	newNode->currScreen->actionfuncPtr = action;
	newNode->nextScreen = NULL;
	newNode->prevScreen = NULL;
  return newNode;
}

void InsertAtHead(char  * scrntitle, void (*action)(void * parameter))
{// char * display;
//  display = strcenter(scrntitle,16);
	node* newNode = GetNewNode(scrntitle, action);
	if ( LCDList == NULL)
	{
		LCDList = newNode;
		return;
	}
	printf("%s",newNode->currScreen->displayline);
	LCDList->prevScreen = newNode;
	LCDList->nextScreen = LCDList;
	LCDList = newNode;
}

void InsertAtTail(char  *scrntitle, void (*action)(void * parameter))
{
	node* temp = LCDList;
	node* newNode = GetNewNode(scrntitle, action);
	if ( LCDList == NULL)
	{
		LCDList = newNode;
		return;
	}
	while(temp->nextScreen != NULL) temp = temp->nextScreen;
	temp->nextScreen = newNode;
	newNode->prevScreen = temp;
}

void Print(node* lList) {
	node* temp = lList;
	printf("Forward: ");
	while(temp != NULL) {
		printf("%s ",temp->currScreen->displayline);
		temp = temp->nextScreen;

	}
	printf("\n");
}

/*void button1(void * parameter)
{
	//lcdSetText(uart1, 1, "Option 1 selected");
	printf("Option #1 - Selected");
	//delay(1000);
	return;
}*/

void LCDRun (void * parameter)
{
	unsigned int buttonpressed;
	node* currnode = NULL;
  while(true)
	{
		if(currnode == NULL)
		{
			currnode = LCDList;
		}
		lcdSetText(uart1, 1,currnode->currScreen->displayline);
		lcdSetText(uart1, 2, "   <   GO   >   ");
	  delay(10);
		if (lcdReadButtons(uart1))
		    {
					buttonpressed = lcdReadButtons(uart1);
					switch (buttonpressed)
					{
						case 1:
							currnode = (currnode->prevScreen != NULL) ?currnode->prevScreen: LCDList;
							break;
						case 2:
							if (currnode->currScreen->actionfuncPtr != NULL)
							{
						   	(currnode->currScreen->actionfuncPtr)(NULL);
						  }
							break;
						case 4:
						  currnode = (currnode->nextScreen != NULL) ?currnode->nextScreen: LCDList;
							break;
					}
				}
				delay(200);
	}
}


void initLCDLList()
{
  //char *strg;
	lcdInit(uart1);
	lcdClear(uart1);
	lcdSetBacklight(uart1, true);
	LCDTask = taskCreate(LCDRun, TASK_DEFAULT_STACK_SIZE,NULL,TASK_PRIORITY_DEFAULT);
//  strg = strcenter("test", 16);
 //printf("|%s| ",strg/*,strcenter("Test", 16)*/);
}
