//
//  BinHeap.h
//  Heap
//
//  Created by leon on 2017/12/7.
//  Copyright © 2017年 Leon. All rights reserved.
//
/**
 二叉堆：完全被填满，除了底层。填入的顺序是从左到右
 一个节点的位置为i, 则左儿子在2i上，有儿子在（2i+1） 父节点在（i/2）当然数组第一个元素为0，不存储数字                                                                                                                                                                                                                                                                                                                                                                                                     

 优先队列(二叉堆实现)：时间越短越优先处理（在这里用值的大小表示），每次插入总是把小的放在前面，大的放后面（对于不同高度来说父节点比子节点小，同一高度从左到右不排序）
 */
#ifndef BinHeap_h
#define BinHeap_h

#include <stdio.h>

struct HeapStruct;

typedef struct HeapStruct *PriorityQueue;
typedef int  ElementType;
struct HeapStruct{
    int capacity;
    int size;
    ElementType *elements;
};
PriorityQueue CreatePriorityQueue(int maxElements);
int isFull(PriorityQueue Q);
int isEmpy(PriorityQueue Q);



#endif /* BinHeap_h */
