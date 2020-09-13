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
//使用快速幂的方法
/*
 21 = 10101 = 2^4 + 2^2+ 2^0
 3^21 = (3^16)*(3^4)*(3^1)
 */
double Power2(double base, int exponent){
    long m = exponent > 0 ? exponent : -(long)exponent;//注意负数变正数时会溢出
    double res = 1;
    while (m > 0) {
        if (m & 1) {//二进制低位是否是1， 是的话和res相乘
            res = res * base;
        }
        base *= base;
        m = m >> 1;
    }
    return exponent > 0 ? res : 1.0/res;
}

/*扩展题： 求 (x^y) mod z
 注意： x^y的结果可能会很大，long类型也无法装下，不能先求x^y再 mod运算。
 但是有一个公式：(a * b) % p == ((a % p)  * (b % p)) % p
 so: 在快速幂的基础上
 */
double powMod(double x, int y, int z){
    if (x < 0 || y < 0 || z ==0) {
        return 0;
    }
    int res = 1;
    while (y > 0) {
        if (y & 1) {
            res = (res % z) * (x % z);
        }
        x = (x % z) * (x % z);
        y = y >> 1;
    }
    return res % z;
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
void perDown(int A[], int n, int i);
void topNSort(int A[], int N1, int B[], int N2){
    for(int i = N1/2-1; i >= 0; i--){
        perDown(A, N1, i);
    }
    //如果比最小的大则执行插入
    for (int i = 0; i < N2; i++) {
        if (B[i] > A[0]) {
            A[0] = B[i];
            perDown(A, N1, 0);
        }
    }
}
//构建小堆
void perDown(int A[], int n, int i){
    int root = A[i];
    int child = 0;
    for(; 2 * i + 1 < n; i = child){
        child = 2 * i  + 1;
        if(child + 1 < n && A[child+1] < A[child]){
            child = child + 1;
        }
        if(A[child] < root){
            A[i] = A[child];
        }else{
            break;
        }
    }
    A[i] = root;
    
}


//MARK:75. 颜色分类

/*
 给定一个包含红色、白色和蓝色，一共 n 个元素的数组，原地对它们进行排序，使得相同颜色的元素相邻，并按照红色、白色、蓝色顺序排列。
 此题中，我们使用整数 0、 1 和 2 分别表示红色、白色和蓝色。
 示例:
 输入: [2,0,2,1,1,0]
 输出: [0,0,1,1,2,2]
 
 [2 2 0]
 0: [0 2 2]
 1:
 */
void sortColors(int* nums, int numsSize){
    if(numsSize == 0 || numsSize == 1){
        return;
    }
    //双指针
    int left = 0;//指向下一个0的下标
    int right = numsSize-1;//指向下一个2的下标
    while (left < numsSize && nums[left] == 0) {
        left++;
    }
    while (right >= 0 && nums[right] == 2) {
        right--;
    }
    int i = left;
    while (i <= right) {//关键 易错点
        if (nums[i] == 0) {
            SwapArr(nums, left++, i++);
        }else if (nums[i] == 1){
            i++;
        }else{ // == 2
            //交换到i的可能是0， 这是还需要第一步的交换判断
            SwapArr(nums, right--, i);
        }
    }
}


//MARK:合并两个有序的数组
/*
 https://leetcode-cn.com/problems/merge-sorted-array
 给你两个有序整数数组 nums1 和 nums2，请你将 nums2 合并到 nums1 中，使 nums1 成为一个有序数组。
 说明:
 初始化 nums1 和 nums2 的元素数量分别为 m 和 n 。
 你可以假设 nums1 有足够的空间（空间大小大于或等于 m + n）来保存 nums2 中的元素。
 示例:
 输入:
 nums1 = [1,2,3,0,0,0], m = 3
 nums2 = [2,5,6],       n = 3
 输出: [1,2,2,3,5,6]
 */
void mergeTwoArray(int* nums1, int nums1Size, int m, int* nums2, int nums2Size, int n){
    //对两个数组逆序处理， cur表示(cur+1)之后都是排序好的
    //1. nums1[i] > nums2[j]时, 把nums1[i]放到 cur位置， cur--
    //2. nums1[i] < nums2[j]时, 把nums2[j]放到 cur位置， cur--
    if (n== 0) {
        return;
    }
    int i = m - 1;
    int j = n - 1;
    int cur = m + n - 1;
    while (j >= 0) {//会对比n次，因为有n个坑位
        if (i >= 0 && nums1[i] >= nums2[j]) {
            nums1[cur--] = nums1[i--];
        }else{
            nums1[cur--] = nums2[j--];
        }
    }
}


//MARK: 面试题 16.16. 部分排序
/*
 https://leetcode-cn.com/problems/sub-sort-lcci/
 给定一个整数数组，编写一个函数，找出索引m和n，只要将索引区间[m,n]的元素排好序，整个数组就是有序的。注意：n-m尽量最小，也就是说，找出符合条件的最短序列。函数返回值为[m,n]，若不存在这样的m和n（例如整个数组是有序的），请返回[-1,-1]。
 
 示例：
 输入： [1,2,4,7,10,11,7,12,6,7,16,18,19]
 输出： [3,9]
 */
int* subSort(int* array, int arraySize, int* returnSize){
    int *res = malloc(sizeof(int) * 2);
    *returnSize = 2;
    res[0] = -1;
    res[1] = -1;
    if(arraySize == 0){
        return res;
    }
    
    //顺序找到最后一个比左边最大元素的下标
    int r = -1;
    int max = array[0];
    for(int i = 1; i < arraySize; i++){
        if(array[i] >= max){
            max = array[i];
        }else{
            r = i;
        }
    }
    if(r == -1){
        return res;
    }
    
    //逆序找到最后一个比右边边最小元素的下标
    int l = -1;
    int min = array[arraySize - 1];
    for(int i = arraySize - 2; i >= 0; i--){
        if(array[i] <= min){
            min = array[i];
        }else{
            l = i;
        }
    }
    res[0] = l;
    res[1] = r;
    return res;
}



//MARK: 剑指 Offer 62. 圆圈中最后剩下的数字
//https://leetcode-cn.com/problems/yuan-quan-zhong-zui-hou-sheng-xia-de-shu-zi-lcof/
/*
 swift 版本： 超时
 func lastRemaining(_ n: Int, _ m: Int) -> Int {
    if n == 0 || m == 0{
        return -1
    }
    var res = Array<Int>(0..<n)
    while res.count > 1{
        let idx = (m-1) % res.count
         res.remove(at: idx)
         let pre = res[0..<(idx)]
         let last = res[idx..<res.count]
         res =  Array(last) + Array(pre)
     }
     return res[0]
 }
 
 //方法2 构建类似环形链表的结构（这里用数组来表示）
 func lastRemaining2(_ n: Int, _ m: Int) -> Int {
   if n == 0 || m == 0{
    return -1
   }
   var res = Array<Int>(0..<n)
   var idx = 0
   while res.count > 1{
      idx = (idx + m - 1) % res.count
      res.remove(at: idx)
    }
   return res[0]
 }
 */
/*
 这题是约瑟夫环问题
 f(n, m) = (f(n-1, m) + m) % n
 */












