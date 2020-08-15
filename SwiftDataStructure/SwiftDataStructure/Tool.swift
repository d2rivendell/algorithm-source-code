//
//  Tool.swift
//  SwiftDataStructure
//
//  Created by leon on 2020/8/15.
//  Copyright © 2020 rivendell. All rights reserved.
//
import Foundation

protocol QueueProtocol {
    associatedtype Element
    func enqueue(_ e: Element)
    func dequeue() -> Element?
    var isEmpty: Bool { get }
}

protocol StackProtocol {
    associatedtype Element
    func push(_ e: Element)
    func pop() -> Element?
    var isEmpty: Bool { get }
}



class Queue<E>: QueueProtocol {
    typealias Element = E
    private var _array: [E] = []
    func enqueue(_ e: E){
        _array.append(e)
    }
    func dequeue() -> E?{
        return _array.remove(at: 0)
    }
    var isEmpty: Bool{
        return _array.isEmpty
    }
}


class Stack<E>: StackProtocol {
    typealias Element = E
    private var _array: [E] = []
    func push(_ e: E){
        _array.append(e)
    }
    func pop() -> E?{
        return _array.popLast()
    }
    var isEmpty: Bool{
        return _array.isEmpty
    }
}


func example(_ name: String, clourse: ()->Void){
    print("\(name)")
    print("-------")
    clourse()
    print("-------")
}
