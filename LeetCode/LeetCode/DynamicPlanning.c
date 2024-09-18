//
//  DynamicPlanning.c
//  LeetCode
//
//  Created by leon on 2020/8/23.
//  Copyright © 2020 leon. All rights reserved.
//

#include <stdio.h>
#include "LeetCode.h"
void freedp(int **dp, int rows){
    for(int i = 0; i < rows; i++){
        printf("%d ", i);
        free(dp[i]);
    }
    free(dp);
}

//MARK: 找零钱 --动态规划法
//money：要找的零钱；A: 现有的零钱数组, 是排序好的；N：零钱的张数
/*
 找到返回最小零钱的张数，找不到返回-1
 dp[i]表示找到i块钱需要最小的张数。
 初始：dp[0] = 0; (重要， 因为c等于i的时候)
 对于i位置， 如果c<=i(小于等于才能找),dp[i - c]存在
 dp[i] = dp[i-c] + 1
 */
int coins(int money, int A[], int changeCount){
    if (money == 0) {
        return -1;
    }
    //dp[i]表示要找到零钱为i的最小的张数
    int dp[money + 1];
    // faces[i]是凑够i分时最后那枚硬币的面值
    int faces[money + 1];
    //自底向上
    dp[0] = 0;//关键！！！如果i-c == 0, 让下面的if也能为true
    for(int i = 1; i <= money; i++){
        faces[i]  =  0;
        dp[i] = -1;
        int min = 0x7fffffff;
        for(int j = 0; j < changeCount; j++){
            int c = A[j];
            if(c > i) continue;
            if(dp[i-c] >= 0 && dp[i-c] < min){
                min = dp[i - c];
                faces[i] = c;
            }
        }
        if(min != 0x7fffffff){
            dp[i] = min + 1;
        }
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
 

 dp[i][j]要参考 dp[i+1][i-1]即左下角的值， 因此， 要一列一列的填写：
 对列升序，再对每一行升序
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
/*
 0 0 0 0
 0 0 0 0
 0 0 0 0
 */
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
    for (int i = 0; i < row; i++) {//遍历之前皇后的位置
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
 https://leetcode.cn/problems/longest-common-subsequence/description/
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



//MARK: 买卖股票最佳时机
/*
 https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock
 给定一个数组，它的第 i 个元素是一支给定股票第 i 天的价格。
 你只能选择`某一天`买入这只股票，并选择在`未来的某一个不同的日子`卖出该股票。设计一个算法来计算你所能获取的最大利润。
 如果你最多只允许完成一笔交易（即买入和卖出一支股票一次），设计一个算法来计算你所能获取的最大利润。
 注意：你不能在买入股票前卖出股票
 示例 1:
 输入: [7,1,5,3,6,4]
 输出: 5
 
 示例 2:
 输入: [7,6,4,3,1]
 输出: 0
 解释: 在这种情况下, 没有交易完成, 所以最大利润为 0。
 */
int maxProfit(int* prices, int pricesSize){
    if(pricesSize == 0){
        return 0;
    }
    int max = 0x80000000;
    int lowestPrice = 0x7fffffff;
    for(int i = 0; i < pricesSize; i++){
        lowestPrice = MIN(prices[i], lowestPrice);
        max = MAX(prices[i] - lowestPrice, max);
    }
    return max;
}
/*
 买卖股票 问题可以转成动态规划问题：
 第i天买，第j天卖的利润是
 第i~j天内，所有相邻两天股价差的和
 ｜0 ｜1 ｜2 ｜3 ｜4 ｜5 ｜
 ｜7 ｜1 ｜5 ｜3 ｜6 ｜4 ｜
 转成：
 ｜0～1｜1 ～2｜2 ～3｜3 ～4｜4 ～5｜
 ｜-6  ｜ 4  ｜  -2 ｜  3  ｜ -2 ｜
 问题就变成求连续子序列最大和问题
 
 */
int maxProfitdp(int* prices, int pricesSize){
    if(pricesSize == 0 || pricesSize == 1){
        return 0;
    }
    int *detals = malloc(sizeof(int) * (pricesSize - 1));
    for(int i = 1; i < pricesSize; i++){
        detals[i - 1] = prices[i] - prices[i-1];
    }
    int dp = detals[0];
    int max = dp;
    for(int i = 1; i < pricesSize - 1; i++){
        if(dp >= 0){
            dp += detals[i];
        }else{
            dp = detals[i];
        }
        max = MAX(dp, max);
    }
    free(detals);
    return MAX(max, 0);
}


//MARK: 72. 编辑距离
/*
 https://leetcode-cn.com/problems/edit-distance/
 给你两个单词 word1 和 word2，请你计算出将 word1 转换成 word2 所使用的最少操作数 。
 
 你可以对一个单词进行如下三种操作：
 
 插入一个字符
 删除一个字符
 替换一个字符
  
 示例 1：
 
 输入：word1 = "horse", word2 = "ros"
 输出：3
 解释：
 horse -> rorse (将 'h' 替换为 'r')
 rorse -> rose (删除 'r')
 rose -> ros (删除 'e')
 
 定义状态：
 假设字符串1"mice"为s1，它的长度为n1；字符串"arise"为s2，它的长度为n2
 dp是大小为 (n1 + 1) * (n2 + 1)的二维数组
 dp[i][j]是s1[0,i)转换成s2[0, j)的最少操作数 (注意是左闭右开)
 具体如minDistance.png所示
 
 状态转移方程：
 初始时：
 dp[0][0] = 0 -> 空串转空串
 dp[i][0] = i -> s1[0, i)转成空串
 dp[0][j] = j -> 空串转成s2[0, i)
 
 对于 s1[0, i)和s2[0, j)分四种情况讨论：
 1 (删). 删除s1[0, i)最后一个字符-->s1[0, i-1)，再转成s2[0, j), dp[i][j] = 1 + dp[i-1][j]
 2（增）. s1[0, i)转成-->s2[0, j-1)，再插入一个字符转成s2[0, j), dp[i][j] = 1 + dp[i][j-1]
 3（改）.
    (1)  s1[0, i).count == s2[0, j).count时
         s1[i-1] != s2[j-1],  dp[i][j] = dp[i-1][j-1]
    (2)  s1[0, i).count != s2[0, j).count时
         s1[i-1] != s2[j-1],  dp[i][j] = 1 + dp[i-1][j-1]
 
 1、2、3三种情况取最小值就是所求 dp[i][j]
 */
int minDistance(char * word1, char * word2){
    int rows = (int)strlen(word1);
    int cols = (int)strlen(word2);
    int **dp = malloc(sizeof(int *) * (rows + 1));
    for(int i = 0; i < rows + 1;i++){
        dp[i] = malloc(sizeof(int) * (cols + 1));
        memset(dp[i], 0, sizeof(int) * (cols + 1));
        dp[i][0] = i;
        if(i == 0){
            for(int j = 0; j < cols + 1;j++){
                dp[0][j] = j;
            }
        }
    }
    for(int i = 1; i < rows + 1;i++){
        for(int j = 1; j < cols + 1; j++){
            int top = dp[i-1][j] + 1;//删除
            int left = dp[i][j-1] + 1;//增加
            int leftTop = dp[i-1][j-1];
            if(word1[i-1] != word2[j-1]){
                leftTop++; // 替换
            }
            dp[i][j] = MIN(MIN(leftTop, top), left);
        }
    }
    int max = dp[rows][cols];
    freedp(dp, rows);
    return max;
}


//MARK: 背包问题
int knapsack(int *values, int v, int *weights, int w, int capacity) {
    /*
     dp[i][j]表示有前j件物体可选，最大承重是j时， 背包的总最大价值
     初始：dp[0][j] = 0 , dp[i][0] = 0;
     对于一个物体，想要不要选需要判断选和不选时哪个结果的价值更大
     dp[i][j] = max(dp[i-1][j], dp[value[i-1]][weights[j] - j] + values[j])
    */
    int dp[v+1][capacity+1];
    for (int i = 0; i < v + 1; i++) {// 遍历每个物体
        for (int j = 0; j < capacity + 1; j++) { //遍历的是背包的容量不是物品的重量
            if (i == 0 || j == 0) {
                dp[i][j] = 0;
                continue;;
            }
            int currentWeight = weights[i - 1];
            if (currentWeight > j) { //一个物体的重量大于背包的容量，不能选！
                dp[i][j] = dp[i-1][j];
            } else { //当前能选
                //判断选和不选哪个更大
                dp[i][j] = MAX(dp[i-1][j], dp[i - 1][j - currentWeight] + values[i-1]);
            }
        }
    }
    return dp[v][capacity];
}

//MARK: 198. 打家劫舍
/*https://leetcode-cn.com/problems/house-robber
 如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警。
 输入：[1,2,3,1]
 输出：4
 解释：偷窃 1 号房屋 (金额 = 1) ，然后偷窃 3 号房屋 (金额 = 3)。
      偷窃到的最高金额 = 1 + 3 = 4
 */
int rob(int* nums, int numsSize){
    /*
      dp[0] = nums[0]
      dp[1] = max(nums[0], nums[1])
      dp[i] = max(dp[i-2]+nums[i], nums[i-1])
    */
    if (numsSize == 0) return  0;
    if (numsSize == 1) return nums[0];
    int dp[numsSize];
    dp[0] = nums[0];
    dp[1] = MAX(nums[0], nums[1]);
    for(int i = 2;  i < numsSize; i++) {
        dp[i] = MAX(dp[i-2] + nums[i], dp[i-1]);
    }
    return dp[numsSize - 1];
}
