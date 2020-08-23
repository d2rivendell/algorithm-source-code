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

void SortTest(void);
void LeetCode(void);
void testLengthOfLIS();
void testLongestCommonSubsequence();
void arrayPrint(int arr[], int N){
    printf("\n");
    for (int i = 0; i < N; i++) {
        printf("%d ", arr[i]);
    }
    
    printf("\n");
}



int main(int argc, const char * argv[]) {
    LeetCode();
    return 0;
}


void SortTest(){
    int A[] = {7, 9, 2, 6, 8, 1, 4, 3, 5, 0};
//    InsertSort(A, sizeof(A)/sizeof(int));
    BubbleSort(A, sizeof(A)/sizeof(int));
    arrayPrint(A, sizeof(A)/sizeof(int));
}

void
LeetCode(){
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
    
    testLongestCommonSubsequence();
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
