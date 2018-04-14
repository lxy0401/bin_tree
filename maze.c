#include <stdio.h>
#define Max_ROW 6
#define Max_COL 6
typedef struct Maze
{
    int map[Max_ROW][Max_COL];
}Maze;

//初始化
void MazeInit(Maze* maze)
{
    int map[Max_ROW][Max_COL]={{0,1,0,0,0,0},
                                {0,1,1,1,0,0},
                                {0,1,0,1,0,0},
                                {0,1,0,1,0,0},
                                {0,1,1,0,0,0},
                                {0,0,1,0,0,0}};
    size_t i=0;
    for(;i<Max_ROW;++i)
    {
        size_t j=0;
        for(;j<Max_COL;++j)
        {
            maze->map[i][j]=map[i][j];
        }
    }
    return ;
}

//打印迷宫
void MazePrint(Maze* maze)
{
    size_t i=0;
    for(;i<Max_ROW;++i)
    {
        size_t j=0;
        for(;j<Max_COL;++j)
        {
            printf("%2d ",maze->map[i][j]);
        }
        printf("\n");
    }
}

/*************
 *
 * Round1使用递归来实现迷宫问题
 * 本质上还是使用栈，不过这个栈是由操作系统提供的，即函数调用栈
 *
 * ***********/
typedef struct Point
{
    int row;
    int col;
}Point;

//判断点是否能落脚
int CanStay(Maze* maze,Point pt)
{
    //1.若pt点在迷宫圈外，则不能落脚
    if(pt.row < 0 || pt.row >= Max_ROW || pt.col < 0 || pt.col >= Max_COL)
    {
        return 0;
    }
    //2.若pt地图内部，若位置为1，则能落脚，若位置为0或者为2，则不能落脚
    int value=maze->map[pt.row][pt.col];
    if(value == 1)
    {
        return 1;
    }
    return 0;
}

//将走过的点做标记2
void Mark(Maze* maze,Point cur)
{
    maze->map[cur.row][cur.col]=2;
}

//判断是否为出口
int IsExit(Maze* maze,Point cur,Point entry)
{
    (void)maze;
    //1.看当前点是否为入口，若为入口，则一定不是出口
    if(cur.row == entry.row && cur.col == entry.col)
    {
        //为入口点
        return 0;
    }
    //2.若点在地图边上，则说明是出口
    if(cur.row == 0 || cur.row == Max_ROW-1 || cur.col == 0 || cur.col == Max_COL-1)
    {
        return 1;
    }
    return 0;
}

void _GetPath(Maze* maze,Point cur,Point entry)
{
    //1.判定当前点是否能落脚
    printf("cur:%d,%d\n",cur.row,cur.col);
    if(!CanStay(maze,cur))
    {
        //不能落脚
        return;
    }
    //2.若能落脚，就给当前位置坐标2，2表示已经走过的路
    Mark(maze,cur);
    //3.若当前点是出口，则说明找到了一条出路，探测结束
    if(IsExit(maze,cur,entry))
    {
        //找到了出路
        printf("找到了一条路径\n");
        return;
    }
    //4.若当前点不是出口，则按顺时针探测四个相邻的点，递归地调用函数自身，递归时更新cur
    //（每次递归的时候，点都是下一次要走的点，这个点究竟能不能走，交给递归函数来判断）
    Point up=cur;
    up.row-=1;//上方的点
    _GetPath(maze,up,entry);
    
    Point right=cur;
    right.col+=1;//右
    _GetPath(maze,right,entry);

    Point down=cur;
    down.row+=1;//下
    _GetPath(maze,down,entry);

    Point left=cur;
    left.col-=1;//左
    _GetPath(maze,left,entry);
    
    return;
}

void GetPath(Maze* maze,Point entry)
{
    if(maze == NULL)
    {
        //非法操作
        return;
    }
    //用_GetPath来辅助完成递归
    _GetPath(maze,entry,entry);//第一个entry为当前走到的点，第二个entry为真正的入口点
}

/****
 *
 * Round2 非递归的方法来实现迷宫问题
 *
 * ******/

/*
#include "seqstack1.h"
typedef char SeqStactType;
typedef struct SeqStact
{
SeqStactType* data;
    size_t size;
    size_t capacity;//data指向内存中能最大容纳的元素的个数MAX_SIZE的替代品
}SeqStact;


void GetPathByLoop(Maze* maze,Point entry)
{
    //1.创建一个栈，并初始化，这个栈保存着我们走过的路径
   SeqStact stack;
   SeqStactInit(&stack);
    //2.判定入口是否合法，若不能则表示参数非法
    if(!CanStay(maze,entry))
    {
        //入口非法
        return ;
    }
    //3.标记入口点，将入口点入栈
    Mark(maze,entry);
    SeqStactPush(&stack,entry);
    while(1)
    {
        //4.进入循环，获取当前栈的栈顶元素，栈顶元素一定能落脚
        Point cur;
        int ret SeqStactTop(&stack,&cur);
        if(ret == 0)
        {
            //栈为空
            return ;
        }
        //5.判定这个点是否为出口，若是出口，函数返回
        if(IsExit(maze,cur,entry))
        {
            printf("找到了一条路径\n");
            return;
        }
    
        //6.按照顺时针方向取相邻点，判断相邻点是否能落脚，若能就标记，并入栈，立刻进入到下一轮循环
        Point up=cur;
        up.row-=1;
        if(CanStay(maze,up))
        {
            Mark(maze,up);
            SeqStactPush(&stack,up);
            continue;
        }

        Point right=cur;
        right.col+=1;
        if(CanStay(maze,right))
        {
            Mark(maze,right);
            SeqStactPush(&stack,right);
            continue;
        }

        Point down=cur;
        down.row+=1;
        if(CanStay(maze,down))
        {
            Mark(maze,down);
            SeqStactPush(&stack,down);
            continue;
        }

        Point left=cur;
        left.col-=1;
        if(CanStay(maze,left))
        {
            Mark(maze,left);
            SeqStactPush(&stack,left);
            continue;
        }
        //7.若四个相邻点都不能落脚，就出栈当前点，相当于回溯
        SeqStactPop(&stack);
    }
    return;
}
*/

/****
 *
 * 以下为测试代码
 *
 * ****/
#include <stdlib.h>
#define TEST_HEADER printf("\n========%s=========\n",__FUNCTION__)
void TestInit()
{
    TEST_HEADER;
    Maze maze;
    MazeInit(&maze);
    MazePrint(&maze);
}
void TestRound1()
{
    TEST_HEADER;
    Maze maze;
    MazeInit(&maze);
    Point entry={0,1};
    GetPath(&maze,entry);
    MazePrint(&maze);
}

int main()
{
    TestInit();
    TestRound1();
    return 0;
}
