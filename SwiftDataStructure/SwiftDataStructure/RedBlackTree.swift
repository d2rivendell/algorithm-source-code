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
     
    class RBNode {
        enum Color {
            case red
            case black
        }
        var color: Color = .red // 建议默认是红色，这样能让红黑树的性质更快得到满足
        var parent: RBNode?
        var left: RBNode?
        var right: RBNode?
        
        init(_ color: Color = .red) {
            self.color = color
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
    /// 给节点染色，并返回改节点
    private func setColor(_ node: RBNode?, with color: RBNode.Color ) {
        guard let nd = node else {
            return
        }
        nd.color = color
    }
    /// 给节点染成红色
    private func setRed(_ node: RBNode?) {
        setColor(node, with: .red)
    }
    /// 给节点染成黑色
    private func setBlack(_ node: RBNode?) {
       setColor(node, with: .black)
    }
    /// 判断一个节点是什么颜色
    private func color(of node: RBNode?) -> RBNode.Color {
        return node?.color ?? .black
    }
    /// 判断一个节点是不是黑色
    private func isBlack(of node: RBNode?) -> Bool {
        return color(of: node) == .black
    }
    /// 判断一个节点是不是红色
    private func isRed(of node: RBNode?) -> Bool {
        return color(of: node) == .red
    }
    
    
    /// 在添加一个节点后，在这个方法里面判断需不需要调整，意味着添加函数只负责添加
    /// 而这里负责调整位置和颜色， 注意addedNode默认是红色，afterAdd负责调整它的最终颜色
    private func afterAdd(_ addedNode: RBNode?) {
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
        
        // uncle是红色， parent和uncle染成黑色， 祖父节点上溢(这里也是涵盖了4种情况)
        if isRed(of: uncle) {
            setBlack(uncle)
            setBlack(parent)
            ///祖父节点当成新添加的节点
            setRed(parent.parent)
            afterAdd(parent.parent)
            return
        }
        
        // uncle是黑色, 需要旋转 (这里也是涵盖了4种情况)
        // LL表示node是祖父节点的左节点的左节点 RR表示node是祖父节点的右节点的右节点，其他同理
        //LL/RR处理相似，把parent染黑，在进行右旋/左旋
        //LR/RL情况，把自己
        if parent.isLeft { // L
            if node.isLeft { //L
                //LL 1. 把parent染黑，进行右旋转
                setBlack(parent)
                rightRotation(node, parent, parent.parent)
                
            } else { // R
                //LR 3.
            }
            
        } else { // R
            if node.isLeft { // L
                //RL
                
            } else { // R
                //RR 2. 把parent染黑，进行左旋
                setBlack(parent)
                leftRotation(node, parent, parent.parent)
            }
        }
        
    }
    
}

//MARK: 旋转处理
extension RBTree {
    
    /// 右旋： 有node 、parent、grand三个节点，把grand向右旋转作为parent的子节点
    /// parent作为新的根节点，并且让原来grand的指针指向新的根节点
    ///      O                                         O (new root)
    ///     /                                          /       \
    ///    O (new root)   ====>         O          O
    ///   /                                          (node)
    ///  O (node)
    func leftRotation(_ node: RBNode?, _ parent: RBNode?, _ grand: RBNode?) {
        parent?.parent = grand?.parent
        parent?.right = grand
    }
    
    /// 右旋： 把node 、parent、grand三个作为一体向左旋， 最终parent作为
    /// 新的根节点，grand作为左节点，并且让原来grand的指针指向新的根节点
    /// O                                                  O (new root)
    ///  \                                              /       \
    ///   O (new root)   ====>         O          O
    ///    \                                                (node)
    ///     O (node)
    func rightRotation(_ node: RBNode?, _ parent: RBNode?, _ grand: RBNode?) {
        parent?.parent = grand?.parent
        parent?.left = grand
    }
}

//MARK: public
extension RBTree {
    
}
