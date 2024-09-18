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

// MARK: 合并 K 个升序链表 https://leetcode.cn/problems/merge-k-sorted-lists/description/
struct ListNode* mergeKList2(struct ListNode* list1, struct ListNode* list2) {
    if(list1 == NULL || list2 == NULL) {
        return list1 == NULL ? list2 : list1;
    }
    struct ListNode temp;
    struct ListNode *head = &temp;
    while(list1 != NULL || list2 != NULL) {
        if(list1 != NULL && list2 != NULL) {
          if(list1->val < list2->val) {
              head->next = list1;
              list1 = list1->next;
          } else {
              head->next = list2;
              list2 = list2->next;
          }
        } else if (list1 != NULL) {
           head->next = list1;
           break;
        } else {
           head->next = list2;
           break;
        }
        head = head->next;
    }
    return temp.next;
}
struct ListNode* mergeKLists(struct ListNode** lists, int listsSize) {
    if(listsSize <= 0 || lists == NULL) return NULL;
    struct ListNode* pre = lists[0];
    for(int i = 1; i < listsSize; i++) {
        pre = mergeKList2(pre, lists[i]);
    }
    return pre;
}


//MARK: 86. 分隔链表 --双指针
/*
 给定一个链表和一个特定值 x，对链表进行分隔，使得所有小于 x 的节点都在大于或等于 x 的节点之前。
 你应当保留两个分区中每个节点的初始相对位置。
 示例:
 输入: head = 1->4->3->2->5->2, x = 3
 输出: 1->2->2->4->3->5
 */
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
    
    /*
     假设相交的话，链表A长度是m+b，链表B是n+b，公共部分是b，那么走过m+n+b步之后一定会相遇，返回结果。 如果不相交的话，没有公共部分，b=0， 那么走过m+n都指向None，返回None
     if (headA == NULL || headB == NULL) return NULL;
       struct ListNode *node1 = headA;
       struct ListNode *node2 = headB;
       while (node1 != node2) {
     // 注意这里是判断 node1 == NULL 而不是 node1-next == NULL
     // 按照上面的意思必须走够m/n步，才会在某一点重合
           node1 = node1 == NULL ? headB : node1->next;
           node2 = node2 == NULL ? headA : node2->next;
       }
       return node1;
     */
}

//MARK: 203. 移除链表元素
/*https://leetcode-cn.com/problems/remove-linked-list-elements/
 删除链表中等于给定值 val 的所有节点。
 示例:
 输入: 1->2->6->3->4->5->6, val = 6
 输出: 1->2->3->4->5
 */
struct ListNode* removeElements1(struct ListNode* head, int val){
    while(head && head->val == val){
        head = head->next;
    }
    if(head == NULL) return NULL;
    
    struct ListNode *pre = head;
    struct ListNode *cur = head->next;
    while(cur){
        while(cur && cur->val == val){
            cur = cur->next;
            pre->next = cur;
        }
        pre = cur;
        if(cur){
            cur = cur->next;
        }
    }
    return head;
}
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
// 1 2 2 1   右边边的2作为中点
struct ListNode* middleOfList(struct ListNode* head){
    if (head == NULL) {
        return NULL;
    }
//    struct ListNode* slow = head;
//    struct ListNode* fast = head->next;//偶数时， 第一个作为中点
//    while (fast->next && fast->next->next) {
//        slow = slow->next;
//        fast = fast->next->next;
//    }
//    return slow->next;
    struct ListNode* slow = head;
    struct ListNode* fast = head;//偶数时，第二个作为中点
    while(fast != NULL && fast->next != NULL){
        fast = fast->next->next;
        slow = slow->next;
    }
    return slow;
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


//MARK: 142. 环形链表II
/*https://leetcode-cn.com/problems/linked-list-cycle-ii/
 给定一个链表，返回链表开始入环的第一个节点。 如果链表无环，则返回 null。
 */
struct ListNode *isCycle(struct ListNode *head) {
    if(head == NULL){
        return NULL;
    }
    struct ListNode *slow = head;
    struct ListNode *fast = head;
    while(fast != NULL &&  fast->next != NULL){
        fast = fast->next->next;
        slow = slow->next;
        if(fast != NULL && fast== slow){
            return slow;
        }
    }
    return NULL;
}
/*
 m+n
 */
struct ListNode *detectCycle(struct ListNode *head) {
    if(head == NULL || head->next == NULL){
        return NULL;
    }
    struct ListNode *meetNode =  isCycle(head);
    if(meetNode == NULL) return NULL;
    
