//: [Previous](@previous)

import Foundation


func example(_ name: String, clourse: ()->Void){
    print("\(name)")
    print("-------")
    clourse()
    print("-------")
}


example("图"){
    //V：顶点的值 E：边的权重
    class Graph<V: Hashable, E>{
        var vertexs: [V: Vertex<V, E>] = [:]
        var edges = Set<Edge<V,E>>()
        
        //顶点包含一个值 和 两个边集合：出度和入度
        fileprivate class Vertex<V: Hashable, E> : Hashable, Equatable{
            var value: V
            var toEdges = Set<Edge<V, E>>()//出度
            var formEdges = Set<Edge<V, E>>() //入度
            init(_ value: V) {
                self.value = value
            }
            
            
            public var hashValue: Int {
                return value.hashValue
            }
            public static func == (lhs: Graph.Vertex<V, E>, rhs: Graph.Vertex<V, E>) -> Bool{
                return lhs.hashValue == rhs.hashValue
            }
        }
        
        //边包含权重和两个顶点
        fileprivate class Edge<V: Hashable, E> : Hashable, Equatable, CustomDebugStringConvertible{
            var from: Vertex<V, E>
            var to: Vertex<V, E>
            var weight: E?
            init(from: Vertex<V, E>, to: Vertex<V, E>, weight: E?) {
               self.from = from
               self.to = to
               self.weight = weight
            }
            
            
            public var hashValue: Int {
               return from.hashValue * 31 + to.hashValue
            }
            public static func == (lhs: Edge<V, E>, rhs: Edge<V, E>) -> Bool{
                return lhs.hashValue == rhs.hashValue
            }
            public var debugDescription: String {
                from.value
              return "\(from.value) ------(\(weight))-------->\(to.value) "
            }
            
        }
        
        func printGraph()  {
            for e in edges{
                print(e)
            }
        }
        
        public func addVertex(v: V){
            if let _ = vertexs[v]{
                return
            }
            vertexs[v] = Vertex<V,E>(v)
        }
        
        public func addEdge(from: V, to: V, weight: E?){
            var formVertex =   vertexs[from];
            var toVertex =   vertexs[to];
            if formVertex == nil{
               formVertex =  Vertex(from)
               vertexs[from] = formVertex
            }
            if toVertex == nil{
                toVertex =  Vertex(to)
                vertexs[to] = toVertex
            }
            let edge = Edge(from: formVertex!, to: toVertex!, weight: weight)
            //如果不存在才会添加
            if formVertex?.toEdges.contains(edge) == false{
                formVertex?.toEdges.insert(edge)
                toVertex?.toEdges.insert(edge)
                edges.insert(edge)
            }
  
        }
    }
    let graph = Graph<String, Int>.init()
    graph.addEdge(from: "a", to: "b", weight: 3)
    graph.addEdge(from: "a", to: "c", weight: 6)
    graph.addEdge(from: "b", to: "d", weight: 9)
    graph.addEdge(from: "d", to: "c", weight: 10)
    print(graph.printGraph())
}



//: [Next](@next)
