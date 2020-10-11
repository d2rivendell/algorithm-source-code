//
//  BRTreeTest.swift
//  SwiftDataStructure
//
//  Created by leon on 2020/10/11.
//  Copyright © 2020 rivendell. All rights reserved.
//

import Foundation

func testBRtree(){
    example("BRtree test") {
        let tree =  RBTree<Int>()
        let nums = [55, 87, 56, 74, 96, 22, 62, 20, 70, 68, 90, 50]
        for n in nums {
           tree.add(n)
        }
        print(tree.description)
    }
}
