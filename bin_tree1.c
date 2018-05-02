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
   TreeNode* cur=NULL;
   while(SeqQueueFront(&queue,&cur))
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
   }
   printf("\n");
}

//还原一棵树
//输入一个数组（数组对每个元素就是树上对节点）
//根据数组内容，构建出一棵树，数组中元素内容符合树对先序遍历结果

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
    ++(*index);
    new_node->lchild=_TreeCreate(data,size,index,null_node);
    //后
    ++(*index);
    new_node->rchild=_TreeCreate(data,size,index,null_node);
    return new_node;
}
TreeNode* TreeCreate(TreeNodeType data[] ,size_t size,char null_node)
{
    //1.根据index指向对元素内容创建一个节点
    //2.先++index后递归的构架新的节点的左子树
    //3.再++index后递归的构架新的节点的右子树
    size_t index=0;//表示当前取数组中的那个元素
    return _TreeCreate(data,size,&index,null_node);//辅助完成递归
}


//树的拷贝
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

//二叉树的销毁
void TreeDestroy(TreeNode* root)
{
    if(root == NULL)
    {
        //空树
        return;
    }
    //按照后序遍历的方式销毁树
    TreeNode* lchild=root->lchild;
    TreeNode* rchild=root->rchild;
    TreeDestroy(root->lchild);
    TreeDestroy(root->rchild);
    DestroyTreeNode(root);
    return;
}

//求二叉树节点个数(方法一)
void _TreeSize(TreeNode* root,size_t* size)
{
    if(root == NULL)
    {
        //空树
        return ;
    }
    ++(*size);
    _TreeSize(root->lchild,size);
    _TreeSize(root->rchild,size);
}

size_t TreeSize1(TreeNode* root)
{
    size_t size=0;
    //运用_TreeSize来辅助完成递归
    _TreeSize(root,&size);
    return size;
}

//求二叉树节点个数（方法二）
//直接采用递归对方法，不如方法一那么直观，但是代码很简单
size_t TreeSize2(TreeNode* root)
{
    if(root == NULL)
    {
        //空树
        return 0;
    }
    return 1+TreeSize2(root->lchild)+TreeSize2(root->rchild);
}

//求二叉树叶子节点个数
size_t TreeLeafSize(TreeNode* root)
{
    if(root == NULL)
    {
        //空树
        return 0;
    }
    if(root->lchild == NULL && root->rchild == NULL)
    {
        //root是叶子节点
        return 1;
    }
    //root不是叶子节点
    //采用递归的方式
    //叶子节点的个数=左子树叶子节点+右字数叶子节点
    return TreeLeafSize(root->lchild)+TreeLeafSize(root->rchild);
}

//求二叉树第K层节点的个数
//采用递归的方法
size_t TreeKLevelSize(TreeNode* root,int k)
{
    if(root == NULL || k<1)
    {
        //非法操作
        return 0;
    }
    if(k == 1)
    {
        return 1;
    }
    return TreeKLevelSize(root->lchild,k-1)+TreeKLevelSize(root->rchild,k-1);
}

//求二叉树的高度
size_t TreeHeight(TreeNode* root)
{
    if(root == NULL)
    {
        //空树
        return 0;
    }
    size_t lheight=TreeHeight(root->lchild);
    size_t rheight=TreeHeight(root->rchild);
    return 1+(lheight>rheight?lheight:rheight);
}

//在二叉树中查找节点，给定一个数值求出对应对指针
//假设二叉树中的节点不重复
TreeNode* TreeFind(TreeNode* root,TreeNodeType to_find)
{
    if(root == NULL)
    {
        //空树
        return NULL;
    }
    if(root->data == to_find)
    {
        return root;
    }
    TreeNode* lresult=TreeFind(root->lchild,to_find);
    TreeNode* rresult=TreeFind(root->rchild,to_find);
    return lresult!=NULL?lresult:rresult;
}

//求出当前节点的父节点
TreeNode* TreeParent(TreeNode* root,TreeNode* child)
{
    if(root == NULL || child == NULL)
    {
        //空树||非法输入
        return NULL;
    }
    if(root->lchild == child || root->rchild == child)
    {
        return root;
    }
    TreeNode* lresult=TreeParent(root->lchild,child);
    TreeNode* rresult=TreeParent(root->rchild,child);
    return lresult!=NULL?lresult:rresult;
}

