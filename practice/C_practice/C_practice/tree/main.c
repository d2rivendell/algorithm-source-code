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
void PrintTree(SearchTree T);
void FreeTree(SearchTree T);
int* inorderTraversal(struct TreeNode* root, int* returnSize);

struct TreeNode* sortedArrayToBST(int* nums, int numsSize);
struct TreeNode* helper(int* nums, int left, int right);

int main(int argc, const char * argv[]) {
    // insert code here...
//    printf("Hello, World!\n");
//    int a[] = {2,3,4,5,6,7,8,9};
//    struct TreeNode *tree = sortedArrayToBST(a, 8);
//    PrintTree(tree);
//    FreeTree(tree);
    printf("%d \n",reverse(1534236469));
    return 0;
}


/**
 中序遍历：先遍历左树再遍历右树
 遍历是升序序列
 */
void
PrintTree(SearchTree T){
    if(T != NULL){
        PrintTree(T->left);
        printf("%d \n",T->element);
        PrintTree(T->right);
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

//将有序数组转换为二叉搜索树,且高度为1
//https://leetcode-cn.com/problems/convert-sorted-array-to-binary-search-tree/solution/jiang-you-xu-shu-zu-zhuan-huan-wei-er-cha-sou-s-33/
struct TreeNode* sortedArrayToBST(int* nums, int numsSize){
    //因为要使用递归，参数要调整
    return helper(nums, 0, numsSize - 1);
}
//关键点是找到中间数
struct TreeNode* helper(int* nums, int left, int right){
    if(left > right){
        return NULL;
    }
    int mid = (left + right)/2;
    struct TreeNode *root = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    root->element = nums[mid];
    root->left = helper(nums, left, mid - 1);
    root->right = helper(nums, mid + 1, right);
    return root;
}
