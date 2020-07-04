//
//  AVLTree.h
//  tree
//
//  Created by leon on 2017/12/6.
//  Copyright © 2017年 Leon. All rights reserved.
//
//AVL树（二叉平衡树）：左右子树保持相同的深度，最多只能相差1
#ifndef AVLTree_h
#define AVLTree_h

#include <stdio.h>
typedef int  AvlElementType;
struct AvlNode;

typedef struct AvlNode *AvlTree;
typedef struct AvlNode *AvlPosition;
int Height(AvlTree T);
AvlPosition Avl_Find(AvlElementType X,AvlTree T);
AvlPosition Avl_FindMin(AvlElementType X,AvlTree T);
AvlPosition Avl_FindMax(AvlElementType X,AvlTree T);


AvlPosition SingleRotateWidthLeft(AvlTree T);
AvlPosition SingleRotateWidthRight(AvlTree T);
AvlPosition DoubleRotateWidthLeft(AvlTree T);
AvlPosition DoubleRotateWidthRight(AvlTree T);
AvlTree Insert_avl(AvlTree T,AvlElementType X);
#endif /* AVLTree_h */
