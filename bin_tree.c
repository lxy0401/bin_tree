#include "bin_tree.h"
#include <stdio.h>
#include <stdlib.h>
//对于链表来说，使用链表对头节点的指针表示一个链表
//对于我们的二叉树来说，使用根节点来表示一个树

void TreeInit(TreeNode** pRoot)
{
    if(pRoot == NULL)
    {
        //非法输入
        return ;
    }
    *pRoot = NULL;
    return;
}


/*****
 *
 *以下为测试代码
 *
 *
 * *****/
#if 1
#include <stdio.h>
#define TEST_HEADER printf("\n========%s=========\n",__FUNCTION__)
void TestInit()
{
    TEST_HEADER;
    TreeNode* root;
    TreeInit(&root);
    printf("ret expected NULL,actual %p\n",root);
}
int main()
{
    TestInit();
    return 0;
}
#endif
