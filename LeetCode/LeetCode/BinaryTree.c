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



//MARK: 99. 恢复二叉搜索树
/*
 https://leetcode-cn.com/problems/recover-binary-search-tree/
 
 */
