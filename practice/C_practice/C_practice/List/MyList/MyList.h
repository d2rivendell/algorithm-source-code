//
//  list.h
//  LinkTest
//
//  Created by Leon.Hwa on 17/4/13.
//  Copyright © 2017年 Leon. All rights reserved.
//

#ifndef list_h
#define list_h

#include <stdio.h>

typedef int  ElementType;

struct Node;
typedef struct Node* PtrToNode;
typedef PtrToNode Position;
typedef PtrToNode List;
struct Node{
    ElementType Element;
    Position next;
};
List  Initialize();
Position First(List L);
void Insert(List L,ElementType X,Position p);
List Find(List L,ElementType X);
void add(List L,ElementType X);


void deleteList(List L);
void printList(List L);
#endif /* list_h */
