//
//  main.c
//  C_practice
//
//  Created by Leon.Hwa on 17/4/12.
//  Copyright © 2017年 Leon. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include <time.h>
#include "Tool.h"
#define false   0
#define true   1



List reverse1(List node);
List reverse2(List node);
ListNode nthToLast(ListNode head,int n );
int main(int argc, const char * argv[]) {
//    List chainList = malloc(sizeof(List));
//    chainList->Element = rand() % 100;
//    chainList->Next = NULL;
//    Insert(20, chainList, Header(chainList));
//    Insert(30, chainList, chainList->Next);
//    List p = chainList;
//       DeleteList(chainList);
    
    ElementType *A = createArray(5);
    List aList = createList(A, 5);
    printList(aList);
    printList(reverse2(aList));
    
    printList(nthToLast(aList, 2));
    
    free(A);
    
    return 0;
}


void
lh_Insert(ElementType X,List L,Position P){
    if (L == NULL || P == NULL) {
        printf("List and Position can not be NULL!!!");
    }
    PtrToNode TmpCell = malloc(sizeof(struct Node));
    TmpCell->Element = X;
    TmpCell->Next = P->Next;
    
}

/**
 反转链表非递归
 */
List reverse1(List node){
    List pre = NULL;
    while (node != NULL) {
        List nextNode = node->Next;//暂存下一个
        node->Next = pre;//下一个指向当前
        pre = node;//当前赋值给上一个
        node = nextNode;//下一个变成当前
    }
    return pre;
}
/**
 反转链表递归
 */
List reverse2(List node){
    if(node->Next == NULL){
        return node;
    }
    //reverseNode是倒数第二个node的next，即 reverseNode = 倒数第二个node->Next
    //即是最后一个List
    List reverseNode = reverse2(node->Next);
    node->Next->Next = node;//把下一个List指向当前
    node->Next = NULL;//当前node的下一个置空，（为转向作准备）
    return reverseNode;//最后一个List，反转后变成Head
}

/**
 判断链表是否有环
 https://blog.csdn.net/u011373710/article/details/54024366#%E5%88%A4%E6%96%AD%E5%8D%95%E9%93%BE%E8%A1%A8%E4%B8%AD%E6%98%AF%E5%90%A6%E6%9C%89%E7%8E%AF%E6%89%BE%E5%88%B0%E7%8E%AF%E7%9A%84%E5%85%A5%E5%8F%A3%E8%8A%82%E7%82%B9
 */
int hasCycle(List head){
    if(head == NULL|| head->Next == NULL){
        return false;
    }
    List slow,fast;
    fast = head->Next;
    slow = head;
    while(fast!=slow){
        if(fast == NULL || fast->Next== NULL){
            return false;
        }
        fast = fast->Next->Next;
        slow = slow->Next;
    }
    return true;
}


/**
 链表相加：
 Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
 Output: 7 -> 0 -> 8
 Explanation: 342 + 465 = 807.

 */
struct Node* addTwoNumbers(struct Node* l1, struct Node* l2) {
    struct Node  *result = malloc(sizeof(struct Node));
    struct Node  *a = l1;
    struct Node  *b = l2;
    struct Node *curr = result;
    int carry = 0;//进位
    while (a !=NULL || b != NULL) {
        int i = (a != NULL) ? a->Element:0;
        int j = (b != NULL) ? b->Element:0;
        int s = i + j + carry;
        carry = s/10;
        struct Node  *cell = malloc(sizeof(struct Node));
        //要置空 否则在其他编译器会报错
        cell->Next = NULL;
        cell->Element = s%10;
        curr->Next = cell;
        curr = cell;
        if(a != NULL){
            a = a->Next;
        }
        if(b != NULL){
            b = b->Next;
        }
    }
    if (carry > 0) {
        struct Node  *cell = malloc(sizeof(struct Node));
        //要置空 否则在其他编译器会报错
        cell->Next = NULL;
        cell->Element = carry;
        curr->Next =cell;
        curr = cell;
    }
    return result->Next;
    
}
/**
 得到链表倒数第n个节点
 */
ListNode nthToLast(ListNode head,int n ){
    if(head == NULL||n<1){
        return NULL;
    }
    ListNode l1 = head;
    ListNode l2 = head;
    for(int i = 0;i<n-1;i++){
        if(l2 == NULL){
            return NULL;
        }
        l2 = l2->Next;
    }
    while(l2->Next!= NULL){
        l1 = l1->Next;
        l2 = l2->Next;
    }
    return l1;

}

