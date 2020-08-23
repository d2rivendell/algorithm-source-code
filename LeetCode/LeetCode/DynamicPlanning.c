//
//  DynamicPlanning.c
//  LeetCode
//
//  Created by leon on 2020/8/23.
//  Copyright © 2020 leon. All rights reserved.
//

#include <stdio.h>
#include "LeetCode.h"


//MARK: 找零钱 --动态规划法
//money：要找的零钱；A: 现有的零钱数组, 是排序好的；N：零钱的张数
int coins(int money, int A[], int changeCount){
    if (money == 0) {
        return -1;
    }
    //dp[i]表示要找到零钱为i的最小的张数
    int *dp = (int *)malloc(sizeof(int) * (money + 1));
    // faces[i]是凑够i分时最后那枚硬币的面值
    int *faces = (int *)malloc(sizeof(int) * (money + 1));
    memset(faces, 1, money + 1);
    memset(dp, 0, money + 1);
    //自底向上
    for (int i = 1; i <= money; i++) {
        int MIN = 0x7fffffff;
        //        int minIdx = -1;
        for (int j = 0; j < changeCount; j++) {
            int change = A[j];//零钱
            if (change > i) {
                break;
            }
            //MIN表示: 对于金额i, 先使用了零钱charge, 剩余零钱最小的零钱张数为dp[i - charge]
            if (dp[i - change] < MIN) {
                MIN = MIN(dp[i - change], MIN);
                faces[i] = change;
            }
            if (MIN == 0x7fffffff) {//金额i确实无法找零，要设置为-1，为了让MIN+1==0
                MIN = -1;
            }
        }
        dp[i] = MIN + 1;
    }
    printf("the money is: ");
    int c = money;
    while (c > 0) {
        printf("%d ", faces[c]);
        c -= faces[c];
    }
    printf("\n");
    free(faces);
    return dp[money];
}




void copyChar(char *src, int b1, int len, char *dst, int b2){
    for (int i = 0; i < len; i++) {
        dst[b2++] = src[b1+i];
    }
}


//MARK: 5. 最长回文子串 --动态规划法
/*
 给定一个字符串 s，找到 s 中最长的回文子串。你可以假设 s 的最大长度为 1000。
 
 示例 1：
 
 输入: "babad"
 输出: "bab"
 注意: "aba" 也是一个有效答案
 https://leetcode-cn.com/problems/longest-palindromic-substring/
 */
/*
 j -------------
 i
 ｜                ｜
 ｜                ｜
 ｜________________｜
 // dp[i][j] 表示s[i-j]之间的字符是否是回文，如果 dp[i+1][i-1] == 1 && s[i] == [j]，则s[i-j]是回文
 //或者[1,2,1]， [2,2]这两种情况下初始的dp[0][2],dp[0][1]不等于0，但是它们也是回文，所以需要特殊处理
 //j-i <= 2的时候默认也是回文
 */
char * longestPalindrome(char * s){
    int len = (int)strlen(s);
    if (len == 0 || len == 1) {
        return s;
    }
    //dp[i][j]表示s[i-j]是否回文
    int **dp = malloc(sizeof(int *) * len);
    for (int i = 0; i < len; i++) {
        dp[i] = malloc(sizeof(int) * len);
        memset(dp[i], 0, sizeof(int) * len);
        dp[i][i] = 1;//顺便把对角线设置了
    }
    int maxLen = 1;
    int begin = 0;
    for (int j = 1; j < len; j++) {//左到右
        for (int i = 0;  i < j; i++) {//
            if (s[i] != s[j]) {
                dp[i][j] = 0;
            }else{
                if (dp[i+1][j-1] || j -i <= 2) {
                    dp[i][j] = 1;
                }
            }
            if (dp[i][j] && (j - i + 1) > maxLen) {
                maxLen = (j - i + 1);
                begin = i;
            }
        }
    }
    char *res = malloc(sizeof(char) * (maxLen + 1));
    memcpy(res, s+begin, maxLen);
    res[maxLen] = '\0';
    for (int i = 0; i < len; i++) {
        free(dp[i]);
    }
    free(dp);
    return res;
}


//MARK: 剑指 Offer 47. 礼物的最大价值 --动态规划法
//类似动态规划
int maxValue(int** grid, int gridSize, int* gridColSize){
    int row = gridSize;
    int col = gridColSize[0];
    //dp保存当前位置最大价值的礼物
    int **dp = malloc(sizeof(int *) * row);
    for(int i = 0; i < row; i++){
        dp[i] = malloc(sizeof(int) *col);
    }
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            int val = grid[i][j];
            int max = 0;
            if(i-1 >= 0){//存在上面位置
                max = dp[i-1][j];
            }
            if(j-1 >= 0 && max < dp[i][j-1]){//存在左边位置
                max =  dp[i][j-1];
            }
            printf("%d %d\n",val,max);
            dp[i][j] = val + max;
        }
    }
    int v = dp[row-1][col-1];
    for(int i = 0; i < row; i++){
        free(dp[i]);
    }
    free(dp);
    return v;
}