    //这步是关键
    while(meetNode !=  head){
        meetNode  = meetNode->next;
        head  = head->next;
    }
    return meetNode;
}
//MARK: 19. 删除链表的倒数第N个节点
/*https://leetcode-cn.com/problems/remove-nth-node-from-end-of-list/
 19. 删除链表的倒数第N个节点
 给定一个链表，删除链表的倒数第 n 个节点，并且返回链表的头结点。
 
 示例：
 给定一个链表: 1->2->3->4->5, 和 n = 2.
                     |   |
 当删除了倒数第二个节点后，链表变为 1->2->3->5.
 说明：
 
 给定的 n 保证是有效的。
 */
struct ListNode* removeNthFromEnd(struct ListNode* head, int n){
    if(head == NULL || n == 0) return head;
    struct ListNode* first = head;//first是要删除的那个
    struct ListNode* second = head;//辅助探测边界， 帮忙定位first和pre的
    int i = 0;
    for(; i < n-1; i++){
        second = second->next;
    }
    if (second->next == NULL){//删除的是第一个
        return head->next;
    }
    struct ListNode* pre = NULL;//删除的前一个
    while(second->next){
        second = second->next;
        pre = first;
        first = first->next;
    }
    pre->next = first->next;
    return head;
}
//MARK: - 旋转链表
/*https://leetcode-cn.com/problems/rotate-list/
 61. 旋转链表
 给定一个链表，旋转链表，将链表每个节点向右移动 k 个位置，其中 k 是非负数。

 示例 1:

 输入: 1->2->3->4->5->NULL, k = 2
 输出: 4->5->1->2->3->NULL
 解释:
 向右旋转 1 步: 5->1->2->3->4->NULL
 向右旋转 2 步: 4->5->1->2->3->NULL
 */
struct ListNode* rotateRight(struct ListNode* head, int k){
    if(head == NULL) return NULL;
     struct ListNode *temp = head;
     //统计个数 顺便定位到最后一个位置（接环）
     int count = 1;
     while(temp->next){
        temp = temp->next;
        count++;
     }
     //闭环
     temp->next = head;
     k = k % count;
     k = count - k;//第k的就是要返回的根节点
     //temp记录前一个节点
     for(int i = 0 ; i < k; i++){
        temp = head;
        head = head->next;
     }
     temp->next = NULL;
     return head;
}


//MARK: 148. 排序链表 -- 归并排序
/*https://leetcode-cn.com/problems/sort-list/
 在 O(n log n) 时间复杂度和常数级空间复杂度下，对链表进行排序。
 示例 1:
 输入: 4->2->1->3
 输出: 1->2->3->4
 */
struct ListNode* sortList(struct ListNode* head) {
    if(head == NULL || head->next == NULL) return head;
    struct ListNode *slow = head;
    /*   这里需要说明下， 偶数时必须用第一个作为中点，
     *  （1）struct ListNode *fast = head;//偶数时 中间第一个作为中点。会死循环❌, 只用在判断是否回文链表那里
     *  （2）struct ListNode *fast = head->next;//偶数时 中间第一个作为中点。
     *   比如当只有两个元素时[1,2]， 使用（1）得到的slow是2,  left=[1,2], right = NULL，继续分解left
     *   发现是死循环，正确的是方式（2）得出slow是1, left=[1], right=[2]
     */
    struct ListNode *fast = head->next;//偶数时，中间第一个作为中点。
    while(fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }
    struct ListNode *left = head;
    struct ListNode *right = slow->next;
    slow->next = NULL; // 🔥关键
    left = sortList(left);
    right = sortList(right);
    struct ListNode temp, *top = &temp;
    while(left && right){
        if(left->val < right->val){
            top->next = left;
            left = left->next;
        }else{
            top->next = right;
            right = right->next;
        }
        top = top->next;
    }
    top->next = (left != NULL ? left : right);
    return temp.next;
}

//MARK: 25. K 个一组翻转链表
/*https://leetcode-cn.com/problems/reverse-nodes-in-k-group/
 示例：
 给你这个链表：1->2->3->4->5
 当 k = 2 时，应当返回: 2->1->4->3->5
 当 k = 3 时，应当返回: 3->2->1->4->5
 */
struct ListNode* reverseKGroup(struct ListNode* head, int k){
    struct ListNode *newHead = NULL;
    newHead = head;
    struct ListNode* pre = NULL; // 上一个末尾
    while (head) {
        struct ListNode *left = head;
        for(int i = 0; i < k - 1; i++) {// 不够k个不需要翻转了
            head = head->next;
            if (head == NULL) {
                //记住最后一组不能翻  但是要链接起来
                if (pre) pre->next = left;
                return newHead;
            }
        }
       struct ListNode *right = head;
       struct ListNode *next = head->next;
       // 断开和下一个的链接否则会出错
       right->next = NULL;
       // 翻转
       reverseList(left);
       if (pre == NULL) {
           newHead = right;
       } else  {
           pre->next = right;
       }
       // 上一个末尾链接当前新的头部
       pre = left;
       head = next;
    }
    return newHead;
}
