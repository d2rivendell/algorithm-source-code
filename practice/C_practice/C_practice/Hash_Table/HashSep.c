//
//  HashSep.c
//  Hash_Table
//
//  Created by leon on 2018/1/4.
//  Copyright © 2018年 Leon. All rights reserved.
//

#include "HashSep.h"
#include <stdlib.h>
#define MinTableSize 5

/**
 当key为字符串时
 利用 Horner法则根据key和TableSize计算下标
 */
Index
string_Hash(const char *Key,int TableSize){
    unsigned int HashVal  = 0;
    while (*Key != '\0') {
        HashVal = (HashVal << 5) + *Key++;
    }
    return HashVal % TableSize;
}
Index
int_Hash(ElementType Key,int TableSize){
    return Key % TableSize;
}


HashTable
initialize(int TableSize){
    if (TableSize < MinTableSize) {
        return NULL;
    }
    HashTable H = malloc(sizeof(HashTable));
    H->TableSize = TableSize;
    H->TheLists = malloc(sizeof(List) * H->TableSize);
    //每个list都有个空表头
    for (int i = 0; i < H->TableSize - 1; i++) {
        H->TheLists[i] = malloc(sizeof(struct ListNode));
        H->TheLists[i]->next = NULL;
    }
    return H;
}

Position
Find(ElementType Key,HashTable H){
    Index idx = int_Hash(Key, H->TableSize);
    List list = H->TheLists[idx];//list是表头，是个空表
    Position p = list->next;
    while (p != NULL && p->val != Key) {
        p = p->next;
    }
    return p;
}

void
Insert(ElementType Key,HashTable H){
    if (Find(Key, H) == NULL) {
        //类似栈
        struct ListNode *node = malloc(sizeof(struct ListNode));
        node->val = Key;
        List L = H->TheLists[int_Hash(Key, H->TableSize)];
        node->next = L->next;
        L->next = node;
    }
}
