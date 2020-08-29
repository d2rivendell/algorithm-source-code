//
//  SkipListTest.swift
//  SwiftDataStructure
//
//  Created by huayf on 2020/8/28.
//  Copyright © 2020 rivendell. All rights reserved.
//

import Foundation


func testSkipListRandom() {
    example("跳表 - random") {
        let skipList = SkipList<Int, Int>()
        for _ in 0..<100{
          let level = skipList.randomLevel()
//          print("\(level)")
          assert(level <= maxLevel, "randomLevel越界")
        }
    }
}

func testSkipListTest() {
    func delete(_ skipList: SkipList<Int, Int>, key: Int){
        print("删除 \(key)")
        assert(skipList.remove(key: key) == key)
        print(skipList)
    }
    example("跳表") {
        let skipList = SkipList<Int, Int>()
        let values = [12,3,21,19,9,17,7,25,6,26]
        for v in values{
            skipList.put(key: v, value: v)
        }
        print(skipList)
        for v in values{
            assert(skipList.get(key: v) == v)
        }
        delete(skipList, key: 17)
        delete(skipList, key: 21)
        delete(skipList, key: 6)
        delete(skipList, key: 26)
        delete(skipList, key: 9)
        delete(skipList, key: 3)
    }
}
