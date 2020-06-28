//
//  main.c
//  Sort
//
//  Created by leon on 2017/12/10.
//  Copyright © 2017年 Leon. All rights reserved.
//

#include <stdio.h>
typedef  int ElementType;

void InsertSort(ElementType A[],int n);
void ShellSort(ElementType A[],int n);
void HeapSort(ElementType A[],int n);
void PercDown(ElementType A[],int i,int N);
void Swap(ElementType *a,ElementType *b);
int main(int argc, const char * argv[]) {
   
    
    ElementType A[] = {26,8,43,16,12,11,4,32,18,22,7,17,33,3,25};
    HeapSort(A, 15);
    for (int i = 0; i < 15; i++) {
        printf("%d ",A[i]);
    }
    printf("\n");

    return 0;
}


/**插入排序
 */
void
InsertSort(ElementType A[],int N){
    int i,j;
    for ( i = 1; i < N ; i++) {
        ElementType p = A[i];
        for ( j = i; j > 0; j--) {
            if(A[j - 1] > p){
                A[j] = A[j-1];//往后移让位置给P
            }else{
                break;
            }
        }
        A[j] = p;
    }

}


/** 希尔排序
 希尔排序是基于插入排序，普通插入排序的增量固定为1。希尔排序的增量 为 N ／= 2
 其实和插入排序的逻辑相似这里的Increment 相当于插入排序的1
 具体过程可由shellSort.jpg看出。
 */
void ShellSort(ElementType A[],int N){
    int i , j ,Increment;
    for (Increment = N /2; Increment > 0; Increment /= 2) {//缩小增量
        //以下部分和InsertSort基本相同
        for (i = Increment; i < N; i++) {//
            ElementType p = A[i];
            for (j = i; j >= Increment; j--) {
                if(A[j - 1] > p){
                    A[j] = A[j-1];
                }else{
                    break;
                }
            }
             A[j] = p;
        }
    }
}

/** 堆排序
 堆排序： 利用之前实现的deleMin函数，每次delete出来的是在堆里面的最小的值。
 把delete的值放在该堆的第size个位置（每delete一次size减1）。这样就避免再开辟
 空间来存储delete出来的值。delete完后，该堆结构的数字就存储了递减排序的数值。
 为了让它最后是正序的，我们改变堆结构使得父节点总是大于子节点，实现deleteMax函数。
（和优先队列相反）
 实现思路：先把传入的无序数组构建成堆结构（和队列不同，这里下标从0开始），之前在二叉堆Insert方法用了上滤的思想，这里构建Max堆用下滤实现,
 具体过程参考 PercolateDown_to_buidHeap.png
 
 @param A 待排序的数组
 @param N 数组长度
 */
void HeapSort(ElementType A[],int N){
    int i = 0;
    //构建max堆
    for (i = N/2; i >= 0; i--) {
        PercDown(A, i, N);
    }
    //deleteMax 把删除的max值依次放在最后面
    for (i = N - 1; i >= 0; i--) {
        //A[0] 根据max堆的特性 A[0]肯定是数组中最大的值，交换过后相当于把Max删除再放到后面
        Swap(&A[i], &A[0]);
        //上次交换过后A[0]肯定不是最大的，这时候要进行下滤进行归位
        PercDown(A, 0, i);
    }
}

/**
 构建堆（下滤）,和优先队列里的二叉堆不一样，这里数组下标从0开始。
 节点i的左儿子在2i+1,右儿子在2i+2

 @param A 待构建的数组
 @param i 位置
 @param N 数组元素个数
 */
void PercDown(ElementType A[],int i,int N){
    ElementType temp;
    int child = 0;
    for (temp = A[i]; 2 * i + 1 < N; i = child) {
        child = 2 * i + 1;
        if (child != N - 1 && A[child] < A[child + 1]) {
            child++;
        }
        if (temp < A[child]) {
            A[i] = A[child];
        }else{
            break;
        }
    }
    A[i] = temp;
}

void Swap(ElementType *a,ElementType *b){
     *a = *a^*b;
     *b = *a^*b;
     *a = *a^*b;
}
