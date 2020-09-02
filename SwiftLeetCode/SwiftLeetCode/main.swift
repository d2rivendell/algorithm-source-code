//
//  main.swift
//  SwiftLeetCode
//
//  Created by leon on 2020/9/2.
//  Copyright © 2020 rivendell. All rights reserved.
//

import Foundation

print("Hello, World!")

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
