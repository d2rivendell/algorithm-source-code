//
//  RedBlackTree.swift
//  SwiftDataStructure
//
//  Created by leon on 2020/10/10.
//  Copyright © 2020 rivendell. All rights reserved.
//

/* 讨论BRTree之前先看下m阶B树的性质
 B树是平衡M路树，拥有二叉搜索树的一些性质， 每个节点的所有子树高度都一致
 假设节点【元素】个数是x
 是根节点时: 1 <= x <= m -1
 非根节点时：ceil(m/2)-1 <= x <= m - 1  //ceil(a)是对a向上取整函数 也可以用┌ a ┐表示
 如果有子节点：
        - 根节点的【子节点个数】为[2,m]
        - 非根节点的【子节点个数】为[ceil(m/2),m]
    
 ⚠️注意： 上面的元素个数和字节点个数是不同的含义
 
 一. 添加:
   新添加的元素必定是添加到叶子结点， 叶子元素超过m-1,即等于m时，这种现象称为【上溢】
   上溢时： 假设上溢结点的元素中间元素位置为k，让改第k个元素与父节点合并, [0, k-1] [k+1, m-1]位置元素分裂为两个子节点
   如父节点也溢出，则重复上述操作,直至根节点
 
 二 删除:
   (1)删除的元素在非叶子节点：
       1.找到前驱或者后继元素，覆盖掉删除的元素
       2.再把前驱或者后继元素删除
       因为非叶子节点的前驱和后继都在叶子结点， 所以真正删除的 元素发生在叶子结点中
   (2)删除的元素在叶子节点：
      当元素个数小于ceil(m/2)-1时，即等于ceil(m/2)-2，这种现象称为【下溢】
      下溢时:
        - 如果下溢节点临近的兄弟，有至少 ceil(m/2)个时， 可以向其借一个元素， 把父节点的元素b合并到本节点，
        兄弟节点的元素a替换原父节点b的位置， 这个操作相当于旋转
        - 如果下溢节点临近的兄弟，只有 ceil(m/2)-1个元素时，将父节点的元素b 挪下来跟左右子节点进行，
          合并后的节点元素个数等于ceil( m/2) + ceil( m/2 ) − 2，不超过m − 1。这个操作可能会
          导致父节点下溢，依然按照上述方法解决，下溢现象可能会一直往上传播
 
 */

/* 疑问1: 为什么有二叉平衡树了 还需要红黑树呢？？*/

/*
红黑树的性质：
 1. 节点是 RED 或者 BLACK
 2. 根节点是 BLACK
 3. 叶子节点（外部节点，节点空）都是 BLACK
 4. RED节点的子节点都是 BLACK
    - RED节点的parent都是 BLACK
    - 从根节点到叶子节点的所路径上不能2个连续的RED节点
 5. 从任一节点到叶子节点的所有路径都包含相同数目BLACK节点
 */

/*  疑问2:为何这些规则下，就能保证平衡？*/



/*==================   编程部分 ====================== */

import Foundation

// 红黑树在构建的时间可以当作B数来处理，black节点和它的红子节点融合成为一个B数的节点
class RBTree<E: Comparable> {
     
    class RBNode<E: Comparable>  {
        enum Color {
            case red
            case black
        }
        var color: Color = .red // 建议默认是红色，这样能让红黑树的性质更快得到满足
        var parent: RBNode?
        var left: RBNode?
        var right: RBNode?
        var element: E
        init(_ element: E, _ parent: RBNode?) {
            self.element = element
            self.parent = parent
        }
        /// 本节点是否是父节点的左节点
        var isLeft: Bool {
            return left != nil
        }
        /// 本节点是否是父节点的右节点
        var isRight: Bool {
            return right != nil
        }
        /// 返回最近的家族成员节点
        func sibling() -> RBNode? {
            if isLeft {
                return parent?.right
            }
            if isRight {
                return parent?.left
            }
            return parent?.sibling()
        }
        
    }
    
    var root: RBNode<E>?
    public private(set) var size = 0
    
}

//MARK: 工具方法
extension RBTree {
    
    /// 给节点染色，并返回改节点
    private func setColor(_ node: RBNode<E>?, with color: RBNode<E>.Color ) {
        guard let nd = node else {
            return
        }
        nd.color = color
    }
    /// 给节点染成红色
    private func setRed(_ node: RBNode<E>?) {
        setColor(node, with: .red)
    }
    /// 给节点染成黑色
    private func setBlack(_ node: RBNode<E>?) {
       setColor(node, with: .black)
    }
    /// 判断一个节点是什么颜色
    private func color(of node: RBNode<E>?) -> RBNode<E>.Color {
        return node?.color ?? .black
    }
    /// 判断一个节点是不是黑色
    private func isBlack(of node: RBNode<E>?) -> Bool {
        return color(of: node) == .black
    }
    /// 判断一个节点是不是红色
    private func isRed(of node: RBNode<E>?) -> Bool {
        return color(of: node) == .red
    }
    
