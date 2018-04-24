#include "seqqueue.h"
#include<stdlib.h>


//队列初始化
void SeqQueueInit(SeqQueue* q)
{
    if(q == NULL)
    {
        //非法操作
        return ;
    }
    q->size = 0;
    q->head = 0;
    q->tail = 0;
    return ;
}

//销毁队列
void SeqQueueDestroy(SeqQueue* q)
{

    if(q == NULL)
    {
        //非法操作
        return ;
    }
    q->size = 0;
    q->head = 0;
    q->tail = 0;
    return ;
}

//入队
void SeqQueuePush(SeqQueue* q,SeqQueueType value)
{
    if(q == NULL)
    {
        //非法操作
        return;
    }
    if(q->size>=SeqQueueMaxSize)
    {
        //队列已满
        return;
    }
    q->data[q->tail++]=value;
    if(q->tail>=SeqQueueMaxSize)
    {
        q->tail=0;
    }
    ++q->size;
}

//出队
void SeqQueuePop(SeqQueue* q)
{
    if(q == NULL)
    {
        //非法操作
        return;
    }
    if(q->size == 0)
    {
        //队列为空
        return ;
    }
    ++q->head;
    --q->size;
    if(q->head == SeqQueueMaxSize)
    {
        q->head=0;
    }
}

//取队首元素
int SeqQueueFront(SeqQueue* q,SeqQueueType* value)
{
    if(q == NULL || value == NULL)
    {
        //非法操作
        return 0;
    }
    if(q->size == 0)
    {
        //队列为空
        return 0;
    }
    *value=q->data[q->head];
    return 1;
}


/*****
 *
 *以下为测试代码
 *
 *
 * *****/
#if 0
#include <stdio.h>
#define TEST_HEADER printf("\n========%s=========\n",__FUNCTION__)
void TestSeqQueue()
{
    TEST_HEADER;
    SeqQueue queue;
    SeqQueueInit(&queue);
    SeqQueuePush(&queue,'a'); 
    SeqQueuePush(&queue,'b');
    SeqQueuePush(&queue,'c');
    SeqQueuePush(&queue,'d');
    SeqQueueType value;
    int ret=0;
    ret=SeqQueueFront(&queue,&value);
    printf("ret expected 1,actuall %d\n",ret);
    printf("value expected a,actuall %c\n",value);
    SeqQueuePop(&queue);

    ret=SeqQueueFront(&queue,&value);
    printf("ret expected 1,actuall %d\n",ret);
    printf("value expected b,actuall %c\n",value);
    SeqQueuePop(&queue);
    
    ret=SeqQueueFront(&queue,&value);
    printf("ret expected 1,actuall %d\n",ret);
    printf("value expected c,actuall %c\n",value);
    SeqQueuePop(&queue);

    ret=SeqQueueFront(&queue,&value);
    printf("ret expected 1,actuall %d\n",ret);
    printf("value expected d,actuall %c\n",value);
    SeqQueuePop(&queue);
    
    ret=SeqQueueFront(&queue,&value);
    printf("ret expected 0,actuall %d\n",ret);
    //printf("value expected a,actuall %c",value);
    SeqQueuePop(&queue);
}

int main()
{
    TestSeqQueue();
    return 0;
}
#endif
