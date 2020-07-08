//
//  main.c
//  tree
//
//  Created by Leon.Hwa on 17/4/13.
//  Copyright © 2017年 Leon. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
//#include "AVLTree.h"
#include "ADTTree.h"
#include <math.h>

/*
 前序遍历：根结点 ---> 左子树 ---> 右子树
 中序遍历：左子树---> 根结点 ---> 右子树
 后序遍历：左子树 ---> 右子树 ---> 根结点
*/


void PrintMidOrderTree(SearchTree T);
void FreeTree(SearchTree T);
int* inorderTraversal(struct TreeNode* root, int* returnSize);

struct TreeNode* sortedArrayToBST(int* nums, int numsSize);
struct TreeNode* sortedArrayToBSTHelper(int* nums, int left, int right);

bool isSymmetric(struct TreeNode* root);
bool isSymmetricHelper(struct TreeNode* left, struct TreeNode* right);

int main(int argc, const char * argv[]) {
    // insert code here...
//    printf("Hello, World!\n");
//    int a[] = {2,3,4,5,6,7,8,9};
//    struct TreeNode *tree = sortedArrayToBST(a, 8);
//    PrintMidOrderTree(tree);
//    FreeTree(tree);
    printf("%d \n",reverse(1534236469));
    return 0;
}


/**
 中序遍历：左子树---> 根结点 ---> 右子树
 遍历是升序序列
 */
void
PrintMidOrderTree(SearchTree T){
    if(T != NULL){
        PrintTree(T->left);
        printf("%d \n",T->element);
        PrintTree(T->right);
    }
}
/**
 前序遍历：根结点 ---> 左子树 ---> 右子树
 */
void
PrintPreOrderTree(SearchTree T){
    if(T != NULL){
        printf("%d \n",T->element);
        PrintTree(T->left);
        PrintTree(T->right);
    }
}

/**
 后序遍历：左子树 ---> 右子树 --->  根结点
 */
void
PrintLastOrderTree(SearchTree T){
    if(T != NULL){
        PrintTree(T->left);
        PrintTree(T->right);
        printf("%d \n",T->element);
    }
}


void FreeTree(SearchTree T){
    if(T != NULL){
        FreeTree(T->left);
        FreeTree(T->right);
        printf("free: %d\n",T->element);
        free(T);
    }
}


/*
 二叉树遍历： 迭代
 */


//int* inorderTraversal(struct TreeNode* root, int* returnSize){
//    int *result = (int *)malloc(sizeof(int));
//    while (<#condition#>) {
//        <#statements#>
//    }
//}


//MARK: - 将有序数组转换为二叉搜索树,且高度为1
//https://leetcode-cn.com/problems/convert-sorted-array-to-binary-search-tree/solution/jiang-you-xu-shu-zu-zhuan-huan-wei-er-cha-sou-s-33/
struct TreeNode* sortedArrayToBST(int* nums, int numsSize){
    //因为要使用递归，参数要调整
    return sortedArrayToBSTHelper(nums, 0, numsSize - 1);
}
//关键点是找到中间数
struct TreeNode* sortedArrayToBSTHelper(int* nums, int left, int right){
    if(left > right){
        return NULL;
    }
    int mid = (left + right)/2;
    struct TreeNode *root = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    root->element = nums[mid];
    root->left = sortedArrayToBSTHelper(nums, left, mid - 1);
    root->right = sortedArrayToBSTHelper(nums, mid + 1, right);
    return root;
}



//MARK: - 翻转二叉树
struct TreeNode* invertTree(struct TreeNode* root){
    //递归
    if(root == NULL){
        return NULL;
    }
    TreeNode right = invertTree(root->left);
    TreeNode left =  invertTree(root->right)
    root->left = right;
    root->right = left;
    return root;
}


//MARK: - 镜像二叉树
bool isSymmetric(struct TreeNode* root){
    if(root == NULL){//注意入参
        return true;
    }
    return isSymmetricHelper(root->left, root->right);
}
//使用的是后顺遍历
bool isSymmetricHelper(struct TreeNode* left, struct TreeNode* right){
    if(left == NULL && right == NULL){//都为空时
        return true;
    }
    if((left != NULL && right == NULL) || (left == NULL && right != NULL)){//只有一个为空时
        return false;
    }
    //左右树相等， 对应的节点也想等时才成立
    bool flag = helper(left->left, right->right) && helper(left->right, right->left) ;
    return flag && (left->val == right->val);
}

//MARK: - 相同二叉树
bool isSameTree(struct TreeNode* p, struct TreeNode* q){
    if(p==NULL && q ==NULL){
        return true;
    }
    if((p!=NULL && q ==NULL) || (p==NULL && q !=NULL)){
        return false;
    }
    return isSameTree(p->left, q->left) && isSameTree(p->right, q->right) && (p->val == q->val);
}
