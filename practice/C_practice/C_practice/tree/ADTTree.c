//
//  ADTTree.c
//  tree
//
//  Created by leon on 2017/12/6.
//  Copyright © 2017年 Leon. All rights reserved.
//

#include "ADTTree.h"
#include <stdlib.h>


void
MakeEmpty( SearchTree T){
    if(T != NULL){
        MakeEmpty(T->left);
        MakeEmpty(T->right);
        free(T);
    }
}

SearchTree
Find(SearchTree T,ElementType X){
    if (T == NULL) {
        return NULL;
    }
    if (T->element < X) {
       return  Find(T->left, X);
    }else if (T->element > X){
        return  Find(T->right, X);
    }else{
        return T;
    }
}

SearchTree
FindMax(SearchTree T){
//    if (T == NULL) {
//        return NULL;
//    }
//    if(T->right == NULL){
//        return T;
//    }
//    return  FindMax(T->right);
    if(T != NULL){
        while (T->right != NULL) {
            T = T->right;
        }
        return T;
    }else{
        return NULL;
    }
}
SearchTree
FindMin(SearchTree T){
    if(T != NULL){
        while (T->left != NULL) {
            T = T->left;
        }
        return T;
    }else{
        return NULL;
    }
}
SearchTree
Insert(SearchTree T,ElementType X){
    if(T == NULL){
        T = malloc(sizeof(SearchTree));
        T->element = X;
        T->left = T->right = NULL;
    }else{
        if (T->element > X) {
           T->left = Insert(T->left, X);
        }else if (T->element < X){
           T->right =  Insert(T->right, X);
        }
    }
    return T;
};



/**
 1:如果被删除的节点有一个儿子，让该节点的父节点指向该节点的子节点，再把该节点删掉即可，参考ADT.png
 2:如果被删除的节点有两个儿子，找出该节点“右树的最小节点”（右最小）。把“右最小”的值复制到被删除节点。最后删除“右最小节点”。这里可以了解到，其实删除的并不是该节点，而是该节点的右树最小节点。
 @param T 要删除节点的树
 @param X 删除的节点值
 @return 返回NULL表示该节点已经被删除或者不存在。返回有值表示要删除的节点在它的儿子下面
 */
SearchTree
Delete(SearchTree T,ElementType X){
    if(T == NULL){
        printf("T is NULL!!!\n");
        return NULL;
    }
    
    if(T->element > X){
      T->left  =  Delete(T->left,X);
    }else if (T->element < X){
      T->right =  Delete(T->right,X);
    }else{
        if(T->left && T->right){  //有两个儿子
            SearchTree tmpCell = FindMin(T->right);
            T->element = tmpCell->element;
            T->right = Delete(T->right, T->element);
        }else if (T->left || T->right){ //有一个儿子
            Position tmp = T;
            if(T->left){
                T = T->left;
            }else if (T->right){
                T = T->right;
            }
            free(tmp);
        }else{//没有儿子
            free(T);
            T = NULL;
        }
    }
    return T;
}
