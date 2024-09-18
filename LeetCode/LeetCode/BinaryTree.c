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
            result = realloc(result,sizeof(int) * (++cur));
            result[cur-1] = root->val;
            //2.左树入栈
            //栈扩容
            stack = realloc(stack,sizeof(struct ListNode *) * (++stk_top));
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

//MARK: 二叉树的后序遍历 -- 需要反转数组
int* postorderTraversal(struct TreeNode* root, int* returnSize){
    // 后序遍历：左 右 中
    //dfs
    if(root == NULL) {
        *returnSize = 0;
        return NULL;
    }

    int *res = malloc(0);
    int cur = 0;
    // 法一： 层序遍历 中 右 左。 然后逆序即可
//    struct TreeNode **stack = malloc(sizeof(struct TreeNode *));
//    stack[0] = root;
//    int stk_top = 1;
//    while(stk_top > 0){
//        struct TreeNode *node =  stack[--stk_top];
//        res = realloc(res, sizeof(int) * (++cur));
//        res[cur - 1] = node->val;
//        if(node->left != NULL){
//            stack = realloc(stack, sizeof(struct TreeNode *) * (++stk_top));
//            stack[stk_top - 1] = node->left;
//        }
//        if(node->right != NULL){
//            stack = realloc(stack, sizeof(struct TreeNode *) * (++stk_top));
//            stack[stk_top - 1] = node->right;
//        }
//    }
//      *returnSize = cur;
    
    // 法二：dfs 遍历中 右 左 再反向输出
//    struct TreeNode **stack = malloc(0);
//    int stk_top = 0;
//    while (stk_top > 0 || root) {
//        if (root) {
//            stack = realloc(stack, sizeof(struct TreeNode *) * (++stk_top));
//            stack[stk_top - 1] = root;
//            res = realloc(res, sizeof(int) * (++cur));
//            res[cur - 1] = root->val;
//            root = root->right;
//        } else {
//            struct TreeNode *node = stack[--stk_top];
//            root = node->left;
//        }
//    }
//
//    *returnSize = cur;
//    //后反转数组
//    for(int i = 0; i <= cur/2 - 1; i++){
//        int temp = res[i];
//        res[i] = res[cur - i - 1];
//        res[cur - i - 1] = temp;
//    }
    
    // 法三：
        struct TreeNode **stack = malloc(0);
        int stk_top = 0;
        struct TreeNode *preVisited = NULL;
        while (stk_top > 0 || root) {
            if (root) {//一直遍历左子树
                stack = realloc(stack, sizeof(struct TreeNode *) * (++stk_top));
                stack[stk_top - 1] = root;
                root = root->left;
            } else {
                struct TreeNode *node = stack[stk_top-1];//先不移出栈
                if (node->right && node->right != preVisited) { //有右节点的话 并且上一个不是右节点，处理右节点
                    /* 这里需要注意， 防止出现死循环
                        O1
                         \\
                           O2
                     */
//                    stack = realloc(stack, sizeof(struct TreeNode *) * (++stk_top));
                    root = node->right;
                } else {
                    stk_top--; //出栈
                    res = realloc(res, sizeof(int) * (++cur));
                    res[cur - 1] = node->val;
                    preVisited = node;
                }
            }
        }
    *returnSize = cur;
    return res;
}



//MARK: -上下反转二叉树
/*
      1              4
     / \            / \
    2   3    ==>    5   2
   / \                 / \
  4   5               3   1
 */
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

// MARK: - 判断对称二叉树
// https://leetcode.cn/problems/dui-cheng-de-er-cha-shu-lcof/description/
bool helper(struct TreeNode* left, struct TreeNode* right){
    if(left == NULL && right ==NULL){
        return true;
    }
    if(left == NULL || right == NULL){
        return false;
    }
    return (left->val == right->val) && helper(left->left, right->right) && helper(left->right, right->left);
}

bool isSymmetric(struct TreeNode* root){
   if(root == NULL){
       return true;
   }
   return helper(root->left, root->right);
}


