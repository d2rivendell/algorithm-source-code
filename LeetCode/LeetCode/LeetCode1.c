//
//  LeetCode1.c
//  LeetCode
//
//  Created by leon on 2020/6/19.
//  Copyright © 2020 leon. All rights reserved.
//

#include "LeetCode1.h"
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <string.h>
#include <math.h>

#define DEL(x, y) (x > y ? x - y : y - x)
#define MIN(x, y) (x > y ? y : x)
#define MAX(x, y) (x > y ? x : y)
void SwapArr(int A[], int a, int b){
    int temp = A[a];
    A[a] = A[b];
    A[b] = temp;
}

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2){
    struct ListNode *head =  (struct ListNode *)malloc(sizeof(struct ListNode));
    struct ListNode *cur = head;
    int c = 0;
    while(cur != NULL){
        if (l1 != NULL){
            c += l1->val;
            l1 = l1->next;
        }
        if (l2 != NULL){
            c += l2->val;
            l2 = l2->next;
        }
        cur->val = c % 10;
        c /= 10;
        if (l1 != NULL || l2 != NULL || c){
            cur->next = (struct ListNode *)malloc(sizeof(struct ListNode));
        }
        cur = cur->next;
    }
    return head;
}


//字符串反转
void reverseString(char* s, int sSize){
    for(int i = 0; i < sSize/2; i++){
        char temp = s[i];
        s[i] = s[sSize - i - 1];
        s[sSize - i - 1] = temp;
    }
}

//MARK:最长不重复字符的长度
//abcbdb
int lengthOfLongestSubstring(char * s){
    //通过滑动窗口解决， 由start和i之间组成一个滑动窗口
    int *all =  malloc(sizeof(int) * 128);//保存字符最近的下标
    int start = 0;//当前窗口的开始位置
    int count = 0;//统计当前不相同的个数
    int max = 0;//当前最大不重复的个数
    int begin = 0;//最后用来打印的
    memset(all, -1, sizeof(int) * 128);
    for (int i = 0; i < strlen(s); i++) {
        if (all[s[i]] >= start){//和窗口范围内重复了(包括窗口边界start)
            start = all[s[i]]  + 1;//调整窗口位置,在重复的位置+1 ❗️
            count = i - start + 1;//调整当前count❗️
        }else{
            count += 1;
        }
        if(count > max){
            begin = start;
            max = count;
        }
        all[s[i]] = i;
    }
    for(int i = 0; i < strlen(s); i++){
        if(i >= begin && i < (begin + max)){
            printf("%c",s[i]);
        }
    }
    free(all);
    return max;
}


/*
 整数反转 给出一个 32 位的有符号整数，你需要将这个整数中每位上的数字进行反转。
 关键：正负号，溢出
 */
//MARK: - 整数反转
int reverse(int x) {
    int rev = 0;
    int INT_MAX = 0x7fffffff;//2147483647
    int INT_MIN = 0x80000000;//-2147483648
    int maxEnd = INT_MAX % 10;
    int minEnd = INT_MIN % 10;
    while (x != 0) {
        int pop = x % 10;
        x /= 10;
        // 正数：NT_MAX/10 == 214748364。 1. rev大于这个数，肯定溢出。 2.rev等于于这个数，余数大于7 也要溢出
        //负数同理
        if (rev > INT_MAX/10 || (rev == INT_MAX / 10 && pop > maxEnd)) return 0;
        if (rev < INT_MIN/10 || (rev == INT_MIN / 10 && pop < minEnd)) return 0;
        rev = rev * 10 + pop;//这里会溢出，累加之前做判断。
    }
    return rev;
}

//MARK: - 判断数字是否是回文数， 小于0不是（因为有符号），
int isPalindrome(int x){
    if(x < 0){
        return 0;
    }else{
        int count = 0;
        int value = x;
        int *arr = (int *)malloc(sizeof(int) * 10);//int不会超过10位
        while(value != 0){//数组逆序存起来（哪个顺序都一样，不影响结果）
            arr[count] = value % 10;
            value /= 10;
            count++;
        }
        //
        for(int i = 0; i < count/2; i++){
            if(arr[i] != arr[count-i-1]){
                return 0;
            }
        }
        free(arr);
        return 1;
    }
}

