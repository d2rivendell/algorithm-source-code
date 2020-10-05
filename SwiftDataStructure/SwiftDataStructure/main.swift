//
//  main.swift
//  SwiftDataStructure
//
//  Created by leon on 2020/8/15.
//  Copyright © 2020 rivendell. All rights reserved.
//

import Foundation

testGraph()
//testTopologicalSort()

//testSkipListRandom()

//testSkipListTest()

testTrie()

func strStr(_ haystack: String, _ needle: String) -> Int {
    if(needle.isEmpty) { return -1}
    var arrStr = Array(haystack)
    let count = arrStr.count
    for i in 0..<count{
        if String(arrStr[i..<count]).hasPrefix(needle){
            return i
        }
    }
    return -1
}

print(strStr("hello", "ll"))
var str = "1234"
let strArr = Array(str)
print(strArr)
//print(String.init(["3", "4"]))

//testBloomFiltert()

//testGeneticAlgorithm()
let arr = Array<Int>.init(0..<5)
print(arr)
["2", "3"].joined()
print(strArr[1..<3])
let subS = String(strArr[1..<3])


//func lastRemaining(_ n: Int, _ m: Int) -> Int {
//    if n == 0 || m == 0{
//        return -1
//    }
//    var res = Array<Int>(0..<n)
//    var idx = 0
//    while res.count > 1{
//        idx = (idx + m - 1) % res.count
//        res.remove(at: idx)
//    }
//    return res[0]
//}
//print(lastRemaining(5, 3))

