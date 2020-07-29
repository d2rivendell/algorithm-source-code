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

//最长不重复字符的长度
int lengthOfLongestSubstring(char * s){
    //通过滑动窗口解决， 由start和i之间组成一个滑动窗口
    int *all =  malloc(sizeof(int) * 128);//保存字符最近的下标
    int start = 0;//当前窗口的开始位置
    int count = 0;//统计当前不相同的个数
    int max = 0;//当前最大不重复的个数
    
    memset(all, -1, sizeof(int) * 128);
    for (int i = 0; i < strlen(s); i++) {
        if (all[s[i]] >= start){//和窗口范围内重复了(包括窗口边界start)
            start = all[s[i]]  + 1;//调整窗口位置,在重复的位置+1 ❗️
            count = i - start + 1;//调整当前count❗️
        }else{
            count += 1;
        }
        max = (count > max) ? count : max;
        all[s[i]] = i;
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
    while (x != 0) {
        int pop = x % 10;
        x /= 10;
        // 正数：NT_MAX/10 == 214748364。 1. rev大于这个数，肯定溢出。 2.rev等于于这个数，余数大于7 也要溢出
        //负数同理
        if (rev > INT_MAX/10 || (rev == INT_MAX / 10 && pop > 7)) return 0;
        if (rev < INT_MIN/10 || (rev == INT_MIN / 10 && pop < -8)) return 0;
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


/*
 给定一个字符串 s，找到 s 中最长的回文子串。你可以假设 s 的最大长度为 1000。
 
 示例 1：

 输入: "babad"
 输出: "bab"
 注意: "aba" 也是一个有效答案
 https://leetcode-cn.com/problems/longest-palindromic-substring/
 */
char * longestPalindrome(char * s){
    int len = strlen(s);
    int w1 = 0, w2 = 0;
    char *temp = (char *) malloc(sizeof(char) * len);
    int i = 0;
    for(i = 0; i < len; i++){
        
    }
    free(temp);
    return "";
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
   //数组是排序好的，左边的指针记录z无重复的， 右边的指针相当于去试探。
   //当发现和慢指针位置的值不一样时就将其放在慢指针位置的后面，再把慢指针往后移动一位
   if(numsSize == 0 || numsSize == 1){
       return numsSize;
   }
   int slow = 0;
   for(int fast = 1; fast < numsSize; fast++){
      if(nums[slow] != nums[fast]){
          nums[slow + 1] = nums[fast];
          slow += 1;
      }
   }
   return slow + 1;
}


//11. 盛最多水的容器
#define DEL(x, y) (x > y ? x - y : y - x)
#define MIN(x, y) (x > y ? y : x)
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
