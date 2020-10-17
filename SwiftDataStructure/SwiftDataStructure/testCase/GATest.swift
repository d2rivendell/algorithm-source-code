//
//  GATest.swift
//  SwiftDataStructure
//
//  Created by leon on 2020/9/13.
//  Copyright © 2020 rivendell. All rights reserved.
//

import Foundation

class MinStack {
    class Stack {
        var min: Int = 0
        var next: Stack? = nil
        var value: Int
        init(_ value: Int) {
            self.value = value
        }
    }
    var head: Stack = Stack(0)
    init() {

    }
    
    func push(_ x: Int) {
        let s =  Stack(x)
        if let next = head.next { //有
            s.min = Swift.min(next.min, x)
            s.next =  next
            head.next = s
        } else { //第一次加
            head.next = s
            s.min = x
        }
    }
    
    func pop() {
       if let  next = head.next {
           head.next = next.next
       }
    }
    
    func top() -> Int {
       if let next = head.next {
        return  next.value
       }
       return -1
    }
    
    func min() -> Int {
        if let next = head.next {
            return  next.min
        }
       return -1
    }
}
func testGeneticAlgorithm(){
    example("遗传算法") {
        geneticAlgorithm()
    }
}

