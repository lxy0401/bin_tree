#include "bin_tree.h"
#include "seqqueue.h"
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

TreeNode* CreateTreeNode(TreeNodeType value)
{
    TreeNode* new_node=(TreeNode*)malloc(sizeof(TreeNode));
    new_node->data=value;
    new_node->lchild=NULL;
    new_node->rchild=NULL;
    return new_node;
}

void DestroyTreeNode(TreeNode* root)
{
    free(root);
    return ;
}

//先序遍历树
void TreePreOrder(TreeNode* root)
{
    if(root == NULL)
    {
        //空树
        return ;
    }
    //先访问根节点
    printf("%c",root->data);
    //遍历左子树
    TreePreOrder(root->lchild);
    //遍历右子树
    TreePreOrder(root->rchild);
    return ;
}

//中序遍历树
void TreeInOrder(TreeNode* root)
{
    if(root == NULL)
    {
        //空树
        return ;
    }
    //遍历左子树
    TreeInOrder(root->lchild); 
    //先访问根节点
    printf("%c",root->data);
    //遍历右子树
    TreeInOrder(root->rchild);
    return ;
}


//后序遍历树
void TreePostOrder(TreeNode* root)
{
    if(root == NULL)
    {
        //空树
        return ;
    }
    //遍历左子树
    TreePostOrder(root->lchild); 
    //遍历右子树
    TreePostOrder(root->rchild);
    //先访问根节点
    printf("%c",root->data);
    return ;
}

//层序遍历树
void TreeLevelOrder(TreeNode* root)
{
    if(root == NULL)
    {
        //空树
        return ;
    }
   SeqQueue queue;
   SeqQueueInit(&queue);
   SeqQueuePush(&queue,root);
   while(1)
   {
       SeqQueueType front;
       int ret=SeqQueueFront(&queue,&front);
       if(ret = 0)
       {
           //取队首元素失败，说明队列为空
           break;
       }
       //打印当前值，把当前对手元素出队列
       printf("%c",front->data);
       SeqQueuePop(&queue);
       //把当前左右子树入队列
       if(front->lchild!=NULL)
       {
           SeqQueuePush(&queue,front->lchild);
       }
       if(front->rchild!=NULL)
       {
           SeqQueuePush(&queue,front->rchild);
       }
       //printf("\n");
   }
   printf("\n");
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

void TestPreOrder()
{
    TEST_HEADER;
    TreeNode* a=CreateTreeNode('a');
    TreeNode* b=CreateTreeNode('b');
    TreeNode* c=CreateTreeNode('c');
    TreeNode* d=CreateTreeNode('d');
    TreeNode* e=CreateTreeNode('e');
    TreeNode* f=CreateTreeNode('f');
    TreeNode* g=CreateTreeNode('g');
    a->lchild=b;
    a->rchild=c;
    b->lchild=d;
    b->rchild=e;
    e->lchild=g;
    c->rchild=f;
    TreePreOrder(a);
    printf("\n");
}


void TestInOrder()
{
    TEST_HEADER;
    TreeNode* a=CreateTreeNode('a');
    TreeNode* b=CreateTreeNode('b');
    TreeNode* c=CreateTreeNode('c');
    TreeNode* d=CreateTreeNode('d');
    TreeNode* e=CreateTreeNode('e');
    TreeNode* f=CreateTreeNode('f');
    TreeNode* g=CreateTreeNode('g');
    a->lchild=b;
    a->rchild=c;
    b->lchild=d;
    b->rchild=e;
    e->lchild=g;
    c->rchild=f;
    TreeInOrder(a);
    printf("\n");
}


void TestPostOrder()
{
    TEST_HEADER;
    TreeNode* a=CreateTreeNode('a');
    TreeNode* b=CreateTreeNode('b');
    TreeNode* c=CreateTreeNode('c');
    TreeNode* d=CreateTreeNode('d');
    TreeNode* e=CreateTreeNode('e');
    TreeNode* f=CreateTreeNode('f');
    TreeNode* g=CreateTreeNode('g');
    a->lchild=b;
    a->rchild=c;
    b->lchild=d;
    b->rchild=e;
    e->lchild=g;
    c->rchild=f;
    TreePostOrder(a);
    printf("\n");
}

void TestLevelOrder()
{
    TEST_HEADER;
    TreeNode* a=CreateTreeNode('a');
    TreeNode* b=CreateTreeNode('b');
    TreeNode* c=CreateTreeNode('c');
    TreeNode* d=CreateTreeNode('d');
    TreeNode* e=CreateTreeNode('e');
    TreeNode* f=CreateTreeNode('f');
    TreeNode* g=CreateTreeNode('g');
    a->lchild=b;
    a->rchild=c;
    b->lchild=d;
    b->rchild=e;
    e->lchild=g;
    c->rchild=f;
    TreeLevelOrder(a);
    printf("\n");
}
int main()
{
    TestInit();
    TestPreOrder();
    TestInOrder();
    TestPostOrder();
    //TestLevelOrder();
    return 0;
}
#endif
