//
//  BinaryTree.c
//  LeetCode
//
//  Created by huayf on 2020/8/24.
//  Copyright © 2020 leon. All rights reserved.
//

#include <stdio.h>
#include "LeetCode.h"

//MARK: 236. 二叉树的最近公共祖先
/*
 首先肯定是中序遍历
 前置条件： root不为空
 状态转移：
 找到了节点 返回该节点，没有找到返回空（到了尽头）
 */
struct TreeNode* lowestCommonAncestor(struct TreeNode* root, struct TreeNode* p, struct TreeNode* q) {
    if(root == NULL) return NULL; //该分支没有找到，或者根节点为空
    if (root == p || root == q) {//找到了
        return root;
    }
    struct TreeNode *left = lowestCommonAncestor(root->left, p, q);
    struct TreeNode *right = lowestCommonAncestor(root->right, p, q);
    if (left && right) {//子节点都返回值 说明都找到了， 现在的节点就是最近的节点
        return root;
    }
    //只找到了一个返回 找到的那一个
    return left != NULL ? left : right;
}


//MARK: - 迭代中序遍历
//左-中-右
int* inorderTraversal(struct TreeNode* root, int* returnSize){
    if (root == NULL) {
           *returnSize = 0;
           return NULL;
       }
       //建立一个指向 TreeNode *类型的可变数组，用来充当栈的功能
       struct TreeNode **stack = (struct TreeNode **)malloc(0);
       //当前数组的容量， 也就是栈顶的位置
       int stk_top = 0;
       
       //可变数组
       int cur = 0;
       int *result = (int *)malloc(0);
       while (stk_top != 0 || root != NULL) {
           if(root) {//便利左树
               //栈扩容
               stk_top++;
               stack = realloc(stack, sizeof(struct TreeNode *) * stk_top);
               
               stack[stk_top-1] = root;
               root =  root->left;
           }else{//当前节点为空，说明左边走到头了，从栈中弹出节点并保存，然后转向右边节点，继续上面整个过程
               struct TreeNode *node = stack[--stk_top];
               //数组扩容
               cur++;
               result = realloc(result, sizeof(int) * cur);
               
               result[cur-1] = node->val;
               root = node->right;
               free(node);
           }
       }
       free(stack);
       *returnSize = cur;
       return result;
}

//MARK:二叉树前序遍历
int* preorderTraversal(struct TreeNode* root, int* returnSize){
    if (root == NULL) {
        *returnSize = 0;
        return NULL;
    }
    //栈
    int stk_top = 0;
    struct TreeNode **stack = (struct TreeNode **)malloc(0);
    
    //数组
    int cur = 0;
    int *result = (int *)malloc(0);
    
    while (stk_top != 0 || root) {
        if (root) {
            //1.存入数组
            //数组扩容
            cur++;
            result = realloc(result,sizeof(int) * cur);
            result[cur-1] = root->val;
            //2.左树入栈
            //栈扩容
            stk_top++;
            stack = realloc(stack,sizeof(struct ListNode *) * stk_top);
            stack[stk_top-1] = root;
            root = root->left;
        }else{
            struct TreeNode *node = stack[--stk_top];
            root = node->right;
            free(node);
        }
    }
    
    free(stack);
    *returnSize = cur;
    return result;
}

//MARK: -上下反转二叉树
//和递归翻转链表类似
struct TreeNode* upsidedownTree(struct TreeNode* root){
    if(root == NULL || root->left == NULL){
        return root;//排除空树，或者返回最左数
    }
    struct TreeNode *leftChild = root->left;//默认
    struct TreeNode *rightChild = root->right;
    struct TreeNode* last =  upsidedownTree(root->left);//我始终是最后一个左树
    
    leftChild->left = rightChild;
    leftChild->right = root;
    //防止如果root是最右节点，这里需要置空，防止双向引用
    root->left = NULL;
    root->right = NULL;
    return last;
}


//MARK: 99. 恢复二叉搜索树
/*
 https://leetcode-cn.com/problems/recover-binary-search-tree/
 二叉搜索树中的两个节点被错误地交换。
 请在不改变其结构的情况下，恢复这棵树。
 
 对于二叉搜索树，中序遍历的值是由小到大排序好的。被错误地交换，相当于排序出错了，只有找到排序出错的两个位置，再进行交换即可
 */
struct TreeNode* first;
struct TreeNode* second;
struct TreeNode* pre;
void findWrongTree(struct TreeNode* root);
void check(struct TreeNode* root);



//递归法
void recoverTree(struct TreeNode* root){
    findWrongTree(root);
    int temp = first->val;
    first->val = second->val;
    second->val = temp;
}

void check(struct TreeNode* root){
    if (pre != NULL && pre->val > root->val) {
        second = root;
        if(first != NULL) return;
        first = pre;
    }
    pre = root;
}
void findWrongTree(struct TreeNode* root){
    if (root == NULL) {
        return;
    }
    findWrongTree(root->left);
    check(root);
    findWrongTree(root->right);
}
