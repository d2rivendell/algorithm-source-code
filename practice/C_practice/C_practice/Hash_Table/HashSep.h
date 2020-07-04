//
//  HashSep.h
//  Hash_Table
//
//  Created by leon on 2018/1/4.
//  Copyright © 2018年 Leon. All rights reserved.
//
//分离链接法：
#ifndef HashSep_h
#define HashSep_h

#include <stdio.h>
typedef unsigned int Index;
typedef  int ElementType;
struct ListNode;
typedef struct ListNode *Position;
struct ListNode{
    ElementType val;
    Position next;
};
typedef  Position List;
struct HashTb1;
typedef struct HashTb1 *HashTable;
struct HashTb1{
    int TableSize;
    // 数组指针
    List *TheLists;
};

//根据key 返回hash后的下标
Index string_Hash(const char *Key,int TableSize);
Index int_Hash(ElementType Key,int TableSize);
Position Find(ElementType Key,HashTable H);
#endif /* HashSep_h */
