#pragma once
#include "seqqueue.h"
typedef char TreeNodeType;
typedef struct TreeNode
{
    TreeNodeType data;
    struct TreeNode* lchild;
    struct TreeNode* rchild;
}TreeNode;

//对于链表来说，使用链表对头节点的指针表示一个链表
//对于我们的二叉树来说，使用根节点来表示一个树

//二叉树初始化
void TreeInit(TreeNode** pRoot);

//先序遍历树
void TreePreOrder(TreeNode* root);

//中序遍历树
void TreeInOrder(TreeNode* root);

//后序遍历树
void TreePostOrder(TreeNode* root);

//层序遍历树
void TreeLevelOrder(TreeNode* root);

//还原一棵树
//输入一个数组（数组对每个元素就是树上对节点）
//根据数组内容，构建出一棵树，数组中元素内容符合树对先序遍历结果
TreeNode* TreeCreate(TreeNodeType data[] ,size_t size,char null_node);

//树对拷贝
TreeNode* TreeClone(TreeNode* root);

//二叉树对销毁
void TreeDestroy(TreeNode* root);

//求二叉树节点个数(方法一)
void _TreeSize(TreeNode* root,size_t* size);

//求二叉树节点个数（方法二）
//直接采用递归对方法，不如方法一那么直观，但是代码很简单
size_t TreeSize2(TreeNode* root);

//求二叉树叶子节点个数
size_t TreeLeafSize(TreeNode* root);

//求二叉树第K层节点对个数
//采用递归对方法
size_t TreeKLevelSize(TreeNode* root,int k);

//求二叉树对高度
size_t TreeHeight(TreeNode* root);

//在二叉树中查找节点，给定一个数值求出对应对指针
//假设二叉树中的节点不重复
TreeNode* TreeFind(TreeNode* root,TreeNodeType to_find);

//求出当前节点的父节点
TreeNode* TreeParent(TreeNode* root,TreeNode* child);

//返回当前节点的左右子树
TreeNode* TreeLChild(TreeNode* node);
TreeNode* TreeRChild(TreeNode* node);
