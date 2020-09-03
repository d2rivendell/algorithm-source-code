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
    //stack存放的是下标
    int *stack = malloc(0);
    int stk_top = 0;
    
    int *res = malloc(sizeof(int) * TSize);
    memset(res, 0,sizeof(int) * TSize);
    *returnSize = TSize;
    for(int i = 0; i < TSize; i++){
        while(stk_top > 0 && T[i] > T[stack[stk_top - 1]]){
            //出栈
            int smallValueIndex = stack[--stk_top];
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

//反向开始
int* dailyTemperatures2(int* T, int TSize, int* returnSize){
    
}
