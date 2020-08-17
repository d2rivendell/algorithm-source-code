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

//就地移除字符串所有的空格
void removeAllBlank(char *s){
    //如果当前是空格
    int len = (int)strlen(s);
    int cur = 0;
    int count = 0;
    for(int i = 0; i < len; i++){
        if(s[i] == ' '){//当前是空格
            count++;
        }else{//非空格
            s[cur++] = s[i];
        }
    }
    printf("空格的个数是%d\n",count);
    s[cur] = '\0';
}

//就地移除两边的空格， 单词之间最多只能有一个空格
//“ I am a student ”
void normalString(char *s){
    int len = (int)strlen(s);
    int cur = 0;
    int preIsBlank = 1;//初始化设置为1防止第一个字符就是空格
    int count = 0;
    for(int i = 0; i < len; i++){
        if(s[i] == ' '){//空格
            // 如果前面是空格就会跳过
            if(preIsBlank){
                //do nothing
                count++;
            }else{
                s[cur++] = s[i];
            }
            preIsBlank = 1;
        }else{
            s[cur++] = s[i];
            preIsBlank = 0;
        }
    }
    if(cur == 0){//说明s都是空格
        s[cur] = '\0';
        return;
    }
    //末尾可能会有空格
    if(preIsBlank) {
        cur =  cur - 1;
    }
    s[cur] = '\0';
}

void singleReverse(char *s, int a, int b){
    int len = b - a + 1;
    //1 2 3
    //1 2 3 4
    for(int i = 0; i < len/2; i++){
        char temp = s[a + i];
        s[a + i] = s[a + len - 1 - i];
        s[a + len - 1 -i]  = temp;
    }
}

int main(int argc, const char * argv[]) {
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
//    int A[] = {1, 5, 20, 20, 25, 31};
//    printf("%d\n", coins(19, &A, 6));
//
    printf("%s\n",longestPalindrome("cbbd"));
//
//字符串
//    char *s = "  the sky is blue ";
//    int len = (int)strlen(s);
//    char *ss = malloc(sizeof(char) * (len + 1));
//    memcpy(ss, s, len);
//    ss[len] = '\0';
//    printf("res:||%s||\n", reverseWords(ss));

//    placeQueen(4);
    
    
    
//N皇后
//    placeQueen(4);
    int A[9] = {-2,1,-3,4,-1,2,1,-5,4};
    printf("最大子序列： %d\n",  maxSubArrayDp(A, 9));
}
