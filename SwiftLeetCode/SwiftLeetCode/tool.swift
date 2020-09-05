//
//  tool.swift
//  SwiftLeetCode
//
//  Created by leon on 2020/9/5.
//  Copyright © 2020 rivendell. All rights reserved.
//

import Foundation

func example(_ name: String, clourse: ()->Void){
    print("\(name)")
    print("-------")
    clourse()
    print("-------")
}


public class TreeNode {
    public var val: Int
    public var left: TreeNode?
    public var right: TreeNode?
    public init() { self.val = 0; self.left = nil; self.right = nil; }
    public init(_ val: Int) { self.val = val; self.left = nil; self.right = nil; }
    public init(_ val: Int, _ left: TreeNode?, _ right: TreeNode?) {
        self.val = val
        self.left = left
        self.right = right
    }
}
