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
int main()
{
    TestInit();
    return 0;
}
