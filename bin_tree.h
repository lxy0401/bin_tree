#pragma once
typedef char TreeNodeType;
typedef struct TreeNode
{
    TreeNodeType data;
    struct TreeNode* lchild;
    struct TreeNode* rchild;
}TreeNode;

//对于链表来说，使用链表对头节点的指针表示一个链表
//对于我们的二叉树来说，使用根节点来表示一个树

void TreeInit(TreeNode** pRoot);
