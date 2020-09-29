//
//  TrieTest.swift
//  SwiftDataStructure
//
//  Created by leon on 2020/9/30.
//  Copyright © 2020 rivendell. All rights reserved.
//

import Foundation

func testTrie(){
    example("Trie test") {
        let trie = Trie<Int>()
        trie.add("cat", v: 0)
        trie.add("dog", v: 1)
        trie.add("doggy", v: 2)
        trie.add("catalog", v: 3)
        trie.add("cast", v: 4)
        trie.add("螺蛳粉", v: 5)
        
        assert(trie.size == 6)
        assert(trie.start(with:"do"))
        assert(trie.start(with:"c"))
        assert(trie.start(with:"ca"))
        assert(trie.start(with:"cat"))
        assert(trie.start(with:"cata"))
        assert(!trie.start(with:"hehe"))
        assert(trie.contain(with:"螺蛳粉") == 5)
        assert(trie.remove(with:"cat") == 0)
        assert(trie.remove(with:"catalog") == 3)
        assert(trie.remove(with:"cast") == 4)
        assert(trie.size == 3)
        assert(trie.start(with:"螺"))
        assert(trie.start(with:"do"))
        assert(!trie.start(with:"c"))
        
    }
}