//MARK: 99. 恢复二叉搜索树
/*
 https://leetcode-cn.com/problems/recover-binary-search-tree/
 二叉搜索树中的两个节点被错误地交换。
 请在不改变其结构的情况下，恢复这棵树。
 
 对于二叉搜索树，【中序遍历】的值是由小到大排序好的。被错误地交换，相当于排序出错了，只有找到排序出错的两个位置，再进行交换即可第二个shi
 如果有两个位置错误交换的话，第一个肯定是大的值，这个值本来是在后面的。 第二个是小的值，这个值本来是在前面的。
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

void check(struct TreeNode* node){
    if (pre != NULL && pre->val > node->val) {
        //第二个是较小的值
        second = node;
        if(first != NULL) return;
        //第一个是较大的值，
        first = pre;
    }
    pre = node;
}
void findWrongTree(struct TreeNode* root){
    if (root == NULL) {
        return;
    }
    findWrongTree(root->left);
    check(root);
    findWrongTree(root->right);
}


//迭代法
void recoverTree2(struct TreeNode* root){
    struct TreeNode **stack = malloc(0);
    int stk_top = 0;
    while (root != NULL || stk_top != 0) {
        if (root) {
            stk_top++;
            stack = realloc(stack, sizeof(struct TreeNode *) * stk_top);
            stack[stk_top-1] = root;
            root = root->left;
        }else{
            struct TreeNode * node = stack[stk_top-1];
            if (pre != NULL && pre->val > node->val) {
                second = node;
                if (first == NULL) {
                    first = pre;
                }
            }
            pre = node;
            root = node->right;
            free(node);
        }
    }
    int temp = first->val;
    first->val = second->val;
    second->val = temp;
    free(stack);
}


//MARK: 面试题 04.05. 合法二叉搜索树
/*
 https://leetcode-cn.com/problems/legal-binary-search-tree-lcci/
 输入:
  5
 / \
1   4
   / \
  3   6
输出: false
 注意3和5.
 root要和左树的最大值，右数的最小值对比
 */
bool isValidBST(struct TreeNode* root){
    if(root == NULL){
        return true;
    }
    struct TreeNode* leftMaxNode = root->left;
    struct TreeNode* rightMinNode = root->right;
    while(leftMaxNode && leftMaxNode->right != NULL){
        leftMaxNode = leftMaxNode->right;
    }
    while(rightMinNode && rightMinNode->left != NULL){
        rightMinNode = rightMinNode->left;
    }
    bool leftFix = true;
    bool rightFix = true;
    if(leftMaxNode && leftMaxNode->val >= root->val){
        leftFix = false;
    }
    if(rightMinNode && rightMinNode->val <= root->val){
        rightFix = false;
    }
    return leftFix && rightFix && isValidBST(root->left) && isValidBST(root->right);
}

//MARK: 572. 另一个树的子树
/*
 https://leetcode-cn.com/problems/subtree-of-another-tree
 给定两个非空二叉树 s 和 t，检验 s 中是否包含和 t 具有相同结构和节点值的子树。s 的一个子树包括 s 的一个节点和这个节点的所有子孙。s 也可以看做它自身的一棵子树。
 
示例 1:
给定的树 s:
 
     3
    / \
   4   5
  / \
 1   2
 
给定的树 t：
 
   4
  / \
 1   2
 */
bool isSameTree(struct TreeNode* l, struct TreeNode* r);
bool isSubtree(struct TreeNode* s, struct TreeNode* t){
    if(t == NULL) return true;
    if(s == NULL) return false;
    
    struct TreeNode **stack = malloc(0);
    int stk_top = 0;
    //前序遍历找到和t根节点相同的节点
    struct TreeNode* head  =s;
    //先中序列便利找到s中的一个节点和t的根节点相同的节点
    while (stk_top != 0 || head != NULL) {
        if (head) {
            stk_top++;
            stack = realloc(stack, sizeof(struct TreeNode *) * stk_top);
            stack[stk_top-1] = head;
            //因为s中可能有多个节点和t是一样的，一找到就要便利一次直到找到了才返回
            if (isSameTree(head, t)) {
                return true;
            }
            head = head->left;
        }else{
            struct TreeNode* node = stack[--stk_top];
            head = node->right;
        }
    }
    return false;
}

bool isSameTree(struct TreeNode* l, struct TreeNode* r){
    if (l == NULL && r == NULL) {
        return true;
    }
    if (l == NULL || r== NULL) {
        return false;
    }
    return l->val == r->val && isSameTree(l->left, r->left) && isSameTree(l->right, r->right);
}

//MARK: 114. 二叉树展开为链表
/*https://leetcode-cn.com/problems/flatten-binary-tree-to-linked-list
 例如，给定二叉树
 
     1
    / \
   2   5
  / \   \
 3   4   6
 将其展开为：
 
1
 \
  2
   \
    3
     \
      4
       \
        5
         \
          6
 */
struct TreeNode* helper(struct TreeNode* root){
    if(root != NULL){
        struct TreeNode* left = helper(root->left);
        struct TreeNode* right = helper(root->right);
        root->left = NULL;
        if(left != NULL){
            root->right = left;
            //找到left最右边的位置
            while(left->right != NULL){
                left = left->right;
            }
            left->right = right;
        }
    }
    return root;
}

void flatten(struct TreeNode* root){
    if(root == NULL){
        return;
    }
    helper(root);
}
//法二： 前序遍历后把节点放在数组中， 再一个拼接起来


