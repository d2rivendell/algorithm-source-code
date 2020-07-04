//
//  queue.c
//  Queue
//
//  Created by leon on 2017/12/6.
//  Copyright © 2017年 Leon. All rights reserved.
//

#include "queue.h"
#include <stdlib.h>
#define MaxElementSize 20
#define MinElementSize 3
struct LHQueueRecord{
    int size;
    int capacity;
    int front;
    int rear;
    ElementType *array;
};

Queue
createQueue(int maxSize){
    if(MaxElementSize < maxSize){
        printf("queue size too big");
        return NULL;
    }
    if(MinElementSize > maxSize){
        printf("queue size too small");
        return NULL;
    }
    Queue Q;
    Q = malloc(sizeof(struct LHQueueRecord));
    if(Q == NULL){
        printf("Out of space!!!");
    }
    Q->capacity = maxSize;
    Q->array = malloc(sizeof(ElementType) * maxSize);
    MakeEmpty(Q);
    return Q;
};


/**
 初始化队列：rear在front 的前面表示队列为空
 */
void MakeEmpty( Queue Q ){
    Q->size = 0;
    Q->front = 1;
    Q->rear = 0;
}

/**
 入队
 @param X 元素
 */
void
Enqueue(Queue Q,ElementType X){
    if(Q == NULL){
        return ;
    }
    if(!IsFull(Q)){
        //判断 下个rear的位置
        if(Q->rear + 1 == Q->capacity){
            Q->rear = 0;
        }else{
            Q->rear++;
        }
        Q->size++;
        Q->array[Q->rear] = X;
    }else{
        printf("\narray is full!!!!!!!\n");
    }
}
/**
 出队
 */
ElementType
Dequeue(Queue Q){
    if(Q == NULL){
        printf("queue is NULL");
        return -1;
    }
    if(!IsEmpy(Q)){
        ElementType e = Q->array[Q->front];
        //判断 下个front的位置
        if(Q->front + 1 == Q->capacity){
            Q->front = 0;
        }else{
            Q->front++;
        }
        Q->size--;
        return e;
    }else{
        printf("\narray is empy!!!!!!!\n");
            return -1;
    }

}

int
IsFull(Queue Q){
    return Q->size == Q->capacity;
};

int
IsEmpy(Queue Q){
    /** 或者
     return Q->rear = Q->front-1;
     */
    return Q->size == 0;
};
