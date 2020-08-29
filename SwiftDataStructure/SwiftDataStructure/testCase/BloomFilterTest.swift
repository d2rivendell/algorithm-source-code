//
//  BloomFilterTest.swift
//  SwiftDataStructure
//
//  Created by huayf on 2020/8/29.
//  Copyright © 2020 rivendell. All rights reserved.
//

import Foundation

func testBloomFiltert() {
    
    example("BloomFiltert") {
        let count = 100000
        var urls: [String] = []
        let bloomFilter =  BloomFilter<String>.init(n: count, p: 0.01)
        var errCount = 0
        for i in 0..<count{
            let s = "https://www.baidu.com?\(i)"
            urls.append(s)
            bloomFilter.push(s)
        }
        for i in 100000..<(100000 + 10000){
            let s = "https://www.baidu.com?\(i)"
            urls.append(s)
        }
        for i in 0..<urls.count{
            let contain =  bloomFilter.contain(urls[i])
            if (i < 100000 && contain == false) || (i >= 100000 && contain == true){
                errCount += 1
            }
        }
        print("error rate: \(Double(errCount)/Double(urls.count) * 100)%")
    }

}
