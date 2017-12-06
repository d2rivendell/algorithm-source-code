//
//  ADTTree.h
//  tree
//
//  Created by leon on 2017/12/6.
//  Copyright © 2017年 Leon. All rights reserved.
//
// ADT数：对于树中每个节点X。它的左树关键字的值小于X关键字的值，相反右树的关键字的值大于X关键字的值
#ifndef ADTTree_h
#define ADTTree_h

#include <stdio.h>

typedef int  ElemwnrType;

struct TreeNode;
typedef struct TreeNode *Position;
typedef struct TreeNode *SearchTree;
void MakeEmpty( SearchTree T);
SearchTree FindMax(SearchTree T);
SearchTree FindMin(SearchTree T);
SearchTree Insert(SearchTree T,ElemwnrType X);
SearchTree Delete(SearchTree T,ElemwnrType X);
#endif /* ADTTree_h */
