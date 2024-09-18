//
//  main.m
//  LeetCode
//
//  Created by leon on 2020/6/19.
//  Copyright © 2020 leon. All rights reserved.
//

#import <Foundation/Foundation.h>
#include "LeetCode.h"
#include "Sort.h"
#include "kmp.h"
#include <stdbool.h>

void SortTest(void);
void LeetCode(void);
void testLengthOfLIS();
void testLongestCommonSubsequence();
void testPartitionList();
void topNTest();
void testDailyTemperatures();
void testParentIndexes();
void testSortColors();
void testMergeTwoArray();
void testKnapsack();

int *createIntArray(int N){
    srand((unsigned)time(NULL));//以时间作种
    int *A = (int *)malloc(sizeof(int) * N);
    for (int i = 0; i < N; i++) {
        A[i] = rand() % 100;
    }
    return A;
}

struct ListNode  *createList(int A[], int N){
    struct ListNode  *p = (struct ListNode *) malloc(sizeof(struct ListNode ));
    struct ListNode  *head = p;
    for (int i = 0; i < N; i++) {
        p->val = A[i];
        p->next = NULL;
        if (i + 1 < N){
            p->next = (struct ListNode *) malloc(sizeof(struct ListNode ));
            p = p->next;
        }
    }
    return head;
}

void arrayPrint(int arr[], int N, bool check){
    printf("\n");
    for (int i = 0; i < N; i++) {
        printf("%d ", arr[i]);
        if(check && i > 0) {
            assert(arr[i] >= arr[i-1]);
        }
    }
    
    printf("\n");
}
void listPrint(struct ListNode *head){
    printf("\n");
    while (head) {
        printf("%d ",head->val);
        head = head->next;
    }
    printf("\n");
}


int main(int argc, const char * argv[]) {
    printf("4个砝码可以称几种: %d\n", weights(6));
    LeetCode();
    return 0;
}


void SortTest(){
    int N = 30;
    int *A = createIntArray(N);
//    InsertSort(A, sizeof(A)/sizeof(int));
//    BubbleSort(A, N);
    arrayPrint(A, N, false);
    MergeSort(A, N);
    arrayPrint(A, N, true);
   
}

void
LeetCode(){
//    struct ListNode temp, *top = &temp;
//    SortTest();

//    reverseString("1234", 4);
//    int max = lengthOfLongestSubstring("pwwkew");
//    double res = Power(2, -1);
//    revertStr("  I     am a Student.     ");
//    int A[] = {1, 5, 20, 20, 25, 31};
//    printf("%d\n", coins(19, &A, 6));
//
//    printf("%s\n",longestPalindrome("cbbd"));
//
    
    
//字符串
//    char *s = "  the sky is blue ";
//    int len = (int)strlen(s);
//    char *ss = malloc(sizeof(char) * (len + 1));
//    memcpy(ss, s, len);
//    ss[len] = '\0';
//    printf("res:||%s||\n", reverseWords(ss));

//    placeQueen(4);
    
    
    
//N皇后
//    placeQueen(4);
//    int A[9] = {-2,1,-3,4,-1,2,1,-5,4};
//    printf("连续最大子序列和： %d\n",  maxSubArrayDp2(A, 9));
    
//    testLengthOfLIS();
    
//    testLongestCommonSubsequence();
    
//分隔链表
//    testPartitionList();
    
//topNTest
//    topNTest();
    
//    testDailyTemperatures();
    
//    testParentIndexes();
    
//    testSortColors();
    
//    testKnapsack();
//    char *s = malloc(sizeof(char) * 12);
//    char *s2 = "erbottlewat";
//    memcpy(s, s2, sizeof(char) * 11);
//    s[11] = '\0';
//    printf("%s \n",  s);
//    char *s3 = malloc(sizeof(char) * 12);
//    s3[11] = '\0';
//    //len == 11
//    memcpy(s3, s + sizeof(char) * 8, sizeof(char) * 3);
//    memcpy(s3 + sizeof(char) * 3, s, sizeof(char) * 8);
//    printf("%s \n",  s3);
//    testMergeTwoArray();
    int res = reverse(1234567);
    printf("res: %d \n", res);
}


void testLengthOfLIS(){
    int A[9] = {1,3,6,7,9,4,10,5,6};
//    int A[] = {2, 2}
     printf("最大上升子序列长度： %d\n",  lengthOfLIS2(A, 9));
}

//最长公共子序列
void testLongestCommonSubsequence(){
    printf("最长公共子序列： %d\n",  longestCommonSubsequence2("abcdefhn", "aefz"));
    
}


void testPartitionList(){
    printf("分隔链表：\n");
    int A[] = {1,4,3,2,5,2};
    listPrint(partition(createList(A, 6), 3));
}


void topNTest(){
    printf("topNTest：\n");
    int N = 10;
    int *A = createIntArray(N);
    sleep(1);
    int *B = createIntArray(N);
    int *combine =(int *)malloc(sizeof(int) * N * 2);
    for (int i = 0; i < 2 * N; i++) {
        if(i < N){
            combine[i] = A[i];
        }else{
            combine[i] = B[i-N];
        }
    }
    arrayPrint(A, N, false);
    arrayPrint(B, N, false);
    topNSort(A, N, B, N);
    
    printf("result: \n");
    InsertSort(A,N);
    arrayPrint(A, N, false);
    
    printf("对比一般排序: \n");
    InsertSort(combine, 2 * N);
    arrayPrint(combine, 2 * N, false);
}


void testDailyTemperatures(){
    int temperatures[8] = {73, 74, 75, 71, 69, 72, 76, 73};
    int returnSize;
    int *res = dailyTemperatures2(&temperatures, 8, &returnSize);
    for(int i=0; i < returnSize;i++){
        printf("%d  ", res[i]);
    }
    printf("\n");
    free(res);
}


void testParentIndexes(){
    printf("最大二叉树每个节点的父节点的索引\n");
    int nums[] = {3,2,1,6,0,5};
    int *res = parentIndexes(&nums, 6);
    arrayPrint(res, 6, false);
    free(res);
}

void testSortColors(){
    printf("颜色分类\n");
    int nums[] = {2,0,2,1,1,0};
    sortColors(nums, 6);
    arrayPrint(nums, 6, false);
}
void testMergeTwoArray(){
    printf("testMergeTwoArray： \n");
    int *nums1 = malloc(sizeof(int) * 6);
    int *nums2 = malloc(sizeof(int) * 3);
    
    int arr1[6] = {1,2,3,0,0,0};
    int arr2[3] = {2,5,6};
    for (int i = 0; i < 6; i++) {
        nums1[i] = arr1[i];
    }
    for (int i = 0; i < 3; i++) {
        nums2[i] = arr2[i];
    }
    mergeTwoArray(nums1, 6, 3, nums2, 3, 3);
    arrayPrint(nums1, 6, false);
}


void testKnapsack() {
    int values[] = {6, 3, 5, 4, 6};
    int weights[] = {2, 2, 6, 5, 4};
    int capacity = 10;
    int res =  knapsack(values, 5, weights, 5, capacity);
    printf("\ntestKnapsack: %d \n", res);
}


