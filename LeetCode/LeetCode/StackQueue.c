//
//  StackQueue.c
//  LeetCode
//
//  Created by leon on 2020/9/2.
//  Copyright © 2020 leon. All rights reserved.
//

#include "LeetCode.h"

//MARK: 739. 每日温度
/*
 https://leetcode-cn.com/problems/daily-temperatures
 
 请根据每日 气温 列表，重新生成一个列表。对应位置的输出为：要想观测到更高的气温，至少需要等待的天数。如果气温在这之后都不会升高，请在该位置用 0 来代替。

 例如，给定一个列表 temperatures = [73, 74, 75, 71, 69, 72, 76, 73]，你的输出应该是 [1, 1, 4, 2, 1, 1, 0, 0]。

 提示：气温 列表长度的范围是 [1, 30000]。每个气温的值的均为华氏度，都是在 [30, 100] 范围内的整数。

 */
int* dailyTemperatures(int* T, int TSize, int* returnSize){//时间复杂度有点高
    if (TSize == 0) {
        *returnSize = 0;
        return NULL;
    }
    //stack存放的是递减的元素的【下标】
    int *stack = malloc(0);
    int stk_top = 0;
    
    int *res = malloc(sizeof(int) * TSize);
    memset(res, 0,sizeof(int) * TSize);
    *returnSize = TSize;//大小和原数组一样大
    for(int i = 0; i < TSize; i++){
        //发现当前i位置的元素比栈里面的大，则将栈里面的弹出， 并计算下标的差值
        while(stk_top > 0 && T[i] > T[stack[stk_top - 1]]){
            //出栈
            int smallValueIndex = stack[--stk_top];
            //计算下标差值
            res[smallValueIndex] = i - smallValueIndex;
        }
        //入栈
        stk_top++;
        stack = realloc(stack, sizeof(int) * stk_top);
        stack[stk_top-1] = i;
    }
    free(stack);
    return res;
}

//倒推法，反向开始,  类似动态规划
/*
- i用来扫描所有的元素，从右往左扫描（ 逐渐递减），一开始i指向倒数第2个元素

- 对于每一个i ，一开始令 j = i + 1
  ① 如果 T[i] < T[j]那么values[j] = j - i 然后i--
  ② 如果 T[i] == T[j]
        如果values[j] == 0, 那么values[i] == 0,然后i--
        如果values[j] != 0, 那么values[i] == values[j] + j - i,然后i--
  ③  如果 T[i] > T[j] 否则，
        如果T[j] == 0;  说明j的右边没有任何一个数字比i大， values[i] = 0; 然后ii--
        如果T[j] != 0; 设置j = j + values[j], 找比j大的下一个值，和i再比较。回到步骤①
 */
int* dailyTemperatures2(int* T, int TSize, int* returnSize){
    if(TSize == 0){
           *returnSize = 0;
           return NULL;
       }
       int *res = malloc(sizeof(int) * TSize);
       memset(res, 0, sizeof(int) * TSize);
       *returnSize = TSize;
       res[TSize-1] = 0;
       int l = 0, r = 0;
       for(int i = TSize - 2; i >= 0; i--){
           l = i;
           r = i + 1;
           while(r < TSize){
              if(T[l] < T[r]){
                    res[l] = r - l;
                    break;
               }else if(T[l] > T[r] && (res[r] > 0)){ // res[r] > 0确保不会死循环
                    //l可能小于r后面的,找到那个位置
                    r = res[r] + r;
               }else{// ==
                   // 此时r和l不一定是相邻的
                   res[l] = (res[r] == 0 ? 0 : res[r] + r - l);
                   break;
               }
           }
       }
       return res;
 
}


//MARK:654. 最大二叉树
/*
 最大二叉树是指越往根节点，值越大？
 给定一个不含重复元素的整数数组。一个以此数组构建的最大二叉树定义如下：
 
 二叉树的根是数组中的最大元素。
 左子树是通过数组中最大值左边部分构造出的最大二叉树。
 右子树是通过数组中最大值右边部分构造出的最大二叉树。
 通过给定的数组构建最大二叉树，并且输出这个树的根节点。
 
 示例 ：
 输入：[3,2,1,6,0,5]
 输出：返回下面这棵树的根节点：
 
    6
 /    \
3      5
 \    /
  2  0
   \
    1
 
 */
struct TreeNode*  constructMaximumBinaryTreeHelper(int* nums, int left, int right);
struct TreeNode* constructMaximumBinaryTree(int* nums, int numsSize){
    if(numsSize == 0){
        return NULL;
    }
    return constructMaximumBinaryTreeHelper(nums, 0,  numsSize -  1);
}

