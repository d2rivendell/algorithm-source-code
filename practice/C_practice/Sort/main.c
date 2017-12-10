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
int main(int argc, const char * argv[]) {
   
    
    ElementType A[] = {26,8,43,16,12,11,4,32,18,22,7,17,33,3,25};
    ShellSort(A, 15);
    for (int i = 0; i < 15; i++) {
        printf("%d ",A[i]);
    }
    printf("\n");
    return 0;
}


/**
 插入排序
 */
void
InsertSort(ElementType A[],int N){
    int i,j;
    for ( i = 1; i < N ; i++) {
        ElementType p = A[i];
        for ( j = i; j > 0; j--) {
            if(A[j - 1] > p){
                A[j] = A[j-1];
            }else{
                break;
            }
        }
        A[j] = p;
    }

}


/**
 希尔排序是基于插入排序，普通插入排序的增量固定为1。希尔排序的增量 为 N ／= 2
 其实喝插入排序的逻辑相识这里的Increment 相当于插入排序的1
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

/**
 堆排序： 利用之前实现的deleMin函数，每次delete出来的是在堆里面的最小的值。
 把delete的值放在该堆的第size个位置（没delete一次size减1）。这样就避免再开辟
 空间来存储delete出来的值。delete完后，该堆结构的数字就存储了递减排序的数值。
 为了让它最后是正序的，我们改变堆结构使得父节点总是大于子节点，实现deleteMax函数。
（和优先队列相反）
 
 */
void HeapSort(ElementType A[],int n){

}
