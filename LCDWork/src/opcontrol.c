/** @file opcontrol.c
 * @brief File for operator control code
 *
 * This file should contain the user operatorControl() function and any functions related to it.
 *
 * Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "string.h"
#include "main.h"
#include "LCDList.h"

/*
 * Runs the user operator control code. This function will be started in its own task with the
 * default priority and stack size whenever the robot is enabled via the Field Management System
 * or the VEX Competition Switch in the operator control mode. If the robot is disabled or
 * communications is lost, the operator control task will be stopped by the kernel. Re-enabling
 * the robot will restart the task, not resume it from where it left off.
 *
 * If no VEX Competition Switch or Field Management system is plugged in, the VEX Cortex will
 * run the operator control task. Be warned that this will also occur if the VEX Cortex is
 * tethered directly to a computer via the USB A to A cable without any VEX Joystick attached.
 *
 * Code running in this task can take almost any action, as the VEX Joystick is available and
 * the scheduler is operational. However, proper use of delay() or taskDelayUntil() is highly
 * recommended to give other tasks (including system tasks such as updating LCDs) time to run.
 *
 * This task should never exit; it should end with some kind of infinite loop, even if empty.
 */
/*typedef void (*buttonfunct)();

typedef struct {
	char displayline[16];
	void (*actionfuncPtr)(void * parameter);
}lcdOption;

typedef struct nd {
	 lcdOption* currScreen;
	 struct nd* nextScreen;
	 struct nd* prevScreen;
}node;

node* LCDList;

TaskHandle LCDTask;

char * strcenter (char* str, int len)
{
	char * tempstr = (char *)malloc(len+1 );
	int sl = strlen(str);
	int l = (len - sl)/2;
  printf("Len - %d %d %d %s\n",l,sl,len,str);
	char * beg = tempstr;
	char * strc = str;
	for(int x=0;x<l;x++)
	{
		*beg++ = ' ';
	}
	while(*strc != '\0')
	{
		*beg++ = *strc++;
	}
	for(int x = tempstr - beg;x<len;x++)
	{
		*beg++ = ' ';
	}
*beg= *beg +l+sl ;
	for(int x=(l+sl);x<len;x++)
	{
		printf("%d\n ",x);
		*beg++ = ' ';
	}
	beg[len]='\0';
	printf("Tempstr = %s %d",tempstr, strlen(tempstr));
	delay(100);
	return(tempstr);
}


node* GetNewNode(char const * scrntitle, void (*action)(void * parameter))
{
	node* newNode = (node*)malloc(sizeof(node));
	newNode->currScreen = (lcdOption *)malloc(sizeof(lcdOption));
	strncpy(newNode->currScreen->displayline, strcenter((char *)scrntitle,16),16);
	newNode->currScreen->actionfuncPtr = action;
	newNode->nextScreen = NULL;
	newNode->prevScreen = NULL;
  return newNode;
}

void InsertAtHead(char const * scrntitle, void (*action)(void * parameter))
{
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

void InsertAtTail(char const *scrntitle, void (*action)(void * parameter))
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
*/
void button1(void * parameter)
{
	//lcdSetText(uart1, 1, "Option 1 selected");
	printf("Option #1 - Selected");
	//delay(1000);
	return;
}
/*
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
	lcdInit(uart1);
	lcdClear(uart1);
	lcdSetBacklight(uart1, true);
	LCDTask = taskCreate(LCDRun, TASK_DEFAULT_STACK_SIZE,NULL,TASK_PRIORITY_DEFAULT);
}
*/
void operatorControl() {
	initLCDLList();
//	lcdClear(uart1);
  InsertAtHead("Screen 1", button1);
	InsertAtTail("Screen 2", NULL);
	InsertAtTail("Screen 3", NULL);
//Print(LCDList);
//lcdSetBacklight(uart1, true);
//LCDTask = taskCreate(LCDRun, TASK_DEFAULT_STACK_SIZE,NULL,TASK_PRIORITY_DEFAULT);
	while (1) {
		delay(20);
	//	lcdInit(uart1);
	//	lcdSetBacklight(uart1, true);
	//	lcdSetText(uart1,1," LCD!!");
	//	lcdSetText(uart1,2,"Woohooo!!");
		//delay(10);

	}
}
