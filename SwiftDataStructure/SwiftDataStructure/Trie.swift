//
//  Trie.swift
//  SwiftDataStructure
//
//  Created by leon on 2020/9/29.
//  Copyright © 2020 rivendell. All rights reserved.
//

import Foundation

///前缀树， 字典树
class Trie<V> {
    public class Node<V> {
        ///节点是某个单词的结尾时，即isWord==true时，保存单词对应的value
        var value: V?
        ///节点是否某个单词的结尾
        var isWord: Bool = false
        private lazy var children: [Character: Node<V>] = [:]
        //指向父节点
        var parent: Node<V>?
        ///节点
        var character: Character
        
        public init(character:  Character) {
            self.character = character
        }
        
        var hasChild: Bool {
            return children.isEmpty == false
        }
        
        func addChild(character: Character, node: Node<V>) {
            return children[character] = node
        }
        
        func findChild(character: Character) -> Node<V>? {
            return children[character]
        }
        
        func removeChild(character: Character){
            return children[character] = nil
        }
    }
    
    public private(set) var size: Int = 0
    public private(set) var root = Node<V>(character: "-")
    
    //============ private func ============
    private func _get(str: String) -> Node<V>? {
        guaranteeIsNotEmpty(str)
        var node: Node<V>? = root
        for c in str{
            if let childNode = node?.findChild(character: c){
                node = childNode
            }else{
                return nil
            }
        }
        return node
    }
    
    private func guaranteeIsNotEmpty(_ str: String) {
        assert(str.isEmpty == false, "str must not be empty!")
    }
    
     //============ public func ============
    
    ///添加单词，如果存在返回旧值
    @discardableResult
    public func add(_ str: String, v: V) -> V? {
        guaranteeIsNotEmpty(str)
        var node: Node<V> = root
        for c in str{
            var childNode = node.findChild(character: c)
            if childNode == nil {
                childNode =  Node<V>.init(character: c)
                childNode?.parent = node
                node.addChild(character: c, node: childNode!)
            }
            node = childNode!
        }
        
        if node.isWord {//之前就存在， 这里只做更新
            let old = node.value
            node.value = v
            return old
        }
        node.isWord = true
        node.value = v
        size += 1
        return nil
    }
    
    ///查找单词
    public func contain(with str: String) -> V? {
        guard  let node =  _get(str: str), node.isWord else{
            return nil
        }
        return node.value!
    }
    
    ///查找前缀
    public func start(with str: String) -> Bool {
        guard  let _ =  _get(str: str) else{
            return false
        }
        return true
    }
    
    ///添加单词，如果存在返回旧值
    @discardableResult
    public func remove(with str: String) -> V? {
        // 找到单词，不是单词不处理
        guard var node =  _get(str: str), node.isWord else{
            return nil
        }
        size -= 1
        let old = node.value!
        //先看是不是该单词下面还有没有其他单词（node是其他单词的前缀）
        if(node.hasChild){
            //剥夺其作为单词结尾的标志
            node.value = nil
            node.isWord = false
            return old
        }
        //往上删除
        while let parent = node.parent {
            parent.removeChild(character: node.character)
            //父节点如果是单词 或者其有其他节点， 就此打住
            if(parent.isWord || parent.hasChild){
                break
            }
            node = parent
        }
        return old
    }
    
}

