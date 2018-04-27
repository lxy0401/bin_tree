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

//还原一棵树
//输入一个数组（数组对每个元素就是树上对节点）
//根据数组内容，构建出一棵树，数组中元素内容符合树对先序遍历结果
/////
//辅助递归函数
TreeNode* _TreeCreate(TreeNodeType data[],size_t size,size_t* index,TreeNodeType null_node)
{
    if(index == NULL)
    {
        //非法输入
        return NULL;
    }
    if(*index >= size)
    {
        //数组遍历结束
        return NULL;
    }
    if(data[*index] == null_node)
    {
        //空树
        return NULL;
    }
    TreeNode* new_node=CreateTreeNode(data[*index]);
    //先
    new_node->lchild=_TreeCreate(data,size,index,null_node);
    //后
    new_node->rchild=_TreeCreate(data,size,index,null_node);
    return new_node;
}
TreeNode* TreeCreate(TreeNodeType data[] ,size_t size,char null_node)
{
    //1.根据index指向对元素内容创建一个节点
    //2.先++index后递归的构架新的节点对左子树
    //3.再++index后递归的构架新的节点对右子树
    size_t index=0;//表示当前取数组中对那个元素
    return _TreeCreate(data,size,&index,null_node);//辅助完成递归
}


//树对拷贝
TreeNode* TreeClone(TreeNode* root)
{
    if(root == NULL)
    {
        //空树
        return NULL;
    }
    //按照先序方式遍历
    TreeNode* new_node=CreateTreeNode(root->data);
    new_node->lchild=TreeClone(root->lchild);
    new_node->rchild=TreeClone(root->rchild);
    return new_node;
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

void TestCreate()
{
    TEST_HEADER;
    TreeNodeType data[]="adb##eg###c#f##";
    TreeNode* root=TreeCreate(data,(sizeof(data)/sizeof(data[0]))-1,'#');
    printf("\n");
    TreePreOrder(root);
    TreeInOrder(root);
    TreePostOrder(root);
    //TreeLevelOrder(root);
    printf("\n");
}

int main()
{
    TestInit();
    TestPreOrder();
    TestInOrder();
    TestPostOrder();
    //TestLevelOrder();
    TestCreate();
    return 0;
}
#endif
