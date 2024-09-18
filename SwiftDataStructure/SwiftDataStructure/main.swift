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

//testTrie()

//testBRtree()

//func strStr(_ haystack: String, _ needle: String) -> Int {
//    if(needle.isEmpty) { return -1}
//    var arrStr = Array(haystack)
//    let count = arrStr.count
//    for i in 0..<count{
//        if String(arrStr[i..<count]).hasPrefix(needle){
//            return i
//        }
//    }
//    return -1
//}
//
//print(strStr("hello", "ll"))
//var str = "1234"
//let strArr = Array(str)
//print(strArr)
////print(String.init(["3", "4"]))
//
////testBloomFiltert()
//for i in 0...3{
//    print(i)
//}
////testGeneticAlgorithm()
//let arr = Array<Int>.init(0..<5)
//print(arr)
//["2", "3"].joined()
//print(strArr[1..<3])
//let subS = String(strArr[1..<3])
//


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

class Solution2 {
    static func longestCommonSubsequence(_ text1: String, _ text2: String) -> Int {
        let row = text1.count
        let col = text2.count
        var dp: [[Int]] = Array(repeating: Array(repeating: 0, count: col + 1),
                                count: row + 1)

        for i in stride(from: 1, to: row + 1, by: 1) {
            for j in stride(from: 1, to: col + 1, by: 1) {
              dp[i][j] = 0
              if text1[text1.index(text1.startIndex, offsetBy: i - 1)] == text2[text2.index(text2.startIndex, offsetBy: j - 1)] {
                 dp[i][j] = dp[i - 1][j - 1] + 1
              } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1])
              }
           }
        }

        let res = dp[row][col];
        return res
    }
}
print("\(Solution2.longestCommonSubsequence("abcde", "ace"))")

var arr = [1, 2, 3]
arr.popLast()

