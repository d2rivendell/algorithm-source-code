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
