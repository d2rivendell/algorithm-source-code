//
//  queue.h
//  Queue
//
//  Created by leon on 2017/12/6.
//  Copyright © 2017年 Leon. All rights reserved.
//

#ifndef queue_h
#define queue_h

#include <stdio.h>
typedef  int ElementType;
struct LHQueueRecord;
typedef struct LHQueueRecord *Queue;
Queue createQueue(int maxSize);
/**初始化队列：rear在front的前面,表示队列为空*/
void MakeEmpty( Queue Q );
/**
 入队
 @param X 入队元素
 */
void Enqueue(Queue Q,ElementType X);
/**
 出队
 @param Q 出队的队列
 */
ElementType Dequeue(Queue Q);
int IsFull(Queue Q);
int IsEmpy(Queue Q);
#endif /* queue_h */
