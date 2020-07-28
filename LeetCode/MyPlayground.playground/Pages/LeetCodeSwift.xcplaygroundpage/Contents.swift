import Foundation

/*
 实现队列： 使用数组 arr.remove(at: 0)
 实现栈: arr.popLast()
 
 */
func example(_ name: String, clourse: ()->Void){
    print("\(name)")
    print("-------")
    clourse()
    print("-------")
}

extension String{
    func subString(begin: Int, end: Int) -> String{
         let startIndex = self.startIndex
         let beginIndex = self.index(startIndex, offsetBy: begin)
         let endIndex = self.index(beginIndex, offsetBy: end - begin)
         return self[beginIndex...endIndex].description
    }
}

example("最小覆盖子串, 为啥该方法在swift下耗时这么长") {
    return
    /*
     给你一个字符串 S、一个字符串 T，请在字符串 S 里面找出：包含 T 所有字符的最小子串。
     输入: S = "ADOBECODEBANC", T = "ABC"
     输出: "BANC"
     */
    let S = "zcaethzkc", T = "ak"//T中有重复字符怎么办
    func minWindow(_ s: String, _ t: String) -> String {
        //need统计滑动窗口内外的字符,窗口外t中的目标字符是>=1(有重复)非目标字符是0, 在窗口t中目标字符是0，外其他字符<0
        var need: [Character: Int] = [:]
        t.forEach({ (cc) in
            let count = need[cc] ?? 0
            need[cc] = count + 1
        })//现在need里面记录的是要查找的字符
        var needCount = t.count//t的个数
        var i = 0
        var win = (0, s.count+1)
        let startIndex = s.startIndex
        for (idx, c) in s.enumerated(){
            let tCount = need[c] ?? 0
            if tCount > 0{//找到了
                needCount -= 1
            }
            need[c] = tCount - 1//
            if needCount==0{//1. [i, idx]窗口范围内找到了含有字符T
                //但是这个范围之内可能是[x1,x2, z1,z2,x3,z3] (z是要查找的字符，x是无关字符)
                //需要把窗口已到z2处作为新窗口，查找可能更小的
                print("啥？")
                while true {
                    let insideC = s[s.index(startIndex, offsetBy: i)]
                    let tCount = need[insideC] ?? 0
                    if tCount == 0{//3. [i, idx]内找第一个目标字符，把窗口在此位置前移,放出一个目标字符
                        if(idx - i) < win.1 - win.0{//窗口更小，更新窗口
                            win = (i, idx)
                        }
                        need[insideC] = tCount+1//移出窗口要+1
                        i += 1//窗口前一位
                        needCount += 1
                        print(needCount)
                        break
                    }
                    i += 1//2. 把窗口前移
                    need[insideC] = tCount + 1//非目标字符移出窗口后+1
                }
            }
        }
        if win.1 - win.0 > s.count{
             return ""
        }else{
            let begin = s.index(startIndex, offsetBy: win.0)
            let end = s.index(startIndex, offsetBy: win.1)
            return s[begin...end].description
        }
       
    }
    print(Date.init())
    print(minWindow(S, T))
    print(Date.init())
    

}




example("最长回文") {
    return
    /*
     给定一个字符串 s，找到 s 中最长的回文子串。你可以假设 s 的最大长度为 1000。
     
     示例 1：
     
     输入: "babad"
     输出: "bab"
     注意: "aba" 也是一个有效答案
     https://leetcode-cn.com/problems/longest-palindromic-substring/
     */
    func longestPalindrome(_ s: String) -> String {
        if s.count == 0 || s.count == 1{
            return s
        }
        var array: [Character] = []
        let startIndex = s.startIndex
        var w1 = 0
        var w2 = s.count + 1
        var res:[Character] = []
        var mWin = (w1, w2)
        for (idx, ch) in s.enumerated(){
            array.append(ch)
            print(array)
            if isPalindrome(ch: array){
                print(array)
                if idx - w1 < mWin.1 - mWin.0{
                    res = array
                   
                    mWin = (w1, idx)
                }
                w1 += 1//窗口往前移动一步
                array = Array(array.dropFirst())//把第一个丢掉
            }
            w2 = idx
        }
        print(res)
        if res.count < s.count{
            return res.reduce("", { $0 + String($1)})
        }else{
            return ""
        }
    }
    
    func isPalindrome(ch: [Character]) -> Bool{
        let count = ch.count
        if count == 0 || count == 1{ //入口已经做判断了
            return false
        }
        var begin = 0
        var end = count
        while begin < end {
            if ch[begin] != ch[end-1]{
                return false
            }
            begin += 1
            end -= 1
        }
        return true
    }
    print(longestPalindrome("cbbd"))
}


