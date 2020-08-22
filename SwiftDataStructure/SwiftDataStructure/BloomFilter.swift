//
//  BloomFilter.swift
//  SwiftDataStructure
//
//  Created by leon on 2020/8/22.
//  Copyright © 2020 rivendell. All rights reserved.
//

import Cocoa
/**
 布隆过滤器
 查询一个元素一定不存在或者可能存在（因为不同的元素可能会有hash冲突）
  优缺点：
   - 优点：空间效率和查询时都远超过一般的算法
   - 缺点：有一定的误判率、删除困难
它实质上是一个很长的二进制向量和系列随机映射函数（ Hash 函数）
  常见应用：
    网页黑名单系统、垃圾邮件过滤、爬虫的址判重、解决缓存穿透问题
 */
final class BloomFilter<T> {
    //二进制向量的长度
    var bitSize:  Int =  0
    //二进制向量的内容
    var bits: [Int] = []
    //hash函数的个数(每个元素由几个位置一起联合记录是否存在)
    var hashSize: Int  = 0
    
    //n：数据规模
    //p：误判率
    init(n: Int, p: Double) {
        assert(n > 0 && (p > 0 && p < 1), "参数错误")
        let ln2 = log(2.0)
        bitSize = Int(-(Double(n) * log(p))/(ln2 * ln2))
        hashSize = Int(Double(bitSize) * ln2/Double(n))
        bits = [Int].init(repeating: 0, count: (bitSize + Int.bitWidth - 1)/Int.bitWidth)
    }
}

extension BloomFilter{
    
    public func contain<T>(_ value: T)->Bool{
        return false
    }
    
    public func push<T>(_ value: T){
        
    }
}
