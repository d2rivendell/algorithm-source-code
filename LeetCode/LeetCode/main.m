//
//  main.m
//  LeetCode
//
//  Created by leon on 2020/6/19.
//  Copyright © 2020 leon. All rights reserved.
//

#import <Foundation/Foundation.h>
#include "LeetCode1.h"
#include "Sort.h"

void SortTest(void);
void LeetCode(void);

void arrayPrint(int arr[], int N){
    printf("\n");
    for (int i = 0; i < N; i++) {
        printf("%d ", arr[i]);
    }
    
    printf("\n");
}


int main(int argc, const char * argv[]) {
//    printf("count: %d", primeCount(3));
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
    int A[] = {1, 5, 20, 20, 25, 31};
//    printf("%d\n", coins(51, &A, 6));
//    printf("res:||%s||\n", reverseWords("  I     am a Student.     "));
    printf("%s\n",longestPalindrome2("ac"));
}
