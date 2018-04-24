#pragma once
#include <stddef.h>
#define SeqQueueMaxSize 1000

#define FOR_BINTREE
#ifdef FOR_BINTREE
struct TreeNode;
typedef struct TreeNode* SeqQueueType;
#else
typedef char SeqQueueType;
#endif

typedef struct SeqQueue
{
    SeqQueueType data[SeqQueueMaxSize];
    size_t head;
    size_t tail;
    size_t size;
}SeqQueue;


//队列初始化
void SeqQueueInit(SeqQueue* q);

//销毁队列
void SeqQueueDestroy(SeqQueue* q);

//入队
void SeqQueuePush(SeqQueue* q,SeqQueueType value);

//出队
void SeqQueuePop(SeqQueue* q);

//取队首元素
int SeqQueueFront(SeqQueue* q,SeqQueueType* value);
