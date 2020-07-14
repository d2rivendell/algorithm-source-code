//
//  list.c
//  LinkTest
//
//  Created by Leon.Hwa on 17/4/13.
//  Copyright © 2017年 Leon. All rights reserved.
//

#include "MyList.h"
#include <stdlib.h>
Position First(List L){

    return L->next;
}
List Initialize(){
    List L = malloc(sizeof(List));
    L->Element = 0;
    L->next = NULL;
    return L;
}

// insert after p
void Insert(List L,ElementType X,Position p){
    Position child = malloc(sizeof(Position));
    if(child == NULL){
        printf("malloc error\n");
        return;
    }
    if(p == NULL){
        printf("p is NULL\n");
        return;
    }
    child->Element = X;
    child->next = p->next;
    p->next = child;
}

List Find(List L,ElementType X){
    Position P = L->next;
    while (P != NULL && P->Element != X) {
        P = P->next;
    }
    return P;
}

void add(List L,ElementType X){
  Position p = malloc(sizeof(List));
    p->Element = X;
    p->next = L->next;
    L->next = p;
}
void deleteList(List L){ // 联同L 一起删了
    Position p = L->next;
    free(L);
    while (p != NULL) {
        Position temp = p->next;
        free(p);
        p = temp;
    }
    
}

void printList(List L){
    List head = L;
pp:
    if(head != NULL){
        printf("%d\n",L->Element);
        head = head->next;
        goto pp;
    }
    
}