//61. 旋转链表。 给定一个链表，旋转链表，将链表每个节点向右移动 k 个位置，其中 k 是非负数。
//MARK: - 旋转链表
struct ListNode* rotateRight(struct ListNode* head, int k){
     //注意边界条件， 当为0或者是链表长度的时候，返回自身
      if(head == NULL){
          return NULL;
      }
      if (head->next == NULL){
          return head;
      }
      struct ListNode *p = head;
      int count = 1;
      //计算链表长度，并找到最后一个节点，让链表封闭起来（这样可以处理k==0,或者k==count的情况. 
      //返回之前会断开链表）
      while(p->next != NULL){
        count++;
        p = p->next;
      }
      struct ListNode *last = p;
      last->next = head;

      k  %= count;
      int step = count - k;
      p = head;
      for(int j = 0; j < step - 1; j++){
          p = p->next;
      }
       struct ListNode *next = p->next;
       p->next = NULL;// 断环
       return next;
       
}

/*
 给定 nums = [0,0,1,1,1,2,2,3,3,4],
 函数应该返回新的长度 5, 并且原数组 nums 的前五个元素被修改为 0, 1, 2, 3, 4。
 */
//MARK:- 26. 删除排序数组中的重复项
int removeDuplicates(int* nums, int numsSize){
   //数组是排序好的，左边的指针记录无重复的位置，也是最终的长度。 右边的指针相当于去试探。
   //当发现和慢指针位置的值不一样时就将其放在慢指针位置的后面，再把慢指针往后移动一位
   if(numsSize == 0 || numsSize == 1){
       return numsSize;
   }
   int slow = 0;
   for(int fast = 1; fast < numsSize; fast++){
      if(nums[slow] != nums[fast]){
          nums[slow++] = nums[fast];
      }
   }
   return slow + 1;
}

//MARK: 27. 就地移除指定的元素
//和上面26类似
int removeElement(int* nums, int numsSize, int val){
    //val是要移除的元素
    int cur = 0;
    for(int i = 0; i < numsSize; i++){
        if(nums[i] != val){
            nums[cur++] = nums[i];
        }
    }
    return cur;
}


//11. 盛最多水的容器
int area(int i, int j,int left, int right){
    return DEL(i, j) * MIN(left, right);
}

int maxArea(int* height, int heightSize){
    if(heightSize == 0){
        return 0;
    }
    int max = -1;
    int i = 0, j = 0;
    for( i = 0; i < heightSize - 1; i++){
        for( j = i + 1; j < heightSize; j++){
            int a =  area(i,j,height[i], height[j]);
            if(a > max){
                max = a;
            }
        }
    }
    return max;
}

//MARK: 204. 计数质数
int isPrime(int  n);

int countPrimes(int n){
    int count = 0;
    for(int i = 2; i < n; i++){
        if(isPrime(i) == 1){
            count++;
        }
    }
    return count;
}

int isPrime(int  n){
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return 0;
        }
    }
    return  1;
}

//MARK: 斐波那契数列
int climbStairs(int n){
    //0 1 1 2 3 5
    if (n == 0){
        return 0;
    }
    int stepOne = 0;
    int stepTwo = 1;
    int res = 0;
    for(int i = 0; i < n; i++){
        res = stepOne + stepTwo;
        stepOne = stepTwo;
        stepTwo = res;
    }
    return res;
}

//MARK: 剑指 Offer 16. 数值的整数次方
double PowerHelper(double base, int exponent){
    if (exponent == 0) {
        return 1;
    }
    double res = PowerHelper(base, exponent/2);//exponent==2时返回
    return exponent%2 == 0 ? res * res: res * res * base;
}
double Power(double base, int exponent){
    return exponent > 0 ? PowerHelper(base, exponent) : 1.0/PowerHelper(base, -exponent) ;

}


