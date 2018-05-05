#pragma once
#include <stddef.h>
typedef char SeqStactType;
typedef struct SeqStact
{
    SeqStactType* data;
    size_t size;
    size_t capacity;//data指向内存中能最大容纳的元素的个数MAX_SIZE的替代品
}SeqStact;

//栈初始化
void SeqStactInit(SeqStact* stack);

//销毁栈
void SeqStactDestroy(SeqStact* stack);

//入栈
void SeqStactPush(SeqStact* stack,SeqStactType value);

//出栈
void SeqStactPop(SeqStact* stack);

//取栈顶元素
int SeqStactTop(SeqStact* stack,SeqStactType* value);
