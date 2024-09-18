//
//  main.c
//  Sort
//
//  Created by leon on 2017/12/10.
//  Copyright © 2017年 Leon. All rights reserved.
//

#include <stdio.h>
#include "Tool.h"

void heapInsert(int A[], int n, int val);
void perDown2(int A[], int n, int i);
void arraySwap2(int A[], int a, int b){
    int temp = A[a];
    A[a] = A[b];
    A[b] = temp;
}
void heapSort2(int A[], int n){
    
    for(int i = n/2-1; i >= 0; i--){
        perDown2(A, n, i);
    }
    
//    for(int i = 0; i < n; i++){
//        arraySwap2(A, n - i - 1, 0);
//        perDown2(A, n - i - 1, 0);
//    }
}
//构建大堆
void perDown2(int A[], int n, int i){
    int root = A[i];
    int child = 0;
    for(; 2 * i + 1 < n; i = child){
        child = 2 * i  + 1;
        if(child + 1 < n && A[child+1] > A[child]){
            child = child + 1;
        }
        if(A[child] > root){
            A[i] = A[child];
        }else{
            break;
        }
    }
    A[i] = root;
    
}

//在构建好的大堆中插入
/*
 上虑 (空穴上移)
 对于根节点i:
   左子树： 2 * i+ 1
   右子树： 2 * i + 2
 
 对于子树i, 父节点 (i-1)/2
 */
void heapInsert(int A[], int n, int val){
    int parent = 0;
    int i = n - 1;
    for (; (i-1)/2 >= 0 && i != 0; i = parent) {
        parent = (i-1)/2;
        if (A[parent] < val) {
            A[i] = A[parent];
        }else{
            break;
        }
    }
    if (A[i] < val) {
        A[i] = val;
    }
}

void quickHelper2(int A[], int left, int right);
int partition2(int A[], int begin, int end);
void quickSort2(int A[], int n){
    if(n <= 1){
        return;
    }
    quickHelper2(A, 0, n-1);
}

//分治算法
void quickHelper2(int A[], int left, int right){
    if(left < right){
        int p = partition2(A, left, right);
        quickHelper2(A,left, p - 1);
        quickHelper2(A,p + 1, right);
    }
}

int partition2(int A[], int begin, int end){
    int guard = A[begin];
    int i = begin;
    int j = end;
    while(i < j){
        //右边开始
        while(A[j] >= guard && i < j){
            j--;
        }
        while(A[i] <= guard && i < j){
            i++;
        }
        arraySwap2(A, i , j);
    }
    //i , j重叠了
    arraySwap2(A, i , begin);
    return i;
}

typedef  int ElementType;

void Swap(ElementType *a,ElementType *b);
void ArraySwap(int n[], int i, int j);
void ArrayPrint(int A[], int n);
int BinarySearch(int n[], int len, int a);

//冒泡排序
void BubbleSort(ElementType A[],int N);

//插入排序
void InsertSort(ElementType A[],int n);

//希尔排序
void ShellSort(ElementType A[],int n);

//堆排序
void HeapSort(ElementType A[],int n);
void PercDown(ElementType A[],int i,int N);

//快速排序
void Quicksort(int n[], int len);
void quicksortHelper(int n[], int l, int r);
int partition(int n[], int l, int r);

void  heapSort2(int A[], int N);
void PerDown2(int A[], int N, int i);

int main(int argc, const char * argv[]) {
    int len = 9;
    ElementType *A = createArray(len);
    for (int i = 0; i < len; i++) {
        printf("%d ",A[i]);
    }
    printf("\n==============\n");
    heapSort2(A, len);
    ArrayPrint(A, len);
    printf("inser 16");
    heapInsert(A, len, 16);
     ArrayPrint(A, len);
    printf("inser 32");
    heapInsert(A, len, 32);
     ArrayPrint(A, len);
    printf("inser 95");
    heapInsert(A, len, 95);
     ArrayPrint(A, len);
    printf("\n %d 在 第: %d 个\n",A[1], BinarySearch(A, len, A[1]));

    return 0;
}



