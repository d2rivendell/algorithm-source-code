//
//  Tool.c
//  C_practice
//
//  Created by leon on 2020/6/28.
//  Copyright © 2020 Leon. All rights reserved.
//

#include "Tool.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>


void
printList(List L){
    printf("\n");
    int i = 0;
    while (L) {
        printf("%d---> %d\n",i,L->Element);
        L = L->Next;
        i++;
    }
    printf("\n");
}

List createList(ElementType A[], int N){
    List p = (List) malloc(sizeof(List));
    List head = p;
    for (int i = 0; i < N; i++) {
        p->Element = A[i];
        p->Next = NULL;
        if (i + 1 < N){
            p->Next = (List) malloc(sizeof(List));
            p = p->Next;
        }
    }
    return head;
}


ElementType *createArray(int N){
    srand((unsigned)time(NULL));//以时间作种
    ElementType *A = (ElementType *)malloc(sizeof(ElementType) * N);
    for (int i = 0; i < N; i++) {
        A[i] = rand() % 100;
    }
    return A;
}
