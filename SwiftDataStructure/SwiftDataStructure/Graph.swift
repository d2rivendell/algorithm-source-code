//
//  Graph.swift
//  SwiftDataStructure
//
//  Created by leon on 2020/8/15.
//  Copyright © 2020 rivendell. All rights reserved.
//
import Foundation

//V：顶点的值 E：边的权重
class Graph<V: Hashable, E>{
    
    //顶点包含一个值 和 两个边集合：出度和入度
    //两个顶点都 存储着同一条边， 只是一个放在出度，一个放在入度
    class Vertex<V: Hashable, E>: Hashable, CustomDebugStringConvertible{
        
        var value: V
        var outEdges = Set<Edge<V, E>>()//出度
        var inEdges = Set<Edge<V, E>>() //入度
        init(_ value: V) {
            self.value = value
        }
        
        public var hashValue: Int {
            return value.hashValue
        }
        
        static func == (lhs: Vertex<V, E>, rhs: Vertex<V, E>) -> Bool {
            return lhs.hashValue == rhs.hashValue
        }
        var debugDescription: String{
            return "\(value)"
        }
    }
    
    //边包含权重和两个顶点, 对于一条边， 有两个顶点都持有它， 图也持有它，所有有三个地方保存了边
    class Edge<V: Hashable, E> : Hashable, CustomDebugStringConvertible{
        
        static func == (lhs: Edge<V, E>, rhs: Edge<V, E>) -> Bool {
            return lhs.hashValue == rhs.hashValue
        }
        
        var from: Vertex<V, E>
        var to: Vertex<V, E>
        var weight: E?//可以为空
        init(from: Vertex<V, E>, to: Vertex<V, E>, weight: E? = nil) {
            self.from = from
            self.to = to
            self.weight = weight
        }
        
        //判断相等 只要看d两端以及方向是否一致，不需要考虑weight
        public var hashValue: Int {
            return from.hashValue ^ to.hashValue
        }
        public var debugDescription: String {
            return "\(from.value) ------\(String(describing: weight as? Int ?? 0))-------->\(to.value) "
        }
        
    }
    
    var vertexs: [V: Vertex<V, E>] = [:]
    var edges = Set<Edge<V,E>>()
    
    
    func printGraph()  {
        vertexs.forEach{ v in
            print("[\(v.key)]")
            print("=========================")
            print("to: ")
            v.value.outEdges.forEach{ print($0) }
            print("from: ")
            v.value.inEdges.forEach{ print($0) }
            print("=========================")
        }
        edges.forEach{ print($0) }
    }
    
    //MARK: ============添加============
    public func addVertex(v: V){
        if let _ = vertexs[v]{
            return
        }
        vertexs[v] = Vertex<V,E>(v)
    }
    
    //权重可以为空
    public func addEdge(from: V, to: V, weight: E? = nil){
        var formVertex =   vertexs[from];
        var toVertex =   vertexs[to];
        if formVertex == nil{//顶点不存在 则添加
            formVertex =  Vertex(from)
            vertexs[from] = formVertex
        }
        if toVertex == nil{//顶点不存在 则添加
            toVertex =  Vertex(to)
            vertexs[to] = toVertex
        }
        let edge = Edge(from: formVertex!, to: toVertex!, weight: weight)
        //如果不存在才会添加
        if formVertex?.outEdges.contains(edge) == false{
            formVertex?.outEdges.insert(edge)
            toVertex?.inEdges.insert(edge)
            edges.insert(edge)
        }
    }
    
    //MARK: ============删除============
    public func removeVertex(v: V){
        guard let vertex = vertexs[v] else {  return }
        //移除出度的edge
        vertex.outEdges.forEach { (e) in
            e.to.inEdges.remove(e)//和vertex连接的顶点删除
            edges.remove(e)//图删除
            vertex.outEdges.remove(e)//当前顶点删除
        }
        
        //移除入度的edge
        vertex.inEdges.forEach { (e) in
            e.from.outEdges.remove(e)//指向vertex的顶点删除
            edges.remove(e)//图删除
            vertex.inEdges.remove(e)//当前顶点删除
        }
        vertexs[v] = nil
    }
    public func removeEdge(from: V, to: V){
        guard let fromVertex = vertexs[from] else {  return }
        guard let toVertex = vertexs[to] else {  return }
        let edge = Edge(from: fromVertex, to: toVertex)
        if fromVertex.outEdges.contains(edge){
            toVertex.inEdges.remove(edge)
            edges.remove(edge)
        }
    }
    //MARK: ============搜索============
    //广度优先搜索
    func bfs(v: V){
        guard let root  = vertexs[v] else { return }
        let  queue = Queue<Vertex<V, E>>()
        var  visited = Set<Vertex<V,E>>()//图是双向的，所以记录访问过的
        var  collections: [Vertex<V,E>] = []//记录遍历到的顶点
        queue.enqueue(root)
        visited.insert(root)
        while queue.isEmpty == false {
            let vertex = queue.dequeue()!
            collections.append(vertex)
            for  e in vertex.outEdges{
                if visited.contains(e.to) { continue }//图是双向的，访问过了，忽略
                queue.enqueue(e.to)
                visited.insert(e.to)
            }
        }
        collections.forEach { debugPrint($0)}
    }
    
    //深度优先搜索
    func dfs(v: V){
        guard let root  = vertexs[v] else { return }
        var  visited = Set<Vertex<V,E>>()
        var  collections: [Vertex<V,E>] = []
        dfsHelper(vertex: root, visited: &visited, collections: &collections)
        collections.forEach { debugPrint($0)}
    }
    
    func dfsHelper(vertex: Vertex<V,E>, visited: inout Set<Vertex<V,E>>, collections: inout [Vertex<V,E>] ){
        visited.insert(vertex)
        collections.append(vertex)
        for  e in vertex.outEdges{
            if visited.contains(e.to) { continue }//图是双向的，访问过了，忽略
            dfsHelper(vertex: e.to, visited: &visited, collections: &collections)
        }
    }
}


//MAKR: 拓扑排序
//前提： 有向无环图
/*
 只有当一个活动的前驱全部都完成后，这才活动才能能进行
 步骤：
 ①把所有入度为0的顶点放入L中，然后把这些顶点从图去掉
 ②重复操作①，直到找不入度为0的顶点
 
 */
extension Graph{
    
    func topologicalSort() -> [V]{
        //保存要拿掉的入度为0的顶点, 用队列的原因是因为要保证顺序
        let queue = Queue<Vertex<V,E>>()
        var list:[V] = []
        var inMap: [Vertex<V,E> : Int] = [:] //记录每个顶点的当前入度数
        //找到初始入度为0的顶点以及顺便记录其他顶点的入度
        vertexs.forEach { (v, vertex) in
            if vertex.inEdges.count == 0{
                queue.enqueue(vertex)
            }else{
                inMap[vertex] = vertex.inEdges.count
            }
        }
        while queue.isEmpty == false {
            let vertex = queue.dequeue()!
            list.append(vertex.value)
            //变更其他节点的入度数
            for edge in vertex.outEdges{
                let count = (inMap[edge.to] ?? 1) - 1
                if count == 0{
                    queue.enqueue(edge.to)
                }else{
                    inMap[edge.to] = count
                }
            }
        }
        return list
    }
}
