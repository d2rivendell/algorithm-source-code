//
//  LeetCode1.h
//  LeetCode
//
//  Created by leon on 2020/6/19.
//  Copyright © 2020 leon. All rights reserved.
//

#ifndef LeetCode1_h
#define LeetCode1_h

#include <stdio.h>



//2. 两数相加

struct ListNode {
     int val;
     struct ListNode *next;
};

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2);


#endif /* LeetCode1_h */
