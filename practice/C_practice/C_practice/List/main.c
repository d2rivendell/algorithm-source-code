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
struct ListNode* rotateRight(struct ListNode* head, int k);
List removeNthFromEnd(List head, int n);

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
//
//    List res = reverse2(aList);
//    printList(res);
//    printList(nthToLast(res, 0));
    List res =removeNthFromEnd(aList, 2);
    printList(res);
    free(A);
    return 0;
}

//struct ListNode* rotateRight(struct ListNode* head, int k){
//
//    struct ListNode *p = head;
//    int i = 1;
//    while(p->next= NULL){
//        i++;
//        p = p->next;
//    }
//    struct ListNode *last = p;
//    if (k > i){//大于节点数
//        k /= i;
//    }
//    int rK = i - k;
//    p = head;
//    for(int j = 0; j < rK - 1; j++){
//        p = p->next;
//    }
//    struct ListNode *next = p->next;
//    p->next = NULL;
//    last->next = head;
//    return next;
//
//}




//MARK: -删除链表倒数第N个节点
//条件：给定的 n 保证是有效的。
//边界情况：n=1，而且链表节点只有一个； 删除的节点正好是表头
List removeNthFromEnd(List head, int n){
    //    ｜ pre| first|      second|
    if(n == 0){
        return NULL;
    }
    List first = head;//first记录的是要删除的位置
    List second = head;//second目的是要记住链表尾部
    List pre = NULL;//first的前一个节点
    int count = n-1;
    while(count-- > 0){
        second = second->Next;
    }
    while(second->Next != NULL){//⚠️：遍历到最后一个节点
        second = second->Next;
        pre = first;
        first = first->Next;
    }
    if(pre == NULL){//删除的位置是在表头
        return  first->Next;
    }else{//删除的位置非表头
        pre->Next = first->Next;
        return head;
    }
}


/**
 反转链表非递归
 */
//MARK: - 反转链表非递归
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

//MARK: - 反转链表递归
//https://leetcode-cn.com/problems/reverse-linked-list/solution/fan-zhuan-lian-biao-by-leetcode/
List reverse2(List node){
    if (node == NULL || node->Next ==NULL) {
        return node;
    }
    List last = reverse2(node->Next);//我始终是末尾的节点，但是最终我会变成老大
    node->Next->Next = node;//亲爱的下一个节点快点指向我
    node->Next = NULL;//下一个节点你既然指向我了，我就没必要指向你了，我要让位置给我的上一个节点。 因为我可能是head,翻转后我的下一个节点是空
    return last;
}

/**
 判断链表是否有环
 https://blog.csdn.net/u011373710/article/details/54024366#%E5%88%A4%E6%96%AD%E5%8D%95%E9%93%BE%E8%A1%A8%E4%B8%AD%E6%98%AF%E5%90%A6%E6%9C%89%E7%8E%AF%E6%89%BE%E5%88%B0%E7%8E%AF%E7%9A%84%E5%85%A5%E5%8F%A3%E8%8A%82%E7%82%B9
 */
//MARK: - 判断链表是否有环
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
//MARK: -链表相加：
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

//MARK: - 得到链表倒数第n个节点
ListNode nthToLast(ListNode head,int n ){
    if(head == NULL||n<1){
        return NULL;
    }
    ListNode l1 = head;
    ListNode l2 = head;
    for(int i = 0;i<n;i++){
        if(l2 == NULL){
            return NULL;
        }
        l2 = l2->Next;
    }
    while(l2 != NULL){
        l1 = l1->Next;
        l2 = l2->Next;
    }
    return l1;

}

