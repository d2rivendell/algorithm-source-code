//
//  main.c
//  C_practice
//
//  Created by Leon.Hwa on 17/4/12.
//  Copyright © 2017年 Leon. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include <time.h>
int main(int argc, const char * argv[]) {
    srand((unsigned)time(NULL));//以时间作种
//    List chainList = malloc(sizeof(List));
//    chainList->Element = rand() % 100;
//    chainList->Next = NULL;
//    Insert(20, chainList, Header(chainList));
//    Insert(30, chainList, chainList->Next);
//    List p = chainList;
//    int i = 0;
//    while (p) {
//        printf("%d---> %d\n",i,p->Element);
//        p = p->Next;
//        i++;
//    }
//    DeleteList(chainList);

  
    printf("'+' = %d\n'-' = %d\n'*' = %d\n'/' = %d\n",'+','-','*','/');
    printf("=======\n");
    char ch;
    scanf("%c",&ch);
    printf("%d",ch);
    
    
    return 0;
}

void
lh_Insert(ElementType X,List L,Position P){
    if (L == NULL || P == NULL) {
        printf("List and Position can not be NULL!!!");
    }
    PtrToNode TmpCell = malloc(sizeof(struct Node));
    TmpCell->Element = X;
    TmpCell->Next = P->Next;
    
}