//MARK: 4. 寻找两个正序数组的中位数
//给定两个大小为 m 和 n 的正序（从小到大）数组 nums1 和 nums2。请你找出这两个正序数组的中位数，
//并且要求算法的时间复杂度为 O(log(m + n))。
double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size){
    //
    int mid = (nums1Size + nums2Size)/2;
    int isDoubleValue = (nums1Size + nums2Size) % 2 == 0;
    if (isDoubleValue) mid--;//中位数有两个，令中位数为遍历方向靠前的一位
    int i = nums1Size-1;//从最后一位开始遍历
    int j = nums2Size-1;//从最后一位开始遍历
    int count = 0;//记录当前是第几个数
    double val = 0;//第一个中位数
    double otherVal = 0;//第二个中位数
    int getFirstTurn = 0;//用来找第二个中位数标记
    while(count++ <= mid){
        int a = -1;
        int b = -1;
        if(i >= 0)  a = nums1[i];
        if(j >= 0)  b = nums2[j];
        if(a > b){
            if(getFirstTurn == 0){
                val = a;
            }else{//现在是在找前一个数
                getFirstTurn = 0;
                otherVal = a;
                isDoubleValue = 0;
            }
            i--;
        }else{
            if(getFirstTurn == 0){
                 val = b;
            }else{//现在是在找前一个数
                getFirstTurn = 0;
                otherVal = b;
                isDoubleValue = 0;
            }
            j--;
        }
        if(count+1 > mid && isDoubleValue == 1 ){//只找到了一个，还有前一个
            count -= 1;
            getFirstTurn = 1;
        }
    }
    otherVal = otherVal == 0 ? val : otherVal;
    return (val + otherVal)/2.0;
}

//MARK: 剑指 Offer 29. 顺时针打印矩阵
int* spiralOrder(int** matrix, int matrixSize, int* matrixColSize, int* returnSize){
    if(matrixSize == 0){
        *returnSize = 0;
        return NULL;
    }
    int l = 0;
    int r = matrixColSize[0] - 1;//是col
    int t = 0;
    int b = matrixSize - 1;//是row
    printf("l: %d, r: %d, t:%d, b:%d \n", l, r, t, b);
    int *res= malloc(sizeof(int) * matrixColSize[0] * matrixSize);
    *returnSize  = matrixColSize[0] * matrixSize;
    int k = 0;
    while(1){
        printf("//从左到右,由left开始\n");
        for(int i = l; i <= r; i++) res[k++] = matrix[t][i];
        t += 1;
        if(t > b) break;//遍历完了
        
        printf("//从上到下,由top开始\n");
        for(int i = t; i <= b; i++) res[k++] = matrix[i][r];
        r -= 1;
        if(r < l) break;//遍历完了
        
        printf("//从右到左,由right开始\n");
        for(int i = r; i >= l; i--) res[k++] = matrix[b][i];
        b -= 1;
        if(t > b) break;//遍历完了
        
        printf("//从下到上,由bottom开始\n");
        for(int i = b; i >= t; i--) res[k++] = matrix[i][l];
        l += 1;
        if(r < l) break;//遍历完了
    }
    return res;
}

//MARK: 剑指 Offer 15. 二进制中1的个数
int hammingWeight(uint32_t n) {
    uint32_t mask = 0x01;
    int count = 0;
    int i = 32 - 1;
    while(i-- >= 0){
        if(n & mask)count++;
        n = n>>1;
    }
    return count;
}

//MARK: 剑指 Offer 05. 替换空格
char* replaceSpace(char* s){
    if(s == NULL){
        return NULL;
    }
    int len = 0;
    int finalLen = 0;
    int blankLen = 0;
    int i = 0;
    while(s[i] != '\0'){
        len++;
        if(s[i] == ' ')
            blankLen++;
        i++;
    }
    finalLen = len + blankLen * 2;
    printf("original: %d, final: %d\n", len, finalLen);
    char *res = (char *)malloc(sizeof(char) * (finalLen + 1));
    res[finalLen] = '\0';
    //双指针
    i = len-1;
    int j = finalLen-1;
    while(i >= 0){
        if(s[i] == ' '){
            res[j--] = '0';
            res[j--] = '2';
            res[j--] = '%';
        }else{
            res[j--] = s[i];
        }
        printf("+ %c\n",s[i]);
        i--;
    }
    return res;
}