example("94. 二叉树的中序遍历") {
    return
    class TreeNode{
        var val = 0;
        var left: TreeNode?
        var right: TreeNode?
        init(_ val: Int) {
            self.val = val
        }
    }
    
    let root1 = TreeNode.init(1);
    let root2 = TreeNode.init(2);
    let root3 = TreeNode.init(3);
    
    root1.right = root2
    root2.left = root3
    
    //左-中-右
    class Solution {
        func inorderTraversal(_ root: TreeNode?) -> [Int] {
            var rootNode = root
            var array: [Int] = []
            var stackArray: [TreeNode] = []
            while(rootNode != nil || stackArray.isEmpty == false){
                if let rNode =  rootNode {//遍历到最左边
                    stackArray.append(rNode)
                    rootNode = rNode.left
                }else{//出栈 加入结果
                    if let node = stackArray.popLast(){
                        rootNode = node.right//有右节点的话转向
                        array.append(node.val)
                    }
                }
            }
            return array;
        }
    }
    
    //前序遍历
    class Solution2 {
        func preorderTraversal(_ root: TreeNode?) -> [Int] {
            var cur = root
            var res:[Int] = []
            var stack: [TreeNode] = []
            while(cur != nil ||  stack.isEmpty == false){
                if let  node = cur {
                    res.append(node.val)
                    stack.append(node)
                    cur = node.left
                }else{
                    if let node = stack.popLast(){
                        cur = node.right
                    }
                }
            }
            return res
        }
    }
    print(Solution().inorderTraversal(root1))
}



example("LRU") {
    
    //这种方式链表和链尾都是空的相当于围墙， 删除和增加都不需要特别去指定， 顺序是由新到旧
    class LRUCache {
        //双向链表 为了更快删除
        class Node {
            var val: Int = 0
            var key: Int = 0//根据key可以找到字典的位置
            var next: Node? = nil
            var pre:  Node? = nil
            init(key:Int, val: Int) {
                self.key = key
                self.val = val
            }
        }
        var capacity: Int  = 0
        var head: Node//链表头部
        var tail: Node//链表尾部
        var size = 0
        var dict:[Int: Node] = [:]
        init(_ capacity: Int) {
            self.capacity = capacity;
            self.head = Node(key: 0, val: 0)
            self.tail = Node(key: 0, val: 0)
            self.head.next = self.tail
            self.tail.pre = self.head
        }
        
        func get(_ key: Int) -> Int {
            if let hot = dict[key]{//存在, 更新到末尾的位置
                removeNode(node: hot)
                addNode(node: hot)
                return hot.val
            }else{
                return -1
            }
        }
        
        func put(_ key: Int, _ value: Int) {
            if let hot = dict[key] {//存在, 在中间抽离， 并更新到末尾的位置
                hot.val = value
                removeNode(node: hot)
                addNode(node: hot)
            }else{//不存在
                if size == capacity{//满了 要先删除迟钝节点
                    debugPrint(" 满了 delete")
                    if let overTime =  pop(){
                        removeNode(node: overTime)
                    }
                }
                //尾部追加新节点
                let node = Node(key: key, val: value)
                addNode(node: node)
            }
        }
        
        func removeNode(node: Node) {
            node.pre?.next = node.next
            node.next?.pre = node.pre
            self.dict[node.key] = nil
            self.size -= 1
        }
        
        func addNode(node: Node) {
            let top = head.next
            node.next = top
            top?.pre = node
            node.pre = head
            head.next = node
            self.dict[node.key] = node
            self.size += 1
        }
        
        func pop() -> Node? {
            if size > 0 {
                return tail.pre
            }
            return nil
        }
    }
   
    
    let cache = LRUCache.init(2)
    cache.put(1, 1);
    cache.put(2, 2);
    print("get:",cache.get(1));       // 返回  1
    cache.put(3, 3);    // 该操作会使得关键字 2 作废
    print("get:",cache.get(2));       // 返回 -1 (未找到)
    cache.put(4, 4);    // 该操作会使得关键字 1 作废
    print("get:",cache.get(1));       // 返回 -1 (未找到)
    print("get:",cache.get(3));       // 返回  3
    print("get:",cache.get(4));       // 返回  4
}


