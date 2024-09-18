//
//  BinaryTree.swift
//  SwiftLeetCode
//
//  Created by leon on 2020/9/5.
//  Copyright © 2020 rivendell. All rights reserved.
//

import Foundation


//MARK: 上下打印二叉树  (不是前序遍历！！！！！)
example("上下打印二叉树") {
    //借助队列的方式去实现
    
    class TreeNode {
        public var val: Int
        public var left: TreeNode?
        public var right: TreeNode?
        public init(_ val: Int) {
            self.val = val
            self.left = nil
            self.right = nil
        }
    }
    class Solution {
        func levelOrder(_ root: TreeNode?) -> [Int] {
            if root == nil{
                return []
            }
            var queue: [TreeNode] = [root!]
            var res: [Int] = []
            while(!queue.isEmpty){
                let node = queue.remove(at: 0)
                if let left = node.left{
                    queue.append(left)
                }
                if let right = node.right{
                    queue.append(right)
                }
                res.append(node.val)
            }
            return res
        }
        
    }
}

example("前序遍历") {
    class Solution {
        func preorderTraversal(_ root: TreeNode?) -> [Int] {
            // 中 左 右
            if root == nil { return []}
            var stack: [TreeNode] = []
            var res: [Int] = []
            var head = root
            while head != nil || stack.isEmpty == false {
                if let h = head { // 先读数
                    stack.append(h)
                    res.append(h.val)
                    head = h.left
                } else {
                    let node = stack.popLast()!
                    head = node.right
                }
            }
            return res
        }
    }
}

example("中序遍历") {
    class Solution {
        func inorderTraversal(_ root: TreeNode?) -> [Int] {
            if root == nil { return [] }
            var stack: [TreeNode] = []
            var res: [Int] = []
            var head = root
            

            while head != nil || stack.isEmpty == false {
                if let r = head { //直到最左边
                   stack.append(r)
                   head = r.left
                } else {
                   if let last = stack.popLast() { // 到尽头之后开始读数
                        res.append(last.val)
                        head = last.right
                   }
                }
            }
            return res
        }
    }
}

//MARK: 572. 另一个树的子树
example("572. 另一个树的子树") {
    /*
     给定两个非空二叉树 s 和 t，检验 s 中是否包含和 t 具有相同结构和节点值的子树。s 的一个子树包括 s 的一个节点和这个节点的所有子孙。s 也可以看做它自身的一棵子树。
     
     示例 1:
     给定的树 s:
     
     3
     / \
     4   5
     / \
     1   2
     给定的树 t：
     
     4
     / \
     1   2
     返回 true，因为 t 与 s 的一个子树拥有相同的结构和节点值。
     
     来源：力扣（LeetCode）
     链接：https://leetcode-cn.com/problems/subtree-of-another-tree
     著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
     */
    class Solution {
        class Quque<T>{
            var _arr: [T] = []
            init(){
                
            }
            var isEmpty: Bool{
                return _arr.isEmpty
            }
            func enqueue(_ val: T){
                _arr.append(val)
            }
            
            func dequeue() -> T?{
                if(_arr.isEmpty == false){
                    return _arr.remove(at:0)
                }
                return nil
            }
        }
        func isSubtree(_ s: TreeNode?, _ t: TreeNode?) -> Bool {
            if( t == nil){return true}
            if( s == nil){return true}
            let queue = Quque<TreeNode>()
            queue.enqueue(s!)
            var top: TreeNode? = nil
            while(queue.isEmpty == false){
                let node =  queue.dequeue()!
                if let left = node.left{
                    queue.enqueue(left)
                }
                if let right = node.right{
                    queue.enqueue(right)
                }
                if node.val == t!.val{//有可能s中有多个节点和t的根节点相同，每个节点都要区比较
                    top = node
                    if(isSameTree(node,t)){
                        return true
                    }
                }
            }
            return false
        }
        
        func isSameTree(_ s: TreeNode?, _ t: TreeNode?) -> Bool{
            if(s == nil && t == nil) {return  true }
            guard let l = s, let r = t else { return false}
            return l.val == r.val && isSameTree(l.left, r.left) && isSameTree(l.right, r.right)
        }
    }
}

class Trie {
    class Node {
        var children: [Character: Node] = [:]
        var c: Character
        var isWord = false
        init(_ c: Character){
            self.c = c
        }
    }
    var root: Node = Node("-")
    init() {
        
    }
    
    /** Inserts a word into the trie. */
    func insert(_ word: String) {
        if let node = _get(word){
            node.isWord = true
        }
        var node = root
        for c in word{
            if let child = node.children[c]{
                node = child
            }else{
                let child = Node(c)
                node.children[c] = child
                node = child
            }
        }
        node.isWord = true
    }
    
    /** Returns if the word is in the trie. */
    func search(_ word: String) -> Bool {
        guard let node = _get(word), node.isWord else {
            return false
        }
        return true
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    func startsWith(_ prefix: String) -> Bool {
        guard let node = _get(prefix) else {
            return false
        }
        return true
    }
    
    private func _get(_ word: String)-> Node?{
        var node = root
        for c in word{
            guard let child = node.children[c] else{
                return nil
            }
            node = child
        }
        return node
    }
}
