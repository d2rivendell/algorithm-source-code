//
//  BinHeap.c
//  Heap
//
//  Created by leon on 2017/12/7.
//  Copyright © 2017年 Leon. All rights reserved.
//

#include "BinHeap.h"
#include <stdlib.h>
#define MinPQSize 3
#define MinData (-32767)
PriorityQueue CreatePriorityQueue(int maxElements){
    PriorityQueue Q;
    if(maxElements < MinPQSize){
        printf("size is too small!!!!\n");
        return NULL;
    }
    Q = malloc(sizeof(PriorityQueue));
    Q->size = 0;
    Q->capacity = maxElements;
    // elements[0] 作为保留不存储用户数据
    Q->elements = malloc(sizeof(ElementType) * (maxElements + 1));
    Q->elements[0] = MinPQSize;
    return Q;
}
int
isFull(PriorityQueue Q){
    return Q->size == Q->capacity;
}

int
isEmpy(PriorityQueue Q){
    return Q->size == 0;
}

/**
 插入：首先，在size未达到capacity的时候，肯定会在elements加入数据。
 因为父节点一般总会小于或等于子节点。插入之前要和父节点们做对比，直至找到最合适位置
 */
void
Insert(ElementType X,PriorityQueue Q){
    if(!isFull(Q)){
        int i;
        // size+1 占个空位
        for (i = ++Q->size; X < Q->elements[i/2]; i /= 2) {
            Q->elements[i] = Q->elements[i/2];
        }
        Q->elements[i] = X;
    }
}

/**
 删除最小： 最小的值在根节点。删除前要将空穴向下移动到最合适的位置

 */
ElementType
DeleteMin(PriorityQueue Q){
    if(isEmpy(Q)){
        printf("PriorityQueue is empy!!!!\n");
        return -1 ;
    }
    // 0为占用为，根节点在1处
    ElementType  minElement= Q->elements[1];
    ElementType  lastValue = Q->elements[Q->size];
    Q->size--; //把最后一个位置空出来
    int i;
    int child;
    for (i = 1; i *= 2 <= Q->size; i = child ) {
        child = i * 2;
        //找出左右最小节点 child != Q->size表明有右节点存在
        if(child != Q->size && Q->elements[child] > Q->elements[child+1])
             child++;
        //下滤 将空穴下移
        if(lastValue < Q->elements[child]){//如果lastValue比儿子更合适在位置i, 则该位置应该让给lastValue
            break;
        }else{
             Q->elements[i] = Q->elements[child];
        }
    }
    Q->elements[i] = lastValue;
    return minElement;
    
}
