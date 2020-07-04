//
//  main.c
//  Stack
//
//  Created by Leon.Hwa on 17/4/12.
//  Copyright © 2017年 Leon. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "stackli.h"
int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    return 0;
}

void
lh_Push(ElementType X, Stack S){
    if (S == NULL) {
        printf("Stack is NULL");
        return;
    }
   
    PtrToNode node =  malloc(sizeof(PtrToNode));
    if (node == NULL) {
        printf("out of space!!!");
        return;
    }
    node->Element = X;
    PtrToNode temp =  S->Next;
    S->Next = node;
    node->Next = temp;
}
void
lh_Pop(Stack S){
    if (S == NULL) {
        printf("Stack is NULL");
        return;
    }
    PtrToNode temp =  S->Next;
    if (temp != NULL) {
        S->Next = temp->Next;
        free(temp);
    }
    
}