//MARK: 剑指 Offer 21. 调整数组顺序使奇数位于偶数前面
//[奇数, 偶数]
int* exchange(int* nums, int numsSize, int* returnSize){
    int i = 0;
    int j = numsSize - 1;
    //[1,2,3,4]
    while(i < j){
        while(nums[i] % 2 != 0 && i < j){
            i++;
        }
        while(nums[j] % 2 == 0 && i < j){
            j--;
        }
        SwapArr(nums, i, j);
    }
    *returnSize = numsSize;
    return nums;
}


//MARK:  剑指 Offer 50. 第一个只出现一次的字符
char firstUniqChar(char* s){
    /*
      1. memset 的大小包括  sizeof(char) * size！！而不是size!
      2. " "和 ' '是不一样的
      3. strlen长度不包括'\0'
     */
    int size = 128;
    int *all = (int *)malloc(sizeof(int) * size);
    memset(all, -1, sizeof(int) * size);
    unsigned long len = strlen(s);//strlen长度不包括'\0'
    for(unsigned i = 0; i < len; i++){
        all[s[i]] += 1;
    }
    for(unsigned i = 0; i < len; i++){
        if(all[s[i]] == 0){
            free(all);
            return s[i];
        }
    }
    free(all);
    return ' ';
}

//MARK: 剑指 Offer 03. 数组中重复的数字
int findRepeatNumber(int* nums, int numsSize){
    //malloc 的size要注意是什么
    int  maxSize = 100000;
    int *record = malloc(sizeof(int) * maxSize);
    memset(record, 0 , maxSize);
    for(int i = 0; i <= numsSize; i++){
        if(record[nums[i]] > 0){
            free(record);
            return nums[i];
        }else{
            record[nums[i]] += 1;
        }
    }
    return 0;
}

//MARK: 88. 合并两个有序数组
//插入排序
void merge(int* nums1, int nums1Size, int m, int* nums2, int nums2Size, int n){
    if(n == 0){
        return;
    }
    int j = 0;
    int k = 0;
    for(int i = m; i < m + n; i++){
        if(j++ < n){
            int temp = nums2[i - m];
            for( k = i; k > 0; k--){
                if(temp < nums1[k - 1]){
                    nums1[k] = nums1[k-1];
                }else{
                    break;
                }
            }
            nums1[k] = temp;
        }
    }
}

//MARK:- 26. 删除排序数组中的重复项
// 1 2 2 3 4 4 5
int removeDuplicates2(int* nums, int numsSize){
    if(numsSize == 0 || numsSize == 1){
        return numsSize;
    }
    int i = 0;
    int j = 1;
    while(j < numsSize){
        if (nums[j] != nums[i]){
            int temp = nums[i + 1];
            nums[i + 1] = nums[j];
            nums[j] = temp;
            i++;
        }
        j++;
    }
    return i + 1;
}


//素数对， 给定一个整形数字 3<= n <= 1000。找出有多少对素素加起来正好等于n
int isPrimeNumber(int n){
    for(int i = 2; i * i <= n; i++){
        if(n % i == 0){
            return 0;
        }
    }
    return 1;
}
int primeCount(int n){
    int mid = n/2;
    int count = 0;
    for(int i = 2; i <= mid; i++){
        if( isPrimeNumber(i) && isPrimeNumber(n-i) )
            count++;
    }
    return count;
}

//腾讯面试题 "I am a Student."

