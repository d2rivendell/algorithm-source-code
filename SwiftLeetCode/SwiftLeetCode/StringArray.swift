//
//  StringArray.swift
//  SwiftLeetCode
//
//  Created by leon on 2020/9/5.
//  Copyright © 2020 rivendell. All rights reserved.
//

import Foundation
//MARK: 572. 另一个树的子树
example("572. 另一个树的子树") {
    /*
     给定两个非空二叉树 s 和 t，检验 s 中是否包含和 t 具有相同结构和节点值的子树。s 的一个子树包括 s 的一个节点和这个节点的所有子孙。s 也可以看做它自身的一棵子树。
     
     这道题看似二叉树，其实也可以序列化后变字符串， 问题就转换成了字符串包含的问题
     序列化的步骤：
     每个节点的元素用一个特殊符号分割开，每个叶子节点的空节点也要用序列化符号表示.
     因为加上空节点才能完整表达一棵树.
     这里定义'_'为NULL, '|'为元素的分割符
     例如:
      4
     / \
     1   2
     对于前序遍历表示法: "|4|1|_|_|2|_|_|"
     对于前序遍历来说第一个和最后一个都要加上'|', 注意第一个和最后一个都要加上'|'
     否则对于前序遍历
     [12] : "12|_|_|"
     [2] : "2|_|_|"
     它们并非子树的关系，
     
     对于后序 遍历来说,第一个不需要加上'|'
     [12] : "_|_|12|"
     [2] : "_|_|2"
     */
     */
    class Solution {
        init(){
            
        }
        
        func isSubtree(_ s: TreeNode?, _ t: TreeNode?) -> Bool {
            guard let t_tree = t else { return false}
            guard let s_tree = s else { return false}
            var sStr = ""
            var tStr = ""
            traverseTreeAndSerialize(s_tree, &sStr)
            traverseTreeAndSerialize(t_tree, &tStr)
            print(sStr)
            print(tStr)
            return sStr.contains(tStr)
        }
        
        //后序遍历 序列化
        func traverseTreeAndSerialize(_ node: TreeNode, _ str: inout String){
            if let left = node.left{
                traverseTreeAndSerialize(left, &str);
            }else{
                str += "_|"
            }
            if let right = node.right{
                traverseTreeAndSerialize(right, &str);
            }else{
                str += "_|"
            }
            str += "\(node.val)|"
        }
    }

  }

//MARK: 面试题 01.09. 字符串轮转
/*
 https://leetcode-cn.com/problems/string-rotation-lcci/
 字符串轮转。给定两个字符串s1和s2，请编写代码检查s2是否为s1旋转而成（比如，waterbottle是erbottlewat旋转后的字符串）。
 
 示例1:
 输入：s1 = "waterbottle", s2 = "erbottlewat"
 输出：True
 示例2:
 
 输入：s1 = "aa", s2 = "aba"
 输出：False
 */
func isFlipedString(_ s1: String, _ s2: String) -> Bool {
    if s1.count != s2.count {
        return false
    }
    if s1.count == 0 {
        return true
    }
    return (s2 + s2).contains(s1)
}
