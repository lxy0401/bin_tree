#include "seqstack1.h"
#include <stddef.h>
#include <stdlib.h>

//栈初始化
void SeqStactInit(SeqStact* stack)
{
    if(stack == NULL)
    {
        //非法操作
        return ;
    }
    stack->size =0;
    stack->capacity=1000;
    stack->data=(SeqStactType*)malloc(stack->capacity* sizeof(SeqStactType));
}


//销毁栈
void SeqStactDestroy(SeqStact* stack)
{
    free(stack->data);
    stack->size=0;
    stack->capacity=0;
}

//扩容
void SeqStactReSize(SeqStact* stack)
{
    if(stack == NULL)
    {
        //非法操作
        return ;
    }
    if(stack->size<stack->capacity)
    {
        return ;
    }
    //扩容策略可按照自己的喜好来定
    stack->capacity=stack->capacity*2+1;
    SeqStactType* new_ptr=(SeqStactType*)malloc(stack->capacity*sizeof(SeqStactType));
    size_t i=0;
    for(;i<stack->size;++i)
    {
        new_ptr[i]=stack->data[i];
    }
    free(stack->data);
    stack->data=new_ptr;
}

//入栈
void SeqStactPush(SeqStact* stack,SeqStactType value)
{
    if(stack == NULL)
    {
        //非法操作
        return ;
    }
    if(stack->size>=stack->capacity)
    {
        //扩容
        SeqStactReSize(stack);
    }
    stack->data[stack->size++]=value;
    return ;
}

//出栈
void SeqStactPop(SeqStact* stack)
{
    if(stack == NULL)
    {
        //非法操作
        return ;
    }
    if(stack->size == 0)
    {
        //空栈
        return ;
    }
    --stack->size;
    return;
}

//取栈顶元素
int SeqStactTop(SeqStact* stack,SeqStactType* value)
{
    if(stack == NULL || value == NULL)
    {
        //非法操作
        return 0;
    }
    if(stack->size==0)
    {
        //空栈
        return 0;
    }
    *value=stack->data[stack->size-1];
    return 1;
}

/**
 *
 *
 * 以下为测试代码
 *
 *
 * ****/
#include <stdio.h>
#define TEST_HEADER printf("\n========%s=========\n",__FUNCTION__)
void TestInit()
{
    TEST_HEADER;
    SeqStact stack;
    SeqStactInit(&stack);
    printf("size expected 0,actuall %lu\n",stack.size);
    printf("capacity expected 0,actuall %lu\n",stack.capacity);
}

void SeqStactPrintChar(SeqStact* stack,const char* msg)
{
    printf("[%s]\n",msg);
    size_t i=0;
    for(;i<stack->size;++i)
    {
        printf("%c",stack->data[i]);
    }
    printf("\n");
}

void TestDestroy()
{

    TEST_HEADER;
    SeqStact stack;
    SeqStactInit(&stack);
    SeqStactPush(&stack,'a');
    SeqStactPush(&stack,'b');
    SeqStactPush(&stack,'c');
    SeqStactPush(&stack,'d');
    SeqStactPrintChar(&stack,"入栈四个元素");
    SeqStactDestroy(&stack);
    SeqStactPrintChar(&stack,"销毁栈");

}

void TestPush()
{

    TEST_HEADER;
    SeqStact stack;
    SeqStactInit(&stack);
    SeqStactPush(&stack,'a');
    SeqStactPush(&stack,'b');
    SeqStactPush(&stack,'c');
    SeqStactPush(&stack,'d');
    SeqStactPrintChar(&stack,"入栈四个元素");
}

void TestPop()
{

    TEST_HEADER;
    SeqStact stack;
    SeqStactInit(&stack);
    SeqStactPush(&stack,'a');
    SeqStactPush(&stack,'b');
    SeqStactPush(&stack,'c');
    SeqStactPush(&stack,'d');
    SeqStactPrintChar(&stack,"入栈四个元素");
    SeqStactPop(&stack);
    SeqStactPop(&stack);
    SeqStactPrintChar(&stack,"出栈两个元素");
    SeqStactPop(&stack);
    SeqStactPop(&stack);
    SeqStactPrintChar(&stack,"出栈两个元素");
    SeqStactPop(&stack);
    SeqStactPrintChar(&stack,"尝试对空栈进行出栈操作");
}

void TestTop()
{

    TEST_HEADER;
    SeqStact stack;
    SeqStactInit(&stack);
    SeqStactPush(&stack,'a');
    SeqStactPush(&stack,'b');
    SeqStactPush(&stack,'c');
    SeqStactPush(&stack,'d');
    SeqStactType value;
    int ret=SeqStactTop(&stack,&value);
    printf("value expected d,actuall %c\n",value);
    printf("ret expected 1,actuall %d\n",ret);
}

int main()
{
    TestInit();
    TestDestroy();
    TestPush();
    TestPop();
    TestTop();
    return 0;
}