//MARK:- ========  工具函数  ========
void Swap(ElementType *a,ElementType *b){
    *a = *a^*b;
    *b = *a^*b;
    *a = *a^*b;
}


void ArraySwap(int n[], int i, int j){
    int temp = n[i];
    n[i] = n[j];
    n[j] = temp;
}

int BinarySearch(int n[], int len, int a){
    //    [x, x, x, x,x];  0110>1---->011
    if (len == 0) {//防止传空进来
        return -1;
    }
    int begin = 0;
    int end = len - 1;
    while (begin <= end) {
        int min = begin + (end -  begin)/2;//防止出现溢出
        if(a == n[min]){
            return min;
        }else if (a < n[min] ){
            end = min - 1;
        }else if (a > n[min]){
            begin = min + 1;
        }
    }
     return -1;

}

void ArrayPrint(int A[], int n){
    printf("\n");
    for (int i = 0; i < n; i++) {
        printf("%d ",A[i]);
    }
    printf("\n");
}



//MARK:- ======== 排序算法 ========
/**
 冒泡排序
 */
void BubbleSort(ElementType A[],int N){
    int i,j;
    for(i = 1; i< N; i++){  // 外层只需要循环N-1次
        int flag = 1;
        for(j = N - 1; j >= i; j--){
            if(A[j-1]>A[j]){
                int temp = A[j];
                A[j] = A[j-1];
                A[j-1] = temp;
                flag = 0;
            }
        }
        if(flag){
            break;
        }
    }

}

//MARK: 插入排序

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

//MARK: 希尔排序
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
void HeapSort(ElementType A[],int N){
    int i = 0;
    //构建max堆，从倒数第一层的节点边开始构建
    for (i = N/2-1; i >= 0; i--) {
        PercDown(A, i, N);//把第i个节点下滤
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

如果父节点小于子节点。把父节点和子节点交换， 再在子节点重复这个过程
 @param A 待构建的数组
 @param i 位置
 @param N 数组元素个数
 */
void PercDown(ElementType A[],int i,int N){//把第i个节点下滤
    ElementType temp;//保存该层父节点
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




//MARK:快速排序法

/*
 注意点： 1. 从右边开始找，即基数的对立面
        2. 等于基本点的不算
 
 
 任意在数组中选一个基数，使用两个指针i,j。初始i=最左边 j=最右边。 要从右边开始找
 1、 j从右往左寻找第一位小于【基数】的数字,i从左往右寻找第一位大于【基数】的数字; （不是同时滑动，j开始往左边找,然后i往右边找到了就停止）
 2、 找到后将两个数字进行交换。继续循环交换直到i>=j结束循环；
 3、 最终指针i=j,此时交换基数和i(j)指向的数字即可将数组划分为【小于基数｜基数｜大于基数】的三部分，即完成一趟快排；
再选择基数左边的数组和基数右边的数组重复1-3步骤
 */
void Quicksort(int n[], int len){
    quicksortHelper(n, 0, len - 1);
}

void quicksortHelper(int n[], int l, int r){
    if(l < r){//指针还可以滑动
        //当前数组重复1-3
        int p = partition(n, l, r);//p是排序好的位置
        //左边数组重复1-3
        quicksortHelper(n, l, p-1);
        //右边数组重复1-3
        quicksortHelper(n, p+1, r);
    }
}

//找到基准点的位置, 在基准点的右边开始找
int partition(int n[], int l, int r){
    int provit = n[l];//我们选择第一个作为基准点
    int j = r;
    //当[6,4] 基准点为6时， j=1满足条件，如果开始时i=0+1， i和j同时在1的位置，这时不会交换，但是[6,4]顺序是不对的!!
    int i = l;//不要先+1，
    while (i < j) {
        //j先往左边边找 要有等号=
        while (n[j] >= provit && i < j) {
            j--;
        }
        //i先往右边找
        while (n[i] <= provit && i < j) {
            i++;
        }
        //i和j 各自找到了满足的位置， 进行交换
        ArraySwap(n, i, j);
    }
    //i和j重合了，把基准点放到这个位置
     ArraySwap(n, i, l);
    return j;
}
