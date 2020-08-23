//
//  List.c
//  LeetCode
//
//  Created by leon on 2020/8/23.
//  Copyright © 2020 leon. All rights reserved.
//

#include <stdio.h>
#include "LeetCode.h"

//#include "LeetCode1.h"


//MARK: 链表相加
//struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2){
//    struct ListNode *head =  (struct ListNode *)malloc(sizeof(struct ListNode));
//    struct ListNode *cur = head;
//    int c = 0;
//    while(cur != NULL){
//        if (l1 != NULL){
//            c += l1->val;
//            l1 = l1->next;
//        }
//        if (l2 != NULL){
//            c += l2->val;
//            l2 = l2->next;
//        }
//        cur->val = c % 10;
//        c /= 10;
//        if (l1 != NULL || l2 != NULL || c){
//            cur->next = (struct ListNode *)malloc(sizeof(struct ListNode));
//        }
//        cur = cur->next;
//    }
//    return head;
//}
//
//
//
//
////61. 旋转链表。 给定一个链表，旋转链表，将链表每个节点向右移动 k 个位置，其中 k 是非负数。
////MARK: - 旋转链表
//struct ListNode* rotateRight(struct ListNode* head, int k){
//    //注意边界条件， 当为0或者是链表长度的时候，返回自身
//    if(head == NULL){
//        return NULL;
//    }
//    if (head->next == NULL){
//        return head;
//    }
//    struct ListNode *p = head;
//    int count = 1;
//    //计算链表长度，并找到最后一个节点，让链表封闭起来（这样可以处理k==0,或者k==count的情况.
//    //返回之前会断开链表）
//    while(p->next != NULL){
//        count++;
//        p = p->next;
//    }
//    struct ListNode *last = p;
//    last->next = head;
//    
//    k  %= count;
//    int step = count - k;
//    p = head;
//    for(int j = 0; j < step - 1; j++){
//        p = p->next;
//    }
//    struct ListNode *next = p->next;
//    p->next = NULL;// 断环
//    return next;
//    
//}
