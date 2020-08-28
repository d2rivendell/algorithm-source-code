//
//  SkipList.swift
//  SwiftDataStructure
//
//  Created by leon on 2020/8/22.
//  Copyright © 2020 rivendell. All rights reserved.
//

import Cocoa

/*
 跳表，又叫做跳跃表、跳跃列表，在有序链的基础上增加了“跳跃”功能
 由William Pugh 于1990 年发布，设计的初衷是为了取代平衡树（比如红黑）
 Redis 中 的 SortedSet 、LevelDB 中的 MemTable 都用到了跳表
 Redis 、LevelDB 都是著名的 KeyKey-Value 数据库
对比平衡树：
 跳表的实现和维护会更加简单
 跳表的搜索、删除添加平均时间复杂度是 O(logn)
 */


//最高层数
let maxLevel: Int = 32
let rate: Double = 0.4


public protocol defaultValueAble{
    static var `default`: Self { get }
}

extension Int: defaultValueAble{
    public static var `default`: Int{
        return 0
    }
}

public class SkipList<K: Comparable & defaultValueAble,V>: CustomStringConvertible{
    public class Node<K,V>: CustomStringConvertible{
        var key: K
        var value: V?
        var nexts: [Node<K, V>?]//最后一层可能是空，所以要用可选值
        init(key: K, value: V?, level: Int) {
            
            self.key  = key
            self.value = value
            self.nexts = [Node<K, V>?].init(repeating: nil, count: level)
        }
        public var description: String{
            return "key \(key) : value: \(value ?? nil)_\(nexts.count)"
        }
    }
    /// 有效层数,和最高层的节点相等，最高层节点变化后也会跟着变化
    /// 对于 head, 当size不为0即存在节点时， [0, level)层指向的都是有效的节点
    private var level: Int = 0
    
    //空头，不存储节点信息
    private var head: Node<K,V>
    
    //节点数量
    private(set) var size: Int = 0
    
    public  init() {
       self.head = Node<K,V>(key: K.default, value: nil, level: maxLevel)
    }
    
    func randomLevel() -> Int{
        var level: Int = 1
        while (Double(arc4random() % 100)/100.0) < rate && level < maxLevel {
            level += 1
        }
        return level
    }
    
    func compare(_ key1: K, _ key2: K) ->Int{
        if key1 == key2 {
            return 0
        }else if key1 > key2 {
            return 1
        }else{
            return -1
        }
    }
    
    public var description: String{
        var res: String = ""
        res.append(contentsOf: "一共 \(self.level) 层" + "\n")
        var node: Node<K,V>? = self.head
        while let current = node, current.nexts[0] != nil{
            res.append(contentsOf: current.nexts[0]!.description + "\n")
            node = current.nexts[0]
        }
        return res
    }
}


//MARK: public 接口
extension SkipList{
    
    ///查找key值对应的value
    public func get(key: K) -> V?{
        var node: Node<K, V>? = self.head
        //从最上层开始查找
        for i in (0..<self.level).reversed(){
            /*
             1. 下一个节点不为空
             2. 如果下个节点小于key那么要在同层的下下个节点找
             */
            while node?.nexts[i] != nil && self.compare(key, node!.nexts[i]!.key) > 0{
                node = node?.nexts[i]
            }
            if (node?.nexts[i] != nil && self.compare(key, node!.nexts[i]!.key) == 0 ){
                return node?.nexts[i]?.value
            }//找到了
            //同层没有找到 到当前的下一层去查找
        }
        //都找过了， 没有找到
        return nil
    }
    
    /// 将键值对存到跳表中， 如果之前存在该key值， 把原来key对应value返回
    @discardableResult
    public func put(key: K, value: V) -> V?{
        
        var node: Node<K, V>? = self.head
        //记录前面搜索过的节点, node在pre数组d里面的下标和层级有关
        var pre: [Node<K, V>?] = [Node<K, V>?].init(repeating: nil, count: self.level)
        for i in (0..<self.level).reversed(){
            while node?.nexts[i] != nil && self.compare(key, node!.nexts[i]!.key) > 0{
                node = node?.nexts[i]
            }
            if (node?.nexts[i] != nil && self.compare(key, node!.nexts[i]!.key) == 0 ) {
                let oldValue = node!.nexts[i]!.value
                node!.nexts[i]!.value = value
                return oldValue
            }
            pre[i] = node
        }
        //没有找到
        //新增一个节点， 该节点的level是随机的， pre[0～newLevel-1]就是newNode的前驱
        let newLevel =  randomLevel()
        let newNode =  Node<K, V>(key: key, value: value, level: newLevel)
        for i in 0..<newLevel{
            if i >= self.level {//newLevel大于当前的层数
                head.nexts[i] = newNode
                //从这里开始newNode指向的就是NULL
            }else{
                newNode.nexts[i] = pre[i]?.nexts[i]
                pre[i]?.nexts[i] = newNode
            }
            
        }
        //更新当前的层数
        self.level = max(newLevel, self.level)
        //更新当前的节点数量
        self.size += 1
        return nil
    }
    
    @discardableResult
    public func remove(key: K) ->V? {
        var exist = false
        var node: Node<K, V>? = self.head
        //记录key所有的前驱, 下标和层是一一对应的
        var pre: [Node<K, V>?] = [Node<K, V>?].init(repeating: nil, count: self.level)
        for i in (0..<self.level).reversed(){
             while node?.nexts[i] != nil && self.compare(key, node!.nexts[i]!.key) > 0{
                           node = node?.nexts[i]
                       }
            pre[i] = node
            if (node?.nexts[i] != nil && self.compare(key, node!.nexts[i]!.key) == 0 ){//找到 ，但是要记录key所有的前驱， 所有循环还要继续
                exist = true
            }
        }
        //最靠近key的节点的第0层肯定是指向 目标节点
        guard exist , let target = node?.nexts[0] else { return nil}
        //设置前驱的后置
        for i in 0..<target.nexts.count{
            pre[i]?.nexts[i] = target.nexts[i]
        }
        //节点数减1
        self.size -= 1
        
        //设置有效层数
        var newLevel = self.level
        while head.nexts[newLevel - 1] == nil {
            newLevel -= 1
        }
        
        self.level = newLevel
        
        return target.value
    }
}
