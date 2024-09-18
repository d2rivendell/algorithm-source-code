//
//  Sort.c
//  LeetCode
//
//  Created by huayf on 2020/6/28.
//  Copyright © 2020 leon. All rights reserved.
//

#include "Sort.h"

void arraySwap(int arr[], int a, int b) {
    int temp = arr[a];
    arr[a] = arr[b];
    arr[b] = temp;
}

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

// MARK: - 归并排序
//res: 用于保存中间的排序结果
void merge_sort_helper(int A[], int res[], int l, int r);
void MergeSort(int A[], int N){
    int res[N];
    merge_sort_helper(A, res, 0, N-1);
}

void merge_sort_helper(int A[], int res[], int l, int r){
    if(l >= r) return; //l==r的时候，[l,r]不能再分为两组，不需要合并了
    int mid = l + (r - l)/2;
    int start1 = l, end1 = mid, start2 = mid + 1, end2 = r;
    merge_sort_helper(A, res, start1 , end1);
    merge_sort_helper(A, res, start2 , end2);
    //合并两个[l, mid], [mid+1, r]的值，即排序A[l,r]范围内的数字
    int cur = start1;
    //因为是递归，走到这里时说明两个区间[l, mid], [mid+1, r]都各自排序好了，要做的就是合并两个有序的数组即可！
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


//MARK:快速排序法

/*
 注意点： 1. 从右边开始找，即基数的对立面
 2. 等于基本点的不算
 
 
 任意在数组中选一个基数，使用两个指针i,j。初始i=最左边 j=最右边。 要从右边开始找
 1、 j从右往左寻找第一位小于【基数】的数字,i从左往右寻找第一位大于【基数】的数字; （不是同时滑动，j开始往左边找,然后i往右边找到了就停止）
 2、 找到后将两个数字进行交换。继续循环交换直到i>=j结束循环；
 3、 最终指针i=j,此时交换基数和i(j)指向的数字即可将数组划分为【小于基数｜基数｜大于基数】的三部分，即完成一趟快排；
 再选择基数左边的数组和基数右边的数组重复1-3步骤
 
 
 复杂度分析：
 T(n) = O(n) + 2T(n/2)
 数学归纳法得出： T(n) = O(nlogn)
 
 最坏情况下：(类似插入排序)
 T(n) = O(n) + T(1) + T(n-1) = O(n) + T(n-1)
 T(n) = O(n^2)
 */
void quicksortHelper(int A[], int l, int r);
int _partition(int A[], int l, int r);
void QuickSort(int A[], int N){
    quicksortHelper(A, 0, N - 1);
}

void quicksortHelper(int A[], int l, int r){
    if(l < r){//指针还可以滑动
        //当前数组重复1-3
        int p = _partition(A, l, r);//p是排序好的位置
        //左边数组重复1-3
        quicksortHelper(A, l, p-1);
        //右边数组重复1-3
        quicksortHelper(A, p+1, r);
    }
}

//找到基准点的位置, 在基准点的右边开始找
int _partition(int A[], int l, int r){
    int pivot = A[l];//我们选择第一个作为基准点
    int j = r;
    //当[6,4] 基准点为6时， j=1满足条件，如果开始时i=0+1， i和j同时在1的位置，这时不会交换，但是[6,4]顺序是不对的!!
    int i = l;//不要先+1，
    while (i < j) {
        //j先往左边边找 要有等号=
        while (A[j] >= pivot && i < j) {
            j--;
        }
        //i先往右边找
        while (A[i] <= pivot && i < j) {
            i++;
        }
        //i和j 各自找到了满足的位置， 进行交换
        arraySwap(A, i, j);
    }
    //i和j重合了，把基准点放到这个位置
    arraySwap(A, i, l);
    return j;
}


//MARK: 堆排序
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
void PercDown(int A[],int i,int N);
void HeapSort(int A[],int N){
    int i = 0;
    //构建max堆，从倒数第一层的节点边开始构建
    for (i = N/2-1; i >= 0; i--) {
        PercDown(A, i, N);//把第i个节点下滤
    }
    //deleteMax 把删除的max值依次放在最后面
    for (i = N - 1; i >= 0; i--) {
        //A[0] 根据max堆的特性 A[0]肯定是数组中最大的值，交换过后相当于把Max删除再放到后面
        arraySwap(A, 0, i);
        //上次交换过后A[0]肯定不是最大的，这时候要进行下滤进行归位
        PercDown(A, 0, i);
    }
}

/**
 构建堆（下滤）,和优先队列里的二叉堆不一样，这里数组下标从0开始。
 节点i的左儿子在2i+1,右儿子在2i+2
 
 如果父节点小于子节点。把父节点和子节点交换， 再在子节点重复这个过程
 @param A 待构建的数组
 @param i 位置
 @param N 数组元素个数
 */
void PercDown(int A[],int i,int N){//把第i个节点下滤
    int temp;//保存该层父节点
    int child = 0;
    for (temp = A[i]; 2 * i + 1 < N; i = child) {//有左节点
        child = 2 * i + 1;//左边节点
        if (child + 1 < N && A[child] < A[child + 1]) {//如果存在右节点，而且右节点比左节点大
            child++;//右节点
        }
        if (temp < A[child]) {//如果子节点比父节点大，父节点下滤
            A[i] = A[child];
        }else{
            break;//当前位置就是合适的，马上跳出，不跳出i变为 1=child
        }
    }
    A[i] = temp;
    
}
