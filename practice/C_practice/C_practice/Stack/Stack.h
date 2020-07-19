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

#define StackEmpty 0x8fffffff

typedef void * StackElement;

typedef struct
{
    StackElement *elements;
    int  capacity;
    int cur;
}MyStack;

MyStack * MakeStack(int size);
void myFreeStack(MyStack *stack);
void myPush(MyStack *stack, StackElement element);
StackElement  myPop(MyStack *stack);
int StactIsEmpty(MyStack *stack);
#endif /* CaculateBasic_h */
