//
//  NumberArray.c
//  LeetCode
//
//  Created by leon on 2020/8/23.
//  Copyright © 2020 leon. All rights reserved.
//

#include <stdio.h>
#include "LeetCode.h"


void SwapArr(int A[], int a, int b){
    int temp = A[a];
    A[a] = A[b];
    A[b] = temp;
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
 整数反转 给出一个 32 位的有符号整数，你需要将这个整数中每位上的数字进行反转。
 关键：正负号，溢出
 */
//MARK: - 整数反转
int reverse(int x) {
    int rev = 0;
    int int_max = 0x7fffffff;//2147483647
    int int_min = 0x80000000;//-2147483648
    int maxEnd = int_max % 10;
    int minEnd = int_min % 10;
    while (x != 0) {
        int pop = x % 10;
        x /= 10;
        // 正数：NT_MAX/10 == 214748364。 1. rev大于这个数，肯定溢出。 2.rev等于于这个数，余数大于7 也要溢出
        //负数同理
        if (rev > int_max/10 || (rev == int_max / 10 && pop > maxEnd)) return 0;
        if (rev < int_min/10 || (rev == int_min / 10 && pop < minEnd)) return 0;
        rev = rev * 10 + pop;//这里会溢出，累加之前做判断。
    }
    return rev;
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




/*
 有20 个数组，每个数组有500 个元素，并且是有序排列好的，现在在这20*500 个数中找出排名前500 的数。

 这是一个TOP-N问题，用个数为N的最小堆来解决。
 首先读入第一数组的500个数来创建大小为500的小顶堆，建堆的时间复杂度为O(mlogm)(m为数组的大小即为500 ），然后遍历后续19个数组，并与堆顶（最小）元素进行比较。如果比最小的数小，则继续读取后续数字；如果比堆顶的数字大，则替换堆顶元素并重新调整堆为小顶堆。整个过程直至20个数组全部遍历完一遍为止。然后按照中序遍历的方式输出当前堆中的所有500个数字。
 */
