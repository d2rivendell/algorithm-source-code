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
 给定一个数组 nums，有一个大小为 k 的滑动窗口从数组的最左侧移动到数组的最右侧。你只可以看到在滑动窗口内的 k 个数字。滑动窗口每次只向右移动一位。
 
 返回滑动窗口中的最大值。

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

class LRUCache {
    
    class Node{
        var key: Int
        var value: Int
        var pre: Node? = nil
        var next: Node?  = nil
        init(_  key:  Int,  _ val: Int) {
            self.key = key
            self.value = val
        }
    }
    var capacity: Int = 0
    var size: Int = 0
    var dict: [Int: Node] = [:]
    var head = Node(0,0)
    var tail = Node(0,0)
    var isFull: Bool{
        return size == capacity
    }
    init(_ capacity: Int){
        self.capacity = capacity
        self.head.next = self.tail
        self.tail.pre = self.head
    }
    
    func get(_ key: Int) -> Int {
        if let node = dict[key]{
            var value = node.value
            remove(key)
            add(key, value)
            return value
        }
        return -1
    }
    
    func put(_ key: Int, _ value: Int){
        if isFull{
            drop()
        }
        add(key, value)
    }
    
    
    func remove(_ key: Int){
        guard let node = dict[key] else {
            return
        }
        let pre = node.pre
        let next = node.next
        pre?.next = next
        next?.pre = pre
        dict[key] = nil
        self.size -= 1
    }
    
    func add(_ key: Int, _ value: Int){
        let node = Node(key, value)
        let next =  self.head.next
        next?.pre = node
        
        node.next = next
        node.pre = self.head
        
        self.head.next = node
        dict[key] = node
        print(node.value)
        self.size += 1
    }
    
    func drop(){
        if self.size == 0{
            return
        }
        
        let node = tail.pre
        let pre = node?.pre
        
        tail.pre = pre
        pre?.next = tail
        dict[node!.key] = nil
        self.size -= 1
    }
    
    
    
}
//let stack = MinStack()
//stack.push(-2)
//stack.push(0)
//stack.push(-1)
//stack.getMin()


//MARK: LRUCache -- 146. LRU缓存机制
class LRUCache {
    
    class Node{
        var key: Int
        var value: Int
        var pre: Node? = nil
        var next: Node?  = nil
        init(_  key:  Int,  _ val: Int) {
            self.key = key
            self.value = val
        }
    }
    var capacity: Int = 0
    var size: Int = 0
    var dict: [Int: Node] = [:]
    var head = Node(0,0)
    var tail = Node(0,0)
    var isFull: Bool{
        return size == capacity
    }
    init(_ capacity: Int){
        self.capacity = capacity
        self.head.next = self.tail
        self.tail.pre = self.head
    }
    
    func get(_ key: Int) -> Int {
        if let node = dict[key]{
            let value = node.value
            remove(key)
            add(key, value)
            return value
        }
        return -1
    }
    
    func put(_ key: Int, _ value: Int){
        // 错在这里， 不应该直接丢弃， 而是判断里面是不是有了key，只需要更新下就行了
        //        if isFull{
        //            drop()
        //        }
        if let _ = dict[key]{
            remove(key)
            add(key, value)
        }else{
            if isFull{
                drop()
            }
            add(key, value)
        }
        
        add(key, value)
    }
    
    
    func remove(_ key: Int){
        guard let node = dict[key] else {
            return
        }
        let pre = node.pre
        let next = node.next
        
        pre?.next = next
        next?.pre = pre
        
        dict[key] = nil
        self.size -= 1
    }
    
    func add(_ key: Int, _ value: Int){
        let node = Node(key, value)
        
        let next =  self.head.next
        next?.pre = node
        
        node.next = next
        node.pre = self.head
        
        self.head.next = node
        dict[key] = node
        self.size += 1
    }
    
    func drop(){
        if self.size == 0{
            return
        }
        remove(tail.pre!.key)
    }
    
}


print("LRU")
let obj = LRUCache(2)
print(obj.get(2))
obj.put(2, 6)
print(obj.get(1))
obj.put(1, 5)
obj.put(1, 2)
print(obj.get(1))
print(obj.get(2))

//MARK: 104. 二叉树的最大深度
/*https://leetcode-cn.com/problems/maximum-depth-of-binary-tree/
 
 */
class MaxDepthSolution {
    func maxDepth(_ root: TreeNode?) -> Int {
        guard let rootNode = root else { return 0}
        var queue: [TreeNode] = [rootNode]
        var deep = 0
        while queue.isEmpty == false {
            var arr: [TreeNode] = []
            while queue.isEmpty == false {
                let node =  queue.remove(at: 0)
                if let left = node.left {
                    arr.append(left)
                }
                if let right = node.right {
                    arr.append(right)
                }
            }
            queue.append(contentsOf: arr)
            deep += 1
        }
        return deep
    }
}
