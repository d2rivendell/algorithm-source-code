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
      /  \               /   \
     O    O         O      O(T)
    /    \              /       /   \
   O      O         O     O     O
  /
 O
 @param T 返回旋转后的根节点
 
 这里其实是右旋（T本来是left的父节点， 把它向右旋转变成left的右节点， 并改变方向， T的left继承原left的右节点）
 T, T—>left，T->left->left，  让T—>left节点成为新的父节点
 */
AvlPosition
SingleRotateToRight(AvlTree T){
    AvlPosition T_left = T->left;
    T->left = T_left->right;
    T_left->right = T;
    T->height = AVL_MAX(Height(T->left),Height(T->right)) + 1;
    T_left->height = AVL_MAX(Height(T->left),Height(T->right)) + 1;
    return T_left;
}


/**
 和SingleRotateToRight类似
 这里其实是左旋（T本来是right的父节点， 把它向左旋转变成right的左节点， 并改变方向， T的right继承原right的左节点）
 T, T—>right，T->right->right，  让T—>left节点成为新的父节点
 */
AvlPosition
SingleRotateToLeft(AvlTree T){
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
         \
          O
 可以发现，如果只对T进行右旋的话， 还是没有平衡的，这时需要先对T->left进行左旋， 在对T进行右旋
 @param T是根节点
 @return 返回旋转后的根节点
 */
AvlPosition
DoubleRotateRight(AvlTree T){
    /*先把T->left进行右旋转 */
   T->left = SingleRotateToLeft(T->left);
   return SingleRotateToRight(T);
}

/**
  和DoubleRotateRight类似
 */
AvlPosition
DoubleRotateLeft(AvlTree T){
    /*先把T->right进行左边旋转 */
    T->right = SingleRotateToRight(T->right);
    return SingleRotateToLeft(T);
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
            if(X < T->left->element){//X 插在T的左树的左树
               T = SingleRotateToRight(T);
            }else{//X 插在T的左树的右树
               T = DoubleRotateRight(T);
            }
        }
    }else if (X > T->element){
           T->right = Insert(T->right , X);
        if(Height(T->right) - Height(T->left) == 2){
            if(X > T->right->element){//X 插在T的右树的右树
                T = SingleRotateToLeft(T);
            }else{//X 插在T的右树的左树
                T = DoubleRotateLeft(T);
            }
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