    /// 在添加一个节点后，在这个方法里面判断需不需要调整，意味着添加函数只负责添加
    /// 而这里负责调整位置和颜色， 注意addedNode默认是红色，afterAdd负责调整它的最终颜色
    private func afterAdd(_ addedNode: RBNode<E>?) {
        guard let node  = addedNode else { return }
        // 先看父节点的颜色
        guard let parent =  node.parent else {
            //没有父节点，表示添加的接待你是根节点，只需要染黑即可
            setBlack(node)
            return
        }
        
        // 父节点是黑色的话， 不需要调整 (这里涵盖了4种情况)
        if isBlack(of: parent){
            return
        }
        
        // 下面再区分uncle是黑的还是红的
        let uncle = parent.sibling()
        let grand = parent.parent
        // uncle是红色， parent和uncle染成黑色， 祖父节点上溢(这里也是涵盖了4种情况)
        if isRed(of: uncle) {
            setBlack(uncle)
            setBlack(parent)
            ///祖父节点当成新添加的节点
            setRed(grand)
            afterAdd(grand)
            return
        }
        
        // uncle是黑色, 需要旋转 (这里也是涵盖了4种情况)
        // LL表示node是祖父节点的左节点的左节点 RR表示node是祖父节点的右节点的右节点，其他同理
        //LL/RR处理相似，把parent染黑，grand染红，再进行右旋/左旋
        //LR/RL情况，把自己染黑, grand染红，再进行/右双旋/左双旋
        setRed(grand)
        if parent.isLeft { // L
            if node.isLeft { // LL
                // 1. 把parent染黑，进行右旋转
                setBlack(parent)
                singleRightRotation(grand)
            } else { // LR
                // 3. 自己染成黑色， 对grand进行右双旋（parent左旋， grand右旋）
                setBlack(node)
                doubleRightRotation(grand)
            }
        } else { // R
            if node.isLeft { // RL
                //4. 自己染成黑色， 对grand进行左双旋（parent右旋， grand左旋）
                setBlack(node)
                doubleRightRotation(grand)
            } else { // RR
                //2. 把parent染黑，进行左旋
                setBlack(parent)
                singleLeftRotation(grand)
            }
        }
        
    }
}

//MARK: 旋转处理
extension RBTree {
    /// 对grand进行右旋转，并返回新的根节点
    /// 右旋： 有node 、parent、grand三个节点，把grand向右旋转作为parent的右子节点
    /// parent作为新的根节点，并重新设置新的根节点的父节点
    ///      O                                         O (old parent)
    ///     /                                          /       \
    ///    O (parent)   ====>             O          O
    ///   /                                          (node)
    ///  O (node)
    @discardableResult
    func singleRightRotation(_ grand: RBNode<E>?) -> RBNode<E>?{
        let parent = grand?.left
        //指定新的根节点的父节点
        parent?.parent = grand?.parent
        //将新的根节点的右节点转过来用来平衡
        grand?.left = parent?.right
        //旋转原来根节点作为新的根节点的右节点
        parent?.right = grand
        
        return parent
    }
    
    /// 对grand进行左旋转，并返回新的根节点
    /// 左旋：  有node 、parent、grand三个节点，把grand向左旋转作为parent的左子节点
    /// parent作为新的根节点，并重新设置新的根节点的父节点
    /// O                                                  O (old parent)
    ///  \                                              /       \
    ///   O (parent)   ====>             O          O
    ///    \                                                 (node)
    ///     O (node)
    @discardableResult
    func singleLeftRotation(_ grand: RBNode<E>?) -> RBNode<E>? {
        let parent = grand?.left
        //指定新的根节点的父节点
        parent?.parent = grand?.parent
        //将新的根节点的左节点转过来用来平衡
        grand?.right = parent?.left
        //旋转原来根节点作为新的根节点的左节点
        parent?.left = grand
        return parent
    }
    
    /// 右双旋
    /// 先对parent进行左旋转，在对对grand进行右旋转，并返回新的根节点
    ///      O (grand)                              O (node)
    ///     /                                           /       \
    ///    O (parent)          ====>        O        O(grand)
    ///     \                                      (parent)
    ///      O (node)
    @discardableResult
    func doubleRightRotation(_ grand: RBNode<E>?) -> RBNode<E>?{
        let parent = grand?.left
        singleLeftRotation(parent)
        return singleRightRotation(grand)
    }
    
    /// 左双旋
    /// 先对parent进行右旋转，在对对grand进行左旋转，并返回新的根节点
    /// O (grand)                                    O (node)
    ///   \                                           /       \
    ///    O (parent)        ====>    O        O(parent)
    ///    /                                 (grand)
    ///   O (node)
    @discardableResult
    func doubleLeftRotation(_ grand: RBNode<E>?) -> RBNode<E>?{
        let parent = grand?.left
        singleRightRotation( parent)
        return singleLeftRotation(grand)
    }
}

//MARK: public
extension RBTree {
    
    public func addNode(_ e: E) {
        defer {
            size += 1
        }
        if root == nil {
            root = RBNode<E>(e, nil)
            return
        }
        var temp = root
        var parent: RBNode<E> = root!
        while let node = temp { //找到叶子节点
            parent = node
            if node.element > e {
                temp = node.left
            } else if node.element < e{
                temp = node.right
            } else {// 重复了 不处理
                return
            }
        }
        let newNode = RBNode<E>(e, parent)
        if parent.element > e {
            parent.left = newNode
        } else {
            parent.right = newNode
        }
        afterAdd(newNode)
    }
}
