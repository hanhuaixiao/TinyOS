#include "tinyOS.h"


#define NVIC_INT_CTRL	0xE000ED04
#define NVIC_PENDSVSET	0x10000000
#define NVIC_SYSPRI2	0xE000ED22
#define NVIC_PENDSV_PRI	0x000000FF

#define MEM32(addr)	*(volatile unsigned long*)(addr)
#define MEM8(addr)	*(volatile unsigned char*)(addr)

void triggerPendSVC(void)
{
	MEM8(NVIC_SYSPRI2) = NVIC_PENDSV_PRI;
	MEM32(NVIC_INT_CTRL) = NVIC_PENDSVSET;
}

void tTaskInit(tTask* task,void(*entry)(void*),void* param,tTaskStack* stack)
{
	task->stack = stack;
}

typedef struct _BlockType_t
{
	unsigned long* stackPtr;
}BlockType_t;

BlockType_t* blockPtr;
BlockType_t block;


void delay(int cnt)
{
	while(--cnt > 0);
}


int flag;
unsigned long stackBuffer[1024];


tTask tTask1;
tTask tTask2;

tTaskStack task1Env[1024];
tTaskStack task2Env[1024];

void task1(void* param)
{
	for(;;)
	{

	}
}

void task2(void* param)
{
	for(;;)
	{

	}
}

int main(void)
{
	tTaskInit(&tTask1,task1,(void*)0x11111111,&task1Env[1024]);
	tTaskInit(&tTask2,task2,(void*)0x22222222,&task2Env[1024]);

	block.stackPtr = &stackBuffer[1024];//1024的数组下边正确？？不是写错了，是因为后面用到的时候要减的
	blockPtr = &block;
	
	for(;;)
	{
		flag = 0;
		delay(100);
		flag = 1;
		delay(100);

		triggerPendSVC();
	}
}