/*
 
 
 //采用和和NSCache 不一样的策略, 这里head指向的是最新的，越往后越旧
 class LRUCache {
 //双向链表 为了更快删除
 class Node {
 var val: Int = 0
 var key: Int = 0//根据key可以找到字典的位置
 var next: Node? = nil
 var pre:  Node? = nil
 init(key:Int, val: Int) {
 self.key = key
 self.val = val
 }
 }
 var capacity: Int  = 0
 var head: Node//链表头部
 var tail: Node//链表尾部
 var size = 0
 var dict:[Int: Node] = [:]
 init(_ capacity: Int) {
 self.capacity = capacity;
 self.head = Node(key: 0, val: 0)
 self.tail = Node(key: 0, val: 0)
 self.head.next = self.tail
 self.tail.pre = self.head
 }
 
 func get(_ key: Int) -> Int {
 if let hot = dict[key]{//存在, 更新到末尾的位置
 removeNode(node: hot)
 addNode(node: hot)
 return hot.val
 }else{
 return -1
 }
 }
 
 func put(_ key: Int, _ value: Int) {
 if let hot = dict[key] {//存在, 在中间抽离， 并更新到末尾的位置
 hot.val = value
 removeNode(node: hot)
 addNode(node: hot)
 }else{//不存在
 if size == capacity{//满了 要先删除迟钝节点
 debugPrint(" 满了 delete")
 if let overTime =  pop(){
 removeNode(node: overTime)
 }
 }
 //尾部追加新节点
 let node = Node(key: key, val: value)
 addNode(node: node)
 }
 }
 
 func removeNode(node: Node) {
 node.pre?.next = node.next
 node.next?.pre = node.pre
 self.dict[node.key] = nil
 self.size -= 1
 }
 
 func addNode(node: Node) {
 let top = head.next
 node.next = top
 top?.pre = node
 node.pre = head
 head.next = node
 self.dict[node.key] = node
 self.size += 1
 }
 
 func pop() -> Node? {
 if size > 0 {
 return tail.pre
 }
 return nil
 }
 }
 
 class ViewController: UIViewController {
 
 override func viewDidLoad() {
 super.viewDidLoad()
 
 let cache = LRUCache.init(2)
 cache.put(1, 1);
 cache.put(2, 2);
 print("get:",cache.get(1));       // 返回  1
 cache.put(3, 3);    // 该操作会使得关键字 2 作废
 print("get:",cache.get(2));       // 返回 -1 (未找到)
 cache.put(4, 4);    // 该操作会使得关键字 1 作废
 print("get:",cache.get(1));       // 返回 -1 (未找到)
 print("get:",cache.get(3));       // 返回  3
 print("get:",cache.get(4));       // 返回  4
 }
 
 
 }
 
 

 */




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
            var stack: [TreeNode] = [root!]
            var res: [Int] = []
            while(!stack.isEmpty){
                let node = stack.remove(at: 0)
//                stack.popLast()
                if let left = node.left{
                    stack.append(left)
                }
                if let right = node.right{
                    stack.append(right)
                }
                res.append(node.val)
            }
            return res
        }
        
    }
}


//MARK: 剑指 Offer 09. 用两个栈实现队列
example("剑指 Offer 09. 用两个栈实现队列") {
    /*
     ⚠️ 不要用自定义size字段记录数组的下标，容易出错
        直接使用swift的数组接口 isEmpty和count
   */
    class CQueue {
        class Stack{
            var capacity = 10000
            var array: [Int] = []
            func push(_ value: Int){
                if(array.count == capacity){
                    return
                }
                array.append(value)
            }
            func pop() -> Int{
                return array.popLast() ?? -1
            }
            var isEmpty: Bool{
                return array.isEmpty
            }
        }
        var leftStack =  Stack()
        var rightStack =  Stack()//记录头， 为空时从left中拿过来
        
        init() {
            
        }
        
        func appendTail(_ value: Int) {
            //不用拿右边的数组过来
            leftStack.push(value)
        }
        
        func deleteHead() -> Int {
            //把左边的栈倒入右边， 清空左边栈
            if(rightStack.isEmpty){
                while(leftStack.isEmpty == false){
                    rightStack.push(leftStack.pop())
                }
            }
            return rightStack.pop()
        }
    }

}

var set = Set<Int>()
let res1, _ = set.insert(1)
let res2, _ = set.insert(1)


