//
//  AVLTree.c
//  tree
//
//  Created by leon on 2017/12/6.
//  Copyright © 2017年 Leon. All rights reserved.
//

#include "AVLTree.h"
#include <stdlib.h>
#define AVL_MAX(A,B) A > B ? A:B
struct AvlNode{
    AvlElementType element;
    int height;
    AvlTree left;
    AvlTree right;
};

AvlPosition
Avl_Find(AvlElementType X,AvlTree T){
    if(T == NULL){
        printf("error:T is Null\n");
        return NULL;
    }
    if(T->element > X){
        return Avl_Find(X, T->left);
    }else if (T->element < X){
         return Avl_Find(X, T->right);
    }else{
        return T;
    }
}
AvlPosition
Avl_FindMax(AvlElementType X,AvlTree T){
    if(T == NULL){
        return NULL;
    }
    while (T->right) {
        T = T->right;
    }
    return T;
}

AvlPosition
Avl_FindMin(AvlElementType X,AvlTree T){
    if(T == NULL){
        return NULL;
    }
    while (T->left) {
        T = T->left;
    }
    return T;
}


/**
 前提：
 1. T左树的高度比右树多2
 2. T的左树有左树，T的左树的儿子中，左树高度比右树高
       O(T)              O(T_left)
      / \               / \
     O   O             O   O(T)
    / \               /   / \
   O   O             O   O   O
  /
 O
 @param T 返回旋转后的根节点
 */
AvlPosition
SingleRotateWidthLeft(AvlTree T){
    AvlPosition T_left = T->left;
    T->left = T_left->right;
    T_left->right = T;
    T->height = AVL_MAX(Height(T->left),Height(T->right)) + 1;
    T_left->height = AVL_MAX(Height(T->left),Height(T->right)) + 1;
    return T_left;
}


/**
 和SingleRotateWidthLeft类似
 */
AvlPosition
SingleRotateWidthRight(AvlTree T){
    AvlPosition T_right= T->right;
    T->right = T_right->left;
    T_right->left = T;
    T->height = AVL_MAX(Height(T->left),Height(T->right)) + 1;
    T_right->height = AVL_MAX(Height(T->left),Height(T->right)) + 1;
    return T_right;
}


/**
 前提：
 1. T左树的高度比右树多2
 2. T的左树有右树，T的左树的儿子中，右树高度比左树高

         O(T)
        / \
       O   O
      / \
     O   O
        / \
       O   O
 @return 返回旋转后的根节点
 */
AvlPosition
DoubleRotateWidthLeft(AvlTree T){
    /*先把T->left进行右旋转 */
   T->left = SingleRotateWidthRight(T->left);
   return SingleRotateWidthLeft(T);
}

/**
  和DoubleRotateWidthLeft类似
 */
AvlPosition
DoubleRotateWidthRight(AvlTree T){
    /*先把T->right进行左边旋转 */
    T->right = SingleRotateWidthLeft(T->right);
    return SingleRotateWidthRight(T);
}

AvlTree
Insert_avl(AvlTree T,AvlElementType X){
    if(T == NULL){
        T = malloc(sizeof(AvlTree));
        T->element = X;
        T->left = T->right = NULL;
        T->height = 0;
    }else if (X < T->element){
        T->left = Insert(T->left , X);
        if(Height(T->left) - Height(T->right) == 2){
            /**判断X是左树还是右树的叶子就可以判断 哪个儿子高度高*/
            if(X < T->left->element){//X 插在T的左树的左树 single
               T = SingleRotateWidthLeft(T);
            }else{//X 插在T的左树的右树
               T = DoubleRotateWidthLeft(T);
            }
        }
    }else if (X > T->element){
           T->right = Insert(T->right , X);
        /**判断X是左树还是右树的叶子就可以判断 哪个儿子高度高*/
        if(X > T->right->element){//X 插在T的右树的右树 single
            T = SingleRotateWidthLeft(T);
        }else{//X 插在T的右树的左树
            T = DoubleRotateWidthLeft(T);
        }
    }
    T->height = AVL_MAX(Height(T->left),Height(T->right)) + 1;
    return T;
}

int
Height(AvlTree T){
    if(T == NULL){
        return -1;
    }else{
        return T->height;
    }
};
