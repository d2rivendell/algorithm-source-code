//
//  CaculateBasic.h
//  C_practice
//
//  Created by Leon.Hwa on 17/4/13.
//  Copyright © 2017年 Leon. All rights reserved.
//

#ifndef CaculateBasic_h
#define CaculateBasic_h

#include <stdio.h>




typedef int ElementType;
struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode Stack;

struct Node
{
    ElementType Element;
    PtrToNode   Next;
};

int C_IsEmpty( Stack S );
Stack C_CreateStack( void );
void C_DisposeStack( Stack S );
void C_MakeEmpty( Stack S );
void C_Push( ElementType X, Stack S );
ElementType C_Top( Stack S );
void C_Pop( Stack S );


#endif /* CaculateBasic_h */
