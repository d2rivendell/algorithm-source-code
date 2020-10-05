//
//  Sort.c
//  LeetCode
//
//  Created by huayf on 2020/6/28.
//  Copyright © 2020 leon. All rights reserved.
//

#include "Sort.h"

void
InsertSort(int A[], int N){
    int i,j;
    for (i = 1; i < N ; i++){
      int p = A[i];
      for(j = i; j > 0; j--){
          if (p < A[j-1]){
              A[j] = A[j - 1];//往后移让位置给P
          }else{
              break;//默认是排好序的，如果小于p,前面d肯定都是小于p的
          }
      }
      A[j] = p;
    }
}

void
BubbleSort(int A[], int N){
    int i,j;
    for ( i = 1; i <= N - 1; i++) {//循环次数
        int flag = 0;//标记一次循环是否发生过交换
        for ( j = N-1; j >= i; j--) {//每次循环最大交换次数
            if(A[j] < A[j - 1]){
                int temp = A[j];
                A[j] = A[j - 1];
                A[j - 1] = temp;
                flag = 1;
            }
        }
        if(flag == 0){
            break;
        }
    }
}

//res: 用于保存中间的排序结果
void merge_sort_helper(int A[], int res[], int l, int r);
void MergeSort(int A[], int N){
    int res[N];
    merge_sort_helper(A, res, 0, N-1);
}

void merge_sort_helper(int A[], int res[], int l, int r){
    if(l >= r) return; //分解到一个的时候，不需要排序， 想想只有一个元素还排序？
    int mid = l + (r - l)/2;
    int start1 = l, end1 = mid, start2 = mid + 1, end2 = r;
    merge_sort_helper(A, res, start1 , end1);
    merge_sort_helper(A, res, start2 , end2);
    //合并两个[l, mid], [mid+1, r]的值，即排序A[l,r]范围内的数字
    int cur = start1;
    while (start1 <= end1 || start2 <= end2) {
        if(start1 <= end1 && start2 <= end2) {
            res[cur++] = A[start1] < A[start2] ? A[start1++] : A[start2++];
        }else if (start1 <= end1) {
            res[cur++] = A[start1++];
        }else {
            res[cur++] = A[start2++];
        }
    }
    //把中间排序结果存入A
    for (int i = l; i <= r; i++) {
        A[i] = res[i];
    }
}
