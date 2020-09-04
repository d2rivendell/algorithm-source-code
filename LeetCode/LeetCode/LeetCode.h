//
//  LeetCode1.h
//  LeetCode
//
//  Created by leon on 2020/6/19.
//  Copyright © 2020 leon. All rights reserved.
//

#ifndef LeetCode1_h
#define LeetCode1_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define DEL(x, y) (x > y ? x - y : y - x)
#define MIN(x, y) (x > y ? y : x)
#define MAX(x, y) (x > y ? x : y)

//2. 两数相加
struct ListNode {
     int val;
     struct ListNode *next;
};

struct TreeNode {
     int val;
     struct TreeNode *left;
     struct TreeNode *right;
 };
//?
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2);


/// 反转字符串
void reverseString(char* s, int sSize);

//最长不重复字符的长度
int lengthOfLongestSubstring(char * s);

//整数反转 给出一个 32 位的有符号整数，你需要将这个整数中每位上的数字进行反转。
int reverse(int x) ;

//判断数字是否是回文数
int isPalindrome(int x);

//26. 删除排序数组中的重复项 (双直指针)
int removeDuplicates(int* nums, int numsSize);

//质数个数
int countPrimes(int n);

double Power(double base, int exponent);

int* spiralOrder(int** matrix, int matrixSize, int* matrixColSize, int* returnSize);

char firstUniqChar(char* s);


int primeCount(int n);

//151. 翻转字符串里的单词
char * reverseWords(char *s);

void revertStr(char *s);

//找零钱
int coins(int money, int A[], int N);

//MARK: 最长回文子串  --动态规划
char * longestPalindrome(char * s);
//N皇后
void placeQueen(int n);

//连续子数组的最大和 
int  maxSubArray(int A[], int N);
int  maxSubArrayDp(int A[], int N);
int  maxSubArrayDp2(int A[], int N);

//最长上升子序列的长度
int  lengthOfLIS(int A[], int N);
int  lengthOfLIS2(int A[], int N);

//最长公共子序列 子序列是不连续的
int longestCommonSubsequence(char * text1, char * text2);
int longestCommonSubsequence2(char * text1, char * text2);

//MARK: 86. 分隔链表 --双指针
struct ListNode* partition(struct ListNode* head, int x);



//小堆处理 A和B的前N1大的值
void topNSort(int A[], int N1, int B[], int N2);


//739. 每日温度 -栈
int* dailyTemperatures(int* T, int TSize, int* returnSize);
int* dailyTemperatures2(int* T, int TSize, int* returnSize);

//MARK:654. 最大二叉树
struct TreeNode* constructMaximumBinaryTree(int* nums, int numsSize);
//最大二叉树每个节点的父节点的索引
int *parentIndexes(int* nums, int numsSize);


//颜色
void sortColors(int* nums, int numsSize);

void mergeTwoArray(int* nums1, int nums1Size, int m, int* nums2, int nums2Size, int n);
#endif /* LeetCode1_h */