//MARK: N皇后 --回溯法
void place(int row, int n, int *cols);
int isValid(int row, int col, int *cols);
void printQueen(int *cols, int n);
void placeQueen(int n){
    //cols[i]用来记录第i行皇后放置在第几列
    int *cols = malloc(sizeof(int) * n);
    place(0, n, cols);
}

//在第row行放置皇后
void place(int row, int n, int *cols){
    if (row >= n) {
        printf("存在！\n");
        printQueen(cols, n);
        return;
    }
    for(int i = 0; i < n ; i++) {//遍历row行的第i列
        if (isValid(row, i, cols)) {
            cols[row] = i;
            place(row + 1, n, cols);
        }
    }
}

//判断在[row][col]位置是否满足要求， 相当于剪枝处理
int isValid(int row, int col, int *cols){
    for (int i = 0; i < row; i++) {
        if (cols[i] == col) {//同一列已经摆过了
            return 0;
        }
        //对角线是否摆过 (通过对角线的倒数绝对值相等来判断)
        if(row-i == abs(col - cols[i])){
            return 0;
        }
    }
    return 1;
}

void printQueen(int *cols, int n){
    for(int i = 0; i < n ; i++) {//行
        for(int j = 0; j < n ; j++) {//列
            if (cols[i] == j) {
                printf("1 ");
            }else{
                printf("0 ");
            }
        }
        printf("\n");
    }
    printf("------------------------\n");
}


//MARK: 剑指 Offer 42. 连续子数组的最大和 --分治
//左闭右开
int maxSubArrayHelper(int A[], int left, int right);
int  maxSubArray(int A[], int N){
    if (N == 0) {
        return 0;
    }
    return maxSubArrayHelper(A, 0, N);
}

//左闭右开[1,4): 1 2 3
int maxSubArrayHelper(int A[], int left, int right){
    if (right - left < 2){//只有一个元素的时候 right - left <= 1
        return A[left];
    }
    int mid = (right + left) >> 1;
    int leftMaxSum = A[mid - 1];
    int leftsum = leftMaxSum;
    for (int i = mid - 2; i >= 0; i--) { //找到左半边最大的总数，由右边开始
        leftsum += A[i];
        leftMaxSum = MAX(leftMaxSum, leftsum);
    }
    int rightSum = A[mid];
    int rightMaxSum = rightSum;
    for (int i = mid + 1; i < right; i++) { //找到左半边最大的总数，由右边开始
        rightSum += A[i];
        rightMaxSum = MAX(rightSum, rightMaxSum);
    }
    return MAX(leftMaxSum + rightMaxSum,
               MAX(maxSubArrayHelper(A, left, mid), maxSubArrayHelper(A, mid, right)));
}


//MARK: 剑指 Offer 42. 连续子数组的最大和 --动态规划
/*
 [-2,1,-3,4,-1,2,1,-5,4]
 dp[i]表示第i个数字之前最大的和，包括A[i]！
 因为要包括A[i],所以转移公式如下：
 如果 dp[i-1] < 0, dp[i] = A[i];  (前面一个已经是负数了，肯定不能加了)
 如果 dp[i-1] >= 0, dp[i] = dp[i-1] + A[i];
 */
int  maxSubArrayDp(int A[], int N){
    if (N == 0) {
        return 0;
    }
    //dp[i]表示 前i个数列中的最大和
    int *dp = malloc(sizeof(int) * N);
    memset(dp, 0, N);
    int max = A[0];
    dp[0] = max;
    for (int i = 1; i < N; i++) {
        if (dp[i-1]  >= 0) {
            dp[i] = dp[i-1] + A[i];
        }else{
            dp[i] = A[i];
        }
        if (max < dp[i]){
            max = dp[i];
        }
    }
    for (int i = 0; i < N; i++) {
        printf("%d ", dp[i]);
    }
    printf("\n");
    return max;
}

int  maxSubArrayDp2(int A[], int N){
    if (N == 0) {
        return 0;
    }
    int max = A[0];
    int dp = max;
    for (int i = 1; i < N; i++) {
        if (dp  >= 0) {
            dp = dp + A[i];
        }else{
            dp = A[i];
        }
        if (max < dp){
            max = dp;
        }
    }
    printf("\n");
    return max;
    
}
//最大连续子序列和（求最大和） --done
//最大长上升子序列（求长度）--done
//最长公共子序列、最长公共字符串


//MARK: 300. 最长上升子序列的长度 --动态规划
/*
 ⚠️是严格上升
 
 [1,3,6,7,9,4,10,5,6]
 dp[i]表示包含第i个数字最大的子序列的长度
 初始化: dp[i] = 1
 状态转移：
 遍历x∈[0,i-1]之间。如果A[x] >= A[i] 跳过（注意等于的也要跳过）， 找到最大的dp[x]。 dp[i] = dp[x] + 1
 
 */
