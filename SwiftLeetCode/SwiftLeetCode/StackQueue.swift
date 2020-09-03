//
//  StackQueue.swift
//  SwiftLeetCode
//
//  Created by leon on 2020/9/4.
//  Copyright © 2020 rivendell. All rights reserved.
//

import Foundation


//MARK: 239. 滑动窗口最大值
/*
 https://leetcode-cn.com/problems/sliding-window-maximum/
 */
class Solution {
    
    //双端队列 保存值由左到大的值的下标
    class DoubleQueue<T>{
        var array: [T] = []
        var isEmpty: Bool{
            return array.isEmpty
        }
        func push(_ value: T){
            array.append(value)
        }
        func popHead()-> T?{
            if array.isEmpty == false{
                return array.remove(at: 0)
            }
            return nil
        }
        func  popTail()-> T?{
            if array.isEmpty == false{
                return array.popLast()
            }
            return nil
        }
        
        func head()->T?{
            return array.first
        }
        func tail()->T?{
            return array.last
        }
    }
    func maxSlidingWindow(_ nums: [Int], _ k: Int) -> [Int] {
        if nums.count == 0 || nums.count == 1{
            return  nums
        }
        let len = nums.count
        var li = -k + 1
        //注意queue保存的是下标！！！
        let queue =  DoubleQueue<Int>()
        var res:[Int] = []
        //由【li, i】组成滑动窗口， 当li >=0时才开始取出双端队列的值
        for (i, val) in nums.enumerated(){
            //保证val之前比队尾最后一个小
            while queue.isEmpty == false &&  nums[queue.tail()!] < val {
                queue.popTail()
            }
            queue.push(i)
            if(li >= 0){//有完整的窗口
                //队头有过期了的要移除
                while queue.head()! < li {
                    queue.popHead()
                }
                res.append(nums[queue.head()!])
            }
            li += 1
        }
        return res
    }
}

//MARK:面试题 03.02. 栈的最小值
/*
 https://leetcode-cn.com/problems/min-stack-lcci
 请设计一个栈，除了常规栈支持的pop与push函数以外，还支持min函数，该函数返回栈元素中的最小值。执行push、pop和min操作的时间复杂度必须为O(1)。
 
 示例：
 
 MinStack minStack = new MinStack();
 minStack.push(-2);
 minStack.push(0);
 minStack.push(-3);
 minStack.getMin();   --> 返回 -3.
 minStack.pop();
 minStack.top();      --> 返回 0.
 minStack.getMin();   --> 返回 -2.
 */
class MinStack {
    var values: [Int] = []
    var mins: [Int] = []
    /** initialize your data structure here. */
    init() {
        
    }
    func push(_ x: Int) {
        if mins.isEmpty{
            mins.append(x)
        }else{
            //注意⚠️: 是和min数组里面的比
            mins.append(min(x, mins.last!))
        }
        values.append(x)
    }
    
    func pop() {
        if values.isEmpty == false{
            values.popLast()
            mins.popLast()
        }
    }
    
    func top() -> Int {
        if values.isEmpty == false{
            return values.last!
        }
        return 0
    }
    
    func getMin() -> Int {
        if values.isEmpty == false{
            return mins.last!
        }
        return 0
    }
}

let stack = MinStack()
stack.push(-2)
stack.push(0)
stack.push(-1)
stack.getMin()
