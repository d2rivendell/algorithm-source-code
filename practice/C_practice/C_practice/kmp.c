//
//  kmp.c
//  C_practice
//
//  Created by leon on 2020/9/5.
//  Copyright © 2020 Leon. All rights reserved.
//

#include "kmp.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

//蛮力1
int force1(char *s, char *p){
    int strLen = (int)strlen(s);
    int pLen = (int)strlen(p);
    if (s == 0 || p == 0) {
        return -1;
    }
    int pi = 0;
    for(int ti = 0; ti < strLen - pLen; ti++) {
        pi = 0;
        while(pi < pLen && s[ti+pi] == p[pi]){
            pi++;
        }
        if(pi == pLen){
            return ti;
        }
    }
    return -1;

}

//蛮力2
int force2(char *s, char *p){
    int strLen = (int)strlen(s);
    int pLen = (int)strlen(p);
    if (s == 0 || p == 0) {
        return -1;
    }
    int pi = 0;
    int ti = 0;
    while (pi < pLen && ti <=  strLen - pLen + pi) {
        if (s[ti] == p[pi]) {
            pi++;
            ti++;
        }else{
            pi = 0;
            ti =  ti - pi + 1;
        }
    }
    return pi == pLen ? ti - pi : -1;
}


/*
 char *s = "DABCDABCFACBA";
 char *p = "ABCDABCF";
 printf("location: %d\n",force(s, p));
 */

/*
 1.  概念
 
 两个概念："前缀"和"后缀"。
 前缀: 指除了最后一个字符以外，一个字符串的全部头部组合；
 后缀: 指除了第一个字符以外，一个字符串的全部尾部组合。
 
 2. 匹配表
 对于”bread“
 前缀： b、br、bre、brea
 后缀: read、rea、re、r
 没有匹配的，所以匹配值为 0
 模式串匹配表生成步骤：
 模式串的长度为pLen,
 loop: 0 <= i < Plen
 s = pattern[0, i]
 找出s的前缀和后缀匹配的个数
 
 3. 使用
 str: "8812456789"
 p: "12124"
 
 0 <= ti <= strLen - 1
 0 <= pi <= pLen - 1
 蛮力匹配一般每次失配的时候都是每次往前挪动一步
 而在kmp中， 当在ti和pi处失配的时候, ti不变, 模式串往前挪动(pi - next[i])位， 并在p的pi=next[i]处和s的ti处进行。
 直接地说， 当ti和pi失配的时候， ti不变，pi=next[i], ti和pi继续进行匹配
 */

int *next(char *p);
//s: 要查找的字符串
//p: 模式串
//return: 匹配的初始位置， 没有匹配到返回-1
int kmp(char *s, char *p){
    //kmp 基于蛮力2的基础上 修改
    int strLen = (int)strlen(s);
    int pLen = (int)strlen(p);
    if (s == 0 || p == 0) {
        return -1;
    }
    int pi = 0;
    int ti = 0;
    int *nextTable = next(p);
    while (pi < pLen && ti <=  strLen - pLen + pi) {
        if (s[ti] == p[pi]) {
            ti++;
            pi++;
        }else{//失配了
            pi = pLen - nextTable[pi];
        }
    }
    return pi == pLen ?  ti - pi :  -1;
}

int *next(char *p){
    return NULL;
}