int  lengthOfLIS(int A[], int N){
    if (N == 0) {
        return 0;
    }
    int *dp = malloc(sizeof(int) * N);
    // 注意不能用memset初始化为1,。 memset是对每个字节设置 int会被设置
    //为 0000 0001 0000 0001 0000 0001 0000 0001
    int max = 1;
    for (int i = 0; i < N; i++) {
        dp[i] = 1;
        //        int localMax = 0;
        for (int x = 0; x < i; x++) {
            if (A[x] >= A[i]) continue;
            //            if (dp[x] > localMax) {
            //                localMax = dp[x];
            //            }
            dp[i] = MAX(dp[i], dp[x] + 1);
        }
        if(dp[i] > max){
            max = dp[i];
        }
    }
    free(dp);
    return max;
}

//MARK: 300. 最长上升子序列的长度 --牌顶
/*
 top为牌顶数组
 
 如果A[i] <= top[x] 则把A[i]的牌顶下标为x的数组
 如果A[i] > top[x] 即A[i]大于现有牌顶的值 则新开牌顶
 */
//[1,3,6,7,9,4,10,5,6]
int  lengthOfLIS2(int A[], int N){
    if (N == 0) {
        return 0;
    }
    //建立数组保存所有堆的牌顶,最坏情况是所有的都是上升的需要建立N个牌顶
    int *top = malloc(sizeof(int) * N);
    //牌顶的个数
    int topCount = 1;
    top[0] = A[0];
    for (int i = 1; i < N; i++) {
        //这里可以优化为二分查找
        //常规查找1
        //        int t = 0;
        //        for (; t < topCount; t++) {
        //            if (A[i] <=  top[t]) {//找到合适的位置
        //                top[t] = A[i];
        //                break;
        //            }
        //        }
        //        if(t == topCount){//A[i]大于现有牌顶的值 开新牌顶
        //            topCount++;
        //            top[topCount - 1] = A[i];
        //        }
        //二分查找
        int left = 0;
        int right = topCount;
        while (left < right) {
            int  mid = (left + right) >> 1;
            //找到第一个小于且等于牌顶的位置
            if (A[i] <= top[mid]) {
                right = mid;
            }else if (A[i] > top[mid]){
                left = mid + 1;
            }
        }
        top[left] = A[i];//此时：left == right
        if(right == topCount){//A[i]大于现有牌顶的值 开新牌顶
            topCount++;
            top[topCount - 1] = A[i];
        }
    }
    return topCount;
}


//MARK: 1143. 最长公共子序列 --动态规划
/*
 避免数组越界, 要在二维数组外围加一圈值为0的数组
 
 子序列是不连续的
 dp[i][j]表示  是【text1 前 i 个元素 】与【nums2 前 j个元素 】的最长公共子序列长度
 初始状态：
 dp[i][0] = 0;  dp[0][j] = 0;
 状态转移方程:
 当text1[i] == text2[j]时， dp[i][j] =  dp[i-1][j-1] + 1
 当text1[i] != text2[j]时， dp[i][j] =  max{dpdp[i][j-1], dp[i-1][j]}
 */
int longestCommonSubsequence(char * text1, char * text2){
    if (text1 == NULL || text2 == NULL) return 0;
    int len1 = (int)strlen(text1);
    int len2 = (int)strlen(text2);
    if (len1 == 0 || len2 == 0) { return 0; }
    int **dp = malloc(sizeof(int*) * (len1 + 1));
    for (int i = 0; i < len1+1; i++) {
        dp[i] = malloc(sizeof(int) * (len2 + 1));
        memset(dp[i], 0, sizeof(int) * (len2 + 1));
    }
    for (int i = 1; i <= len1; i++) {
        for (int j = 1; j <= len2; j++) {
            dp[i][j] = 0;
            if (text1[i-1] == text2[j-1]) {
                //和二维数组左上角有关联
                dp[i][j] = dp[i-1][j-1] + 1;
            }else{
                //和二维数组左边和上边有关联
                dp[i][j] = MAX(dp[i - 1][j], dp[i][j-1]);
            }
        }
    }
    int max = dp[len1][len2];
    for (int i = 0; i < len1; i++) {
        free(dp[i]);
    }
    free(dp);
    return max;
}

//优化 只使用一维数组
//每次遍历 只和左上角或者左边和上边有关联， 可以通过一维数组和一个leftTop变量即可求出
int longestCommonSubsequence2(char * text1, char * text2){
    if (text1 == NULL || text2 == NULL) return 0;
    int len1 = (int)strlen(text1);
    int len2 = (int)strlen(text2);
    if (len1 == 0 || len2 == 0) { return 0; }
    char *cols = text1 , *rows = text2;
    int col = len1;
    int row = len2;
    //保证最小的作为col
    if (len1 < len2) {
        cols = text2;
        rows = text1;
        col = len2;
        row = len1;
    }
    int *dp =  malloc(sizeof(int) * (col + 1));
    memset(dp, 0, sizeof(int) * (col + 1));
    int leftTop = 0;
    for (int i = 1; i <= row; i++) {
        int cur = 0;
        for (int j = 1; j <= col; j++) {
            leftTop = cur;
            cur = dp[j];
            if (rows[i-1] == cols[j-1]) {
                dp[j] = leftTop + 1;
            }else{
                //和二维数组左边和上边有关联
                dp[j] = MAX(dp[j], dp[j-1]);
            }
        }
    }
    return dp[col];
}


//最长公共子串
/*
 子串是连续的
 */
