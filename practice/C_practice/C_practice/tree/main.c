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
#include "Stack.h"


/*
 前序遍历：根结点 ---> 左子树 ---> 右子树
 中序遍历：左子树---> 根结点 ---> 右子树
 后序遍历：左子树 ---> 右子树 ---> 根结点
*/

void PrintMidOrderTree(SearchTree T);
void FreeTree(SearchTree T);
int* inorderTraversal(struct TreeNode* root, int* returnSize);
struct TreeNode* upsidedownTree(struct TreeNode* root);
struct TreeNode* sortedArrayToBST(int* nums, int numsSize);
struct TreeNode* sortedArrayToBSTHelper(int* nums, int left, int right);

int isSymmetric(struct TreeNode* root);
int isSymmetricHelper(struct TreeNode* left, struct TreeNode* right);

int main(int argc, const char * argv[]) {
    // insert code here...
//    printf("Hello, World!\n");
//    int a[] = {2,3,4,5,6,7,8,9};
//    struct TreeNode *tree = sortedArrayToBST(a, 8);
//    PrintMidOrderTree(tree);
//    FreeTree(tree);
    return 0;
}
struct TreeNode* invertTree2(struct TreeNode* root);
struct TreeNode* invertTree2(struct TreeNode* root){
    if(root == NULL){
        return NULL;
    }
    struct TreeNode * left = invertTree2(root->left);
    struct TreeNode * right = invertTree2(root->right);
    root->left = right;
    root->right = left;
    return root;
}


//MARK: -中序遍历：左子树---> 根结点 ---> 右子树
// 遍历是升序序列
void
PrintMidOrderTree(SearchTree T){
    if(T != NULL){
        PrintMidOrderTree(T->left);
        printf("%d \n",T->element);
        PrintMidOrderTree(T->right);
    }
}

//MARK: - 迭代中序遍历
//左-中-右 
int* inorderTraversal(struct TreeNode* root, int* returnSize){
    if (root == NULL) {
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
               result[cur-1] = node->element;
               root = node->right;
           }
       }
       free(stack);
       *returnSize = cur;
       return result;
}

//MARK: - 前序遍历：根结点 ---> 左子树 ---> 右子树
void
PrintPreOrderTree(SearchTree T){
    if(T != NULL){
        printf("%d \n",T->element);
        PrintPreOrderTree(T->left);
        PrintPreOrderTree(T->right);
    }
}


//MARK: -后序遍历：左子树 ---> 右子树 --->  根结点
void
PrintLastOrderTree(SearchTree T){
    if(T != NULL){
        PrintLastOrderTree(T->left);
        PrintLastOrderTree(T->right);
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
    struct TreeNode *right = invertTree(root->left);
    struct TreeNode *left =  invertTree(root->right);
    root->left = right;
    root->right = left;
    return root;
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

//MARK: - 镜像二叉树
int isSymmetric(struct TreeNode* root){
    if(root == NULL){//注意入参
        return 1;
    }
    return isSymmetricHelper(root->left, root->right);
}
//使用的是后顺遍历
int isSymmetricHelper(struct TreeNode* left, struct TreeNode* right){
    if(left == NULL && right == NULL){//都为空时
        return 1;
    }
    if((left != NULL && right == NULL) || (left == NULL && right != NULL)){//只有一个为空时
        return -1;
    }
    // （当前左节点，当前右节点）（左节点左数，右节点右数）（左节点右数，右节点左数对比）
    int flag = isSymmetricHelper(left->left, right->right) && isSymmetricHelper(left->right, right->left) ;
    return flag && (left->element == right->element);
}

//MARK: - 相同二叉树
int isSameTree(struct TreeNode* p, struct TreeNode* q){
    if(p==NULL && q ==NULL){
        return 1;
    }
    if((p!=NULL && q ==NULL) || (p==NULL && q !=NULL)){
        return -1;
    }
    return isSameTree(p->left, q->left) && isSameTree(p->right, q->right) && (p->element == q->element);
}