struct TreeNode*  constructMaximumBinaryTreeHelper(int* nums, int left, int right){
    if(left > right){
        return NULL;
    }
    int maxIdx = left;;
    for(int i = left; i <= right; i++){
        if(nums[i] > nums[maxIdx]) maxIdx = i;
    }
    struct TreeNode *node = malloc(sizeof(struct TreeNode));
    node->val = nums[maxIdx];
    node->left = constructMaximumBinaryTreeHelper(nums, left, maxIdx-1);
    node->right = constructMaximumBinaryTreeHelper(nums, maxIdx+1, right);
    return node;
}

/*
 在上面这道题目延伸出来的变种题目
 返回一个数组，数组里面存储着每个节点的父节点的索引， 如果节点没有父节点则用-1索引表示
 
 输入：[3,2,1,6,0,5]
 返回：[3,0,1,-1,5,3]
 思路： 找到 一个元素的左边第一个比它大的值， 和右边第一个比它大的值。取较小那个就是它的父节点，
 因为更大那个是它更上一层的节点，可能是爷爷节点。
 借鉴滑动窗口maxSlidingWindow的思路，利用一个递减的栈来处理大小对比的问题。
 比如：
 1. 根据提供的数组元素入栈，保证是逐步递减的，这时栈里面有[3,2,1]
 2. 下一个元素遇到6的时候，弹出比6栈小的元素， 这时可以计算出3，2，1的右边第一个大的元素是6， 1左边最大元素是2， 3左边没有最大元素。
 3. 直到栈里面没有比6小的元素为止 再继续入栈6。 再这样以此类推。
 */
int *parentIndexes(int* nums, int numsSize){
    //保存每个元素最左边第一个比它大的值的下标
    int *lmax = malloc(sizeof(int) *numsSize);
     //保存每个元素最右边第一个比它大的值的下标
    int *rmax = malloc(sizeof(int) *numsSize);
    for (int i = 0; i < numsSize; i++) {
        lmax[i] = -1;
        rmax[i] = -1;
    }
    // 保存降序元素的下标
    int *stack = malloc(0);
    int stk_top = 0;
    for (int i = 0; i < numsSize; i++) {
        //出栈
        while (stk_top >0 && nums[i] > nums[stack[stk_top-1]]) {
            int x = stack[--stk_top];
            rmax[x] = i;
        }
        
        if (stk_top > 0) {//入栈前判断不为空的话，栈顶的元素的下标就是i位置的元素的左边第一个比它大的值的下标
            lmax[i] = stack[stk_top-1];
        }
        //入栈
        stk_top++;
        stack = realloc(stack, sizeof(int) * stk_top);
        stack[stk_top-1] = i;
    }
    
    //对比每个元素的左右最大的元素，找到较小的那个
    int *res = malloc(sizeof(int) *numsSize);
    memset(res, 0, sizeof(int) * numsSize);
     for (int i = 0; i < numsSize; i++) {
         int l = lmax[i];
         int r = rmax[i];
         if (l == -1) {
             res[i] = r;
         }else if (r == -1){
             res[i] = l;
         }else if(l == -1 && r == -1){//根节点就是最大的
             res[i] = -1;
         }else{//
             if (nums[l] < nums[r]) {
                 res[i] = l;
             }else{
                 res[i] = r;
             }
         }
     }
    return res;
}

//MAARK: 20. 有效的括号
/*https://leetcode-cn.com/problems/valid-parentheses
 给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串，判断字符串是否有效。
 有效字符串需满足：
 左括号必须用相同类型的右括号闭合。
 左括号必须以正确的顺序闭合。
 注意空字符串可被认为是有效字符串。
 示例 1:
 输入: "()"
 输出: true
 */
bool isBracketsValid(char * s){
    if(s == NULL) return true;
    int n = strlen(s);
    //只保存'{'、'['、'('字符，遇到对应的右半边后出栈
//    char *stack = malloc(0)
    char stack[n];//在leetCode上使用空间更小
    int stk_top = 0;
    for(int i = 0; i < n; i++){
        char c = s[i];
        if (c == ')' || c == '}' || c == ']'){
            char map = '(';
            if(c == '}'){
                map = '{';
            }else if (c == ']'){
                map = '[';
            }
            //栈为空 或者栈顶和当前字符不匹配
            if(stk_top < 1 || map != stack[stk_top-1]){
                return false;
            }else{//qu
                stk_top--;
            }
        }else if(c == '(' || c == '[' || c == '{'){
            //    stack = realloc(stack, sizeof(char) * (++stk_top));
            ++stk_top;
            stack[stk_top-1] = c;
        }
    }
    //栈不为空说明符号不成对，不是有效的
    return stk_top == 0;
}