//MARK: 151. 翻转字符串里的单词
void reversSingle(char *s, int left, int right){
    for(int i = 0; i < (right - left + 1)/2; i++){
        char temp = s[left + i];
        s[left + i] = s[right - i];
        s[right - i] = temp;
    }
}
char * reverseWords(char * s){
    if(s == NULL){
        return s;
    }
    int len =  (int)strlen(s);
    //step 1. 原地去除空格两边和中间多余的空格
    int cur = 0;//cur之前的字符是处理过的，这个也是最终的字符串长度
    int preIsSpace = 1;//前一个是否是空格,根据这个来判断是否该往前移动
    // hello  word
    for(int i = 0;i < len; i++){
        if(s[i] != ' '){//当前不是空格
            preIsSpace = 0;
            s[cur++] = s[i];
        }else if(preIsSpace == 0){//当前不是空格,前一个也不是空格
            preIsSpace = 1;
            s[cur++] = s[i];
        }else{//当前是空格，前面一个是空格
            //什么也不做，让i往前移动，
        }
    }
    if(cur == 0){//说明全部是空字符串
        return "";
    }
    len = preIsSpace == 1 ? cur - 1 : cur; //把最后一个可能是空格的忽略掉
    s[len] = '\0';
    
    //step2: 翻转整个字符串
    //核心是找到空格的位置
    reversSingle(s, 0, len - 1);
    
    //step: 3对内部单个单词进行翻转
    int left = 0;
    for (int i = 0; i < len; i++) {
        if(s[i] != ' ') continue;//找到是空格为止
        reversSingle(s, left, i-1);
        left = i+1;//left指向空格的下一个字符
    }
    reversSingle(s, left, len - 1);//最后一个需要单独在外面进行翻转
    
// 下面的方式
//    int left = 0;
//    int right = 0;
//    while(right + 1 < len && s[right + 1] != ' ' ){
//        right++;
//    }
//    //step: 3对内部单个单词进行翻转
//    while(right < len){
//        reversSingle(s, left, right);
//        right += 2;
//        left = right;
//        while((right + 1 < len && s[right + 1] != ' ') ){
//            right++;
//        }
//    }
    return s;
}


//MARK:两个栈处理翻转
#define NOTFOUND '~'
typedef  char StackElement;
struct MyStack {
    StackElement *elements;
    int size;
    int cur;//当前的个数
};

struct MyStack * MyStackMake(int count){
    if (count <= 0) {
        return NULL;
    }
    struct MyStack *stack =  malloc(sizeof(struct MyStack));
    StackElement *elements = malloc(sizeof(StackElement) * count);
    memset(elements, 0, count);
    stack->elements = elements;
    stack->size = count;
    stack->cur = 0;
    return  stack;
}


int stackIsEmpty(struct MyStack *stack){
    if (stack->cur == 0) {
        return 1;
    }
    return 0;
}
int stackIsFull(struct MyStack *stack){
    if (stack->cur == stack->size) {
        return 1;
    }
    return 0;
}
StackElement MyStackPop(struct MyStack *stack){
    if (stackIsEmpty(stack))  {
        return NOTFOUND;
    }else{
        stack->cur--;
        return stack->elements[stack->cur];
    }
}
void MyStackPush(struct MyStack *stack, StackElement v){
    if (stackIsFull(stack)) {
        return ;
    }else{
        stack->cur++;
        stack->elements[stack->cur-1] = v;
    }
}

StackElement MyStackTop(struct MyStack *stack){
    if (stackIsEmpty(stack)) {
        return NOTFOUND;
    }else{
        return stack->elements[stack->cur-1];
    }
}


//"I am a Student."
//tnedutS a ma I
//使用两个栈来操作
void revertStr(char *s){
    int len = (int)strlen(s);
    struct MyStack *stack =  MyStackMake(len);
    for (int i = 0; i < len; i++) {
        if (s[i] == ' ') {
            //栈为空且上一个是空格时，不会存储空格
            if (MyStackTop(stack) != ' ' && !stackIsEmpty(stack))  MyStackPush(stack, s[i]);
        }else{
            MyStackPush(stack, s[i]);
        }
    }
    while (MyStackTop(stack )== ' ') {//去除末位空格
        MyStackPop(stack);
    }
    int find = 0;
    if (MyStackTop(stack) == '.') {
        find = 1;
        MyStackPop(stack);
    }
    struct MyStack *res =  MyStackMake(len);
    char *ss = malloc(sizeof(char) * len + 1);
    int k = 0;
    while (!stackIsEmpty(stack)) {
        if (MyStackTop(stack) == ' ') {
            while (stackIsEmpty(res) == 0) {
                ss[k++] = MyStackPop(res);
            }
            ss[k++] = MyStackPop(stack);
        }else{
            MyStackPush(res, MyStackPop(stack));
        }
    }
    while (stackIsEmpty(res) == 0) {
        ss[k++] = MyStackPop(res);
    }
    if (find) {
        ss[k++] = '.';
    }
    ss[k++] = '\0';
    printf("\n");
    printf("%s\n",ss);
}


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
