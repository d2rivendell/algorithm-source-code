//
//  List.c
//  LeetCode
//
//  Created by leon on 2020/8/23.
//  Copyright © 2020 leon. All rights reserved.
//

#include <stdio.h>
#include "LeetCode.h"


//MARK: 链表相加
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

//MARK: 86. 分隔链表 --双指针
struct ListNode* partition(struct ListNode* head, int x){
    //before存储着小于x的值，after存储着大于x的值，最后再join起来
    if(head == NULL)  return NULL;
    
    struct ListNode* before = malloc(sizeof(struct ListNode));
    struct ListNode* after = malloc(sizeof(struct ListNode));
    struct ListNode* beforeHead = before;
    struct ListNode* afterHead = after;
    while (head != NULL) {
        if (head->val < x) {
            before->next = head;
            before = before->next;
        }else{
            after->next = head;
            after = after->next;
        }
        head = head->next;
    }
    after->next = NULL;//记住要收尾
    before->next = afterHead->next;
    struct ListNode* node = beforeHead->next;
    free(beforeHead);
    free(afterHead);
    return node;
}


//MARK: 160. 相交链表
struct ListNode *getIntersectionNode(struct ListNode *headA, struct ListNode *headB) {
    if (headA == NULL || headB == NULL) { return NULL; }
    int reachEndCount = 0;
    struct ListNode *headATop = headA;
    struct ListNode *headBTop = headB;
    while (reachEndCount < 3) {
        if ( headA && headB && headA == headB) {
            return headA;
        }
        headA = headA->next;
        headB = headB->next;
        if (headA == NULL) {
            headA = headBTop;
            reachEndCount++;
        }
        if (headB == NULL) {
            headB = headATop;
            reachEndCount++;
        }
    }
    return NULL;
}

//MARK: 203. 移除链表元素
//删除链表中等于给定值 val 的所有节点。
struct ListNode* removeElements(struct ListNode* head, int val){
    while(head && head->val == val){//去除开头的
        head = head->next;
    }
    if (head == NULL) {
        return NULL;
    }
    struct ListNode* left = head;
    struct ListNode* right = head->next;
    if (head->val == val) {
        return NULL;
    }
    while (left && right) {
        if (right->val == val) {
            //让right指向下一个非val的节点,
            //这样可以一次删除left 和right中间 等于val的节点
            while (right) {
                right = right->next;
                if (right && right->val != val) {
                    break;
                }
            }
            left->next = right;
            left = left->next;
            if (left) {
                right = left->next;
            }
        }else{
            left = left->next;
            right = right->next;
        }
    }
    
    return head;
    
    //方法2是直接建立一个新链表，遍历原链表，
    //把不等于val的其他链表装入新链表，返回新链表即可
}




//MARK: 234. 回文链表
/*
 输入: 1->2->2->1
 输出: true
 要求时间复杂度是O(n), 空间复杂度是O(1)。
 可以根据快慢指针找到链表中点，再把链表节点后半部分翻转， 前半部分再和后半部分比较
 链表节点是奇数时可以直接取中间， 是偶数时要取后一个节点开始作为后半边节点的开始
 比较完之后要把后半部分链表还原回去
 */

// 1 2 1     其中中点是2
// 1 2 2 1   左边的2作为中点
struct ListNode* middleOfList(struct ListNode* head){
    if (head == NULL) {
        return NULL;
    }
    struct ListNode* slow = head;
    struct ListNode* fast = head->next;
    while (fast->next && fast->next->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow->next;
}

struct ListNode*  reverseList(struct ListNode* head){
    struct ListNode* pre = NULL;
    while (head) {
         struct ListNode* next =  head->next;
         head->next = pre;
         pre = head;
         head = next;
    }
    return pre;
}
bool isListPalindrome(struct ListNode* head){
    //空和只有一个都算
    if (head == NULL || head->next == NULL)  return true;
    struct ListNode* leftNode = head;
    struct ListNode* midNode = middleOfList(head);
    struct ListNode* rightNode = reverseList(midNode);
    struct ListNode* rNode = rightNode;
    bool result = true;
    while (rightNode) {//rightNode最后一个指向的是空
        if (leftNode->val != rightNode->val) {
            //不能在这直接return还需要 恢复链表
            result =  false;
            break;
        }
        leftNode = leftNode->next;
        rightNode = rightNode->next;
    }
    //恢复
    reverseList(rNode);
    return result;
}
