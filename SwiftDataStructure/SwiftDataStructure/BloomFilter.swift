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
final class BloomFilter<T: Hashable> {
    //二进制向量的长度
    var bitSize:  Int =  0
    //二进制向量的内容
    var bits: [Int] = []
    //hash函数的个数(每个元素由几个位置一起联合记录是否存在)
    var hashSize: Int  = 0
    
    /// - Parameters:
    ///   - n: 数据规模
    ///   - p: 误差率
    init(n: Int, p: Double) {
        assert(n > 0 && (p > 0 && p < 1), "参数错误")
        let ln2 = log(2.0)
        bitSize = Int(-(Double(n) * log(p))/(ln2 * ln2))
        hashSize = Int(Double(bitSize) * ln2/Double(n))
        bits = [Int].init(repeating: 0, count: (bitSize + Int.bitWidth - 1)/Int.bitWidth)
    }
    
}

//MARK: private
extension BloomFilter{
    
    ///查看二进制向量index位置是否为1
    func _get(_ index: Int) -> Bool{
        let bitsIdx = index / Int.bitWidth
        let bitIdx = index % Int.bitWidth
        let bit = bits[bitsIdx]
        return (bit >> bitIdx) & 1  == 1
    }
    
    ///设置二进制向量index位置为1
    func _set(_ index: Int){
        let bitsIdx = index / Int.bitWidth
        let bitIdx = index % Int.bitWidth
        let bit = bits[bitsIdx]
        bits[bitsIdx] = (1 << bitIdx) | bit
    }
    
}

//MARK: public
extension BloomFilter{
    
    public func contain(_ value: T)->Bool{
        let hash1 = value.hashValue / 100
        var hash2: Int = 0
        if hash1 < 0 {
            hash2 = ~hash1 >> 16
        }else{
            hash2 = hash1 >> 16
        }
        for i in 0..<hashSize{
            var  combinedHash = hash1 + (i * hash2)
            if (combinedHash < 0) {
                combinedHash = ~combinedHash;
            }
            // 生成一个二进位的索引
            let  index = combinedHash % bitSize;
            // 查询index位置的二进位是否为0
            if (_get(index) == false) {return false }
        }
        return true
    }
    
    public func push(_ value: T){
        let hash1 = value.hashValue / 100
        var hash2: Int = 0
        if hash1 < 0 {
            hash2 = ~hash1 >> 16
        }else{
            hash2 = hash1 >> 16
        }
        for i in 0..<hashSize{
            var  combinedHash = hash1 + (i * hash2)
            if (combinedHash < 0) {
                combinedHash = ~combinedHash;
            }
            // 生成一个二进位的索引
            let  index = combinedHash % bitSize;
            // 查询index位置的二进位是否为0
            _set(index)
        }
    }
}
