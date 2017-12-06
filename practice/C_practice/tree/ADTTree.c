//
//  ADTTree.c
//  tree
//
//  Created by leon on 2017/12/6.
//  Copyright © 2017年 Leon. All rights reserved.
//

#include "ADTTree.h"
#include <stdlib.h>
struct TreeNode{
    ElemwnrType element;
    SearchTree left;
    SearchTree right;
};

void
MakeEmpty( SearchTree T){
    if(T != NULL){
        MakeEmpty(T->left);
        MakeEmpty(T->right);
        free(T);
    }
}

SearchTree
Find(SearchTree T,ElemwnrType X){
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
Insert(SearchTree T,ElemwnrType X){
    if(T == NULL){
        T = malloc(sizeof(SearchTree));
        T->element = X;
        T->left = T->right = NULL;
    }else{
        if (T->element > X) {
            Insert(T->left, X);
        }else if (T->element < X){
             Insert(T->right, X);
        }
    }
    return T;
};


SearchTree
Delete(SearchTree T,ElemwnrType X){
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
