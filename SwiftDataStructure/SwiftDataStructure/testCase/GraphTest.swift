//
//  GraphTest.swift
//  SwiftDataStructure
//
//  Created by leon on 2020/8/15.
//  Copyright © 2020 rivendell. All rights reserved.
//

import Foundation

func testGraph() {
    example("图的构建和删除") {
        let graph = Graph<String, Int>.init()
        graph.addEdge(from: "V0", to: "V4", weight: 6)
        graph.addEdge(from: "V1", to: "V0", weight: 9)
        graph.addEdge(from: "V2", to: "V0", weight: 2)
        graph.addEdge(from: "V1", to: "V2", weight: 3)
        graph.addEdge(from: "V2", to: "V3", weight: 5)
        graph.addEdge(from: "V3", to: "V4", weight: 5)
//        print(graph.printGraph())
        print(graph.dfs(v: "V1"))
        print(graph.bfs(v: "V1"))
    }
}

func testTopologicalSort() {
    example("拓扑排序") {
        let graph = Graph<String, Int>.init()
        graph.addEdge(from: "0", to: "2")
        graph.addEdge(from: "1", to: "0")
        graph.addEdge(from: "2", to: "5")
        graph.addEdge(from: "2", to: "6")
        graph.addEdge(from: "3", to: "1")
        graph.addEdge(from: "3", to: "5")
        graph.addEdge(from: "3", to: "7")
        graph.addEdge(from: "5", to: "7")
        graph.addEdge(from: "7", to: "6")
        graph.addEdge(from: "6", to: "4")
        print(graph.topologicalSort())
    }
}



