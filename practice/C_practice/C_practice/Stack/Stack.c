//
//  CaculateBasic.c
//  C_practice
//
//  Created by Leon.Hwa on 17/4/13.
//  Copyright © 2017年 Leon. All rights reserved.
//

#include "Stack.h"
#include <stdlib.h>


MyStack * MakeStack(int size){
    if (size <= 0) {
        return NULL;
    }
    MyStack *stack =  malloc(sizeof(MyStack));
    stack->elements =  malloc(sizeof(int) * size);
    stack->capacity = size;
    stack->cur = -1;
    return stack;
}


void myFreeStack(MyStack *stack){
    free(stack->elements);
    free(stack);
}

void myPush(MyStack *stack, StackElement element){
    if (stack->cur < stack->capacity - 1) {
        printf("push");
        stack->elements[++stack->cur] = element;
    }else{
        printf("stack is full!\n");
    }
}
StackElement myPop(MyStack *stack){
    if (stack->cur >= 0) {
        printf("pop");
        return stack->elements[stack->cur--];
    }else{
        printf("stack is empty!\n");
    }
    return NULL;
}


int StactIsEmpty(MyStack *stack){
    if (stack->cur < 0) {
        return 1;
    }
    return -1;
}
