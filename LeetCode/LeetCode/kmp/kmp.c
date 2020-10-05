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
    /*  s:01234567 --->7
     *  p:012 ---->3
     *  ti最大的下标是4 = 7 - 3
     */
    int tiMax = strLen - pLen;
    for(int ti = 0; ti <= tiMax; ti++) {
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
            //ti在之前的位置往前挪动一步
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
 如果有多个匹配的，要用最大的。即用【最大公共子串】
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
 而在kmp中， 当在ti和pi处失配的时候, ti不变, 模式串往前挪动(pi - next[pi])位， 并在p的pi=next[pi]处和s的ti处进行比较。
 之所以用最大公共子串的原因是, 使用最大公共子串时挪动(pi - next[pi])才是最小的，防止跳过头！！！
  (pi - next[pi])表示： 挪动位数= 匹配的位数- next表在pi的位置。
 直接地说， 当ti和pi失配的时候， ti不变，pi=next[i], ti和pi继续进行匹配
 */

int *next(char *p);
//@return: 匹配的初始位置， 没有匹配到返回-1
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
        if (pi < 0 || s[ti] == p[pi]) {
            ti++;
            pi++;
        }else{//失配
            pi = nextTable[pi];
        }
    }
    free(nextTable);
    return pi == pLen ?  ti - pi :  -1;
}


/*
 next'表示 pattern的最大公共子串的集合，在此基础上next'的值往右移动1为， 左边空出的位置填-1。
 此时新的表用next表示。
 
 该方法是基于新的模式表next进行构造的， 原理见kmp4.png
 */
int *next1(char *p){
    int pLen =  (int)strlen(p);
    int *nextTable  = malloc(sizeof(int) * pLen);
    memset(nextTable, 0, sizeof(int) * pLen);
    nextTable[0] = -1;
    int i = 0;
    int n = -1;//1. 已知next[i]=n, i=0
    while (i < pLen - 1) {
        if (n < 0 || p[i] == p[n]) {//2.当i位置和n位置相等时 (n < 0是第一个特殊条件)
            //i变成i+1了，对应的n变成了n+1。满足next[i]=n条件
            nextTable[++i] = ++n;
        }else{//2.当i位置和n位置不相等时
            //i要和k位置比较， k位置就是next[n]
            n = nextTable[n];
        }
    }
    return nextTable;
}

int *next(char *p){
    int pLen =  (int)strlen(p);
    int *nextTable  = malloc(sizeof(int) * pLen);
    memset(nextTable, 0, sizeof(int) * pLen);
    nextTable[0] = -1;
    int i = 0;
    int n = -1;//1. 已知next[i]=n, i=0
    while (i < pLen - 1) {// 用到i+1， 所以是 < pLen -1
        if (n < 0 || p[i] == p[n]) {//2.当i位置和n位置相等时 (n < 0是第一个特殊条件)
            i++;
            n++;
            if(i < pLen - 1 && p[i] == p[n]){//优化：和前一个相等
                nextTable[i] = nextTable[n]
            }else{
                nextTable[i] = n;
            }
        }else{//2.当i位置和n位置不相等时
            //i要和k位置比较， k位置就是next[n]
            n = nextTable[n];
        }
    }
    return nextTable;
}
