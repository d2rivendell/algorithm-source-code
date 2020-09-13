//
//  StringArray.c
//  LeetCode
//
//  Created by leon on 2020/8/23.
//  Copyright © 2020 leon. All rights reserved.
//

#include <stdio.h>
#include "LeetCode.h"
#include "kmp.h"


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

//MARK:最长不重复字符的长度
//abcbdb
//abba
int lengthOfLongestSubstring(char * s){
    //通过滑动窗口解决， 由start和i之间组成一个滑动窗口
    int *all =  malloc(sizeof(int) * 128);//保存字符最近的下标
    int start = 0;//当前窗口的开始位置
    int count = 0;//统计当前不相同的个数
    int max = 0;//当前最大不重复的个数
    int begin = 0;//最后用来打印的
    memset(all, -1, sizeof(int) * 128);
    for (int i = 0; i < strlen(s); i++) {
        if (all[s[i]] >= start){//和窗口范围内重复了(包括窗口边界start)， 关键点是在【滑动窗口内】， 所以
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

int lengthOfLongestSubstring2(char * s){
    int len = (int)strlen(s);
    if(len == 0 || len == 1) return len;
    //保存窗口内的字符的下标
    int *dict = malloc(sizeof(int) * 128);
    memset(dict, 0, sizeof(int) * 128);
    for(int i = 0; i < 128; i++){
        dict[i] = -1;
    }
    int l=0;//
    int max = 1;
    dict[s[0]] = 0;
    for(int i=1; i < len; i++){
        int idx = dict[s[i]];
        //在滑动窗口范围内已经有重复的字符了，关键点是在【滑动窗口内】
        //所以idx >= l 不可少
        if(idx != -1 && idx >= l){
            l = idx+1;
        }
        dict[s[i]] = i;
        if(i-l+1 > max){
            max = i-l+1;
        }
    }
    free(dict);
    return max;
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



//MARK: 14. 最长公共前缀
/*
 
14. 最长公共前缀  https://leetcode-cn.com/problems/longest-common-prefix
 
 编写一个函数来查找字符串数组中的最长公共前缀。
 
 如果不存在公共前缀，返回空字符串 ""。
 
 示例 1:
 
 输入: ["flower","flow","flight"]
 输出: "fl"
 示例 2:
 
 输入: ["dog","racecar","car"]
 输出: ""
 解释: 输入不存在公共前缀。
 */
char * longestCommonPrefix(char ** strs, int strsSize){
    int minLen = 0x7fffffff;
    int maxLen = 0x08000000;
    if(strsSize == 0){
        return "";
    }
    for(int i = 0; i < strsSize; i++){
        int len = (int)strlen(strs[i]);
        if(len <= minLen){
            minLen = len;
        }
        if(len >= maxLen){
            maxLen = len;
        }
    }
    if(maxLen == 0 || minLen == 0){
        return "";
    }
    int i = 0;
    char *res = (char *)malloc(sizeof(char) * (minLen + 1));
    for(; i < minLen; i++){//列
        char s = strs[0][i];
        for(int j = 1; j < strsSize; j++){//行
            if(strs[j][i] != s){
                res[i] = '\0';
                return res;
            }
        }
        res[i] = s;
    }
    res[i] = '\0';
    return res;
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



//MARK:字符串反转
void reverseString(char* s, int sSize){
    for(int i = 0; i < sSize/2; i++){
        char temp = s[i];
        s[i] = s[sSize - i - 1];
        s[sSize - i - 1] = temp;
    }
}


//MARK:就地移除字符串所有的空格
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

//MARK:就地移除两边的空格， 单词之间最多只能有一个空格
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

//MARK: 就地翻转字符串某个区间的字符
//就地翻转字符串某个区间的字符,如把[a,b]之间的字符翻转
//the -->eht   blue-->eulb
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

//MARK:242. 有效的字母异位词
/*
 https://leetcode-cn.com/problems/valid-anagram/
 给定两个字符串 s 和 t ，编写一个函数来判断 t 是否是 s 的字母异位词。
 
 示例 1:
 
 输入: s = "anagram", t = "nagaram"
 输出: true
 示例 2:
 
 输入: s = "rat", t = "car"
 输出: false
 说明:
 你可以假设字符串只包含小写字母。
 
 来源：力扣（LeetCode）
 链接：https://leetcode-cn.com/problems/valid-anagram
 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */
bool isAnagram(char * s, char * t){
    int sLen = (int)strlen(s);
    int tLen = (int)strlen(t);
    if(sLen != tLen) return false;
    int *container = malloc(sizeof(int) * 128);
    memset(container, 0 , sizeof(int) * 128);
    for(int i = 0; i < sLen; i++){
        //字符会重复
        container[s[i]] = container[s[i]]  + 1;
    }
    for(int i = 0; i < tLen; i++){
        if(container[t[i]] == 0){
            free(container);
            return false;
        }else{
            container[t[i]] = container[t[i]] - 1;
        }
    }
    free(container);
    return true;
}


//MARK: 572. 另一个树的子树
/*
 https://leetcode-cn.com/problems/subtree-of-another-tree
 给定两个非空二叉树 s 和 t，检验 s 中是否包含和 t 具有相同结构和节点值的子树。s 的一个子树包括 s 的一个节点和这个节点的所有子孙。s 也可以看做它自身的一棵子树。
 
 这道题看似二叉树，其实也可以序列化后变字符串， 问题就转换成了字符串包含的问题
 序列化的步骤：
 每个节点的元素用一个特殊符号分割开，每个叶子节点的空节点也要用序列化符号表示.
 因为加上空节点才能完整表达一棵树.
 这里定义'_'为NULL, '|'为元素的分割符
 例如:
   4
  / \
 1   2
 对于前序遍历表示法: "|4|1|_|_|2|_|_|"
对于前序遍历来说第一个和最后一个都要加上'|', 注意第一个和最后一个都要加上'|'
 否则对于前序遍历
 [12] : "12|_|_|"
 [2] : "2|_|_|"
 它们并非子树的关系，

 对于后序 遍历来说,第一个不需要加上'|'
 [12] : "_|_|12|"
 [2] : "_|_|2"
 */
char  *traverseTreeAndSerialize(struct TreeNode* tree);
bool isSubtree2(struct TreeNode* s, struct TreeNode* t){
    if(t == NULL) return true;
    if(s == NULL) return false;
    
    char *s_str = traverseTreeAndSerialize(s);
    char *t_str = traverseTreeAndSerialize(t);
    printf("%s", s_str);
    //剩下的用KMP算法 进行判断
    return kmp(s_str, t_str) != -1;
}

//前序遍历
char  *traverseTreeAndSerialize(struct TreeNode* tree)
{
    struct TreeNode **stack = malloc(0);
    int stk_top = 0;
    
    int cur = 1;
    char *serialize = malloc(sizeof(char) * cur);
    serialize[cur-1] = '|';
    while (tree != NULL || stk_top != 0) {
        if (tree) {
            cur += 2;
            serialize = realloc(serialize, sizeof(char) * cur);
            serialize[cur-1] = '|';
            serialize[cur-2] = '0' + tree->val;
            
            if(tree->left == NULL){
                cur += 2;
                serialize = realloc(serialize, sizeof(char) * cur);
                serialize[cur-1] = '|';
                serialize[cur-2] = '_' ;
            }
            if(tree->right == NULL){
                cur += 2;
                serialize = realloc(serialize, sizeof(char) * cur);
                serialize[cur-1] = '|';
                serialize[cur-2] = '_' ;
            }
            
            stk_top++;
            stack = realloc(stack, sizeof(struct TreeNode*) * stk_top);
            stack[stk_top-1] = tree;
            tree = tree->left;
        }else{
            struct TreeNode *node = stack[--stk_top];
            tree = node->right;
            free(node);
        }
    }
    cur++;
    serialize = realloc(serialize, sizeof(char) * cur);
    serialize[cur-1] = '\0';
    free(stack);
    return serialize;
}




//MAKR: 面试题 01.09. 字符串轮转
/*
 https://leetcode-cn.com/problems/string-rotation-lcci/
 字符串轮转。给定两个字符串s1和s2，请编写代码检查s2是否为s1旋转而成（比如，waterbottle是erbottlewat旋转后的字符串）。
 示例1:
 输入：s1 = "waterbottle", s2 = "erbottlewat"
 输出：True
 示例2:
 输入：s1 = "aa", s2 = "aba"
 输出：False
 */

bool isFlipedString(char* s1, char* s2){
    int len1 = (int)strlen(s1);
    int len2 = (int)strlen(s2);
    if(len1 != len2) return false;
    if(len1 == 0) return true;
//法一： 复杂度高
//    char *str = malloc(sizeof(char) * (len2+1));
//    str[len2] = '\0';
//    for(int i = 0; i < len2; i++){
//        //以第i个字符 作为首字母
//        //拷贝第i个及其以后的字符
//        memcpy(str, s2 + i, sizeof(char) * (len2 - i));
//        //拷贝第i个之前的字符
//        memcpy(str + sizeof(char) * (len2 - i), s2, sizeof(char) * i);
//        printf("%s \n",str);
//        if (kmp(s1, str) != -1) {
//            return true;
//        }
//    }
    
    //法二:
    char *str = malloc(sizeof(char) * (len2 * 2 + 1));
    str[len2 * 2] = '\0';
    memcpy(str, s2, sizeof(char) * len2);
    memcpy(str + sizeof(char) * len2, s2, sizeof(char) * len2);
    if(kmp(str, s1) != -1){
        free(str);
        return true;
    }
    return false;
}