//返回当前节点的左右子树
TreeNode* TreeLChild(TreeNode* node)
{
    if(node == NULL)
    {
        return NULL;
    }
    return node->lchild;
}

TreeNode* TreeRChild(TreeNode* node)
{
    if(node == NULL)
    {
        return NULL;
    }
    return node->rchild;
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
    TreeNodeType data[]="abd##eg###c#f##";
    TreeNode* root=TreeCreate(data,(sizeof(data)/sizeof(data[0]))-1,'#');
    printf("\n");
    TreePreOrder(root);
    printf("\n");
    TreeInOrder(root);
    printf("\n");
    TreePostOrder(root);
    printf("\n");
    TreeLevelOrder(root);
    printf("\n");
}

void TestClone()
{

    TEST_HEADER;
    TreeNodeType data[]="abd##eg###c#f##";
    TreeNode* root=TreeCreate(data,(sizeof(data)/sizeof(data[0]))-1,'#');
    TreeNode* new_root=TreeClone(root);
    printf("\n");
    TreePreOrder(new_root);
    printf("\n");
    TreeInOrder(new_root);
    printf("\n");
    TreePostOrder(new_root);
    printf("\n");
    TreeLevelOrder(new_root);
    printf("\n");
}

void TestDestroy()
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
    TreeDestroy(a);
    return ;
}

void TestSize1()
{
    TEST_HEADER;
    TreeNodeType data[]="abd##eg###c#f##";
    TreeNode* root=TreeCreate(data,(sizeof(data)/sizeof(data[0]))-1,'#');
    size_t size=TreeSize1(root);
    printf("Size expected 7,actual %lu\n",size);
}

void TestSize2()
{
    TEST_HEADER;
    TreeNodeType data[]="abd##eg###c#f##";
    TreeNode* root=TreeCreate(data,(sizeof(data)/sizeof(data[0]))-1,'#');
    size_t size=TreeSize2(root);
    printf("Size expected 7,actual %lu\n",size);
}

void TestLeafSize()
{

    TEST_HEADER;
    TreeNodeType data[]="abd##eg###c#f##";
    TreeNode* root=TreeCreate(data,(sizeof(data)/sizeof(data[0]))-1,'#');
    size_t size=TreeLeafSize(root);
    printf("Size expected 3,actual %lu\n",size);
}

void TestKLevelSize()
{
    TEST_HEADER;
    TreeNodeType data[]="abd##eg###c#f##";
    TreeNode* root=TreeCreate(data,(sizeof(data)/sizeof(data[0]))-1,'#');
    size_t size=TreeKLevelSize(root,3);
    printf("Size expected 3,actual %lu\n",size);
}

void TestHeight()
{
    TEST_HEADER;
    TreeNodeType data[]="abd##eg###c#f##";
    TreeNode* root=TreeCreate(data,(sizeof(data)/sizeof(data[0]))-1,'#');
    size_t size=TreeHeight(root);
    printf("Height expected 4,actual %lu\n",size);
}

void TestFind()
{
    TEST_HEADER;
    TreeNodeType data[]="abd##eg###c#f##";
    TreeNode* root=TreeCreate(data,(sizeof(data)/sizeof(data[0]))-1,'#');
    TreeNode* result=TreeFind(root,'e');
    printf("result expected %p,actual %p\n",root->lchild->rchild,result);
}

void TestParent()
{
    TEST_HEADER;
    TreeNodeType data[]="abd##eg###c#f##";
    TreeNode* root=TreeCreate(data,(sizeof(data)/sizeof(data[0]))-1,'#');
    TreeNode* parent=TreeFind(root,'g');
    printf("result expected e,actual %p\n",parent);
}
int main()
{
    TestInit();
    TestPreOrder();
    TestInOrder();
    TestPostOrder();
    TestLevelOrder();
    TestCreate();
    TestClone();
    TestDestroy();
    TestSize1();
    TestSize2();
    TestLeafSize();
    TestKLevelSize();
    TestHeight();
    TestFind();
    TestParent();
    return 0;
}
#endif
