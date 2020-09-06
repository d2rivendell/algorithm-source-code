//
//  dfs.swift
//  SwiftLeetCode
//
//  Created by leon on 2020/9/6.
//  Copyright © 2020 rivendell. All rights reserved.
//

import Foundation

//MARK: 17. 电话号码的字母组合
class PhoneSolution {
    var digits: [String] = []
    let  phoneMap = [ "2": ["a", "b", "c"],
                      "3": ["d", "e", "f"],
                      "4": ["g", "h", "i"],
                      "5": ["j", "k", "l"],
                      "6": ["m", "n", "o"],
                      "7": ["p", "q", "r", "s"],
                      "8": ["t", "u", "v"],
                      "9": ["w", "x", "y", "z"]]
    var result: [String] = []
    func letterCombinations(_ digits: String) -> [String] {
        if digits.count == 0{
            return []
        }
        self.digits = Array(digits).map{String($0)}
        dfs(0, "")
        return  result
    }
    func dfs(_ idx: Int, _ res: String){
        if idx == self.digits.count{
            result.append(res)
        }else{
            for v in phoneMap[digits[idx]]!{
                var res1 = res + v//使用新的数组来传递
                dfs(idx+1, res1)
            }
        }
    }
}
