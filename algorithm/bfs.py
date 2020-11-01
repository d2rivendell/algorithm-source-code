import collections

def example(text):
    def decorator(func):
       def wrapper(*args, **kw):
           print("=====" + text + "=======")
           return func(*args, **kw)
       return  wrapper
    return decorator

#  找树左下角的值
def findBottomLeftValue(root):
    if root is None:
        return -1
    queue = [root]
    ans = root.val
    while len(queue) > 0:
        node = queue.pop(0)
        if node.right is not None:
            queue.append(node.right)
        if node.left is not None:
            queue.append(node.left)
        ans = node.val
    return ans



#https://leetcode-cn.com/problems/fu-za-lian-biao-de-fu-zhi-lcof/
@example("剑指 Offer 35. 复杂链表的复制")
class Node:
    def __init__(self, x, next=None, random=None):
        self.val = int(x)
        self.next = next
        self.random = random
def copyRandomList (head):
        if head is None:
            return None
        visited = {}
        queue = collections.deque()
        queue.append(head)

        def copyNode(ori):
            c = Node(ori.val, None, None)
            return c

        copy = copyNode(head)
        visited[head] = copy
        while queue:
            node = queue.pop()
            newNode = visited[node]
            if node.next and node.next not in visited:
                queue.append(node.next)
                visited[node.next] = copyNode(node.next)
                # newNode.next = visited[node.next]
            if node.random and node.random not in visited:
                queue.append(node.random)
                visited[node.random] = copyNode(node.random)
                # newNode.random = visited[node.random]
            # 设置 next和random要在这里设 ，上面两个if可能不会走
            newNode.next = visited.get(node.next, None)
            newNode.random = visited.get(node.random, None)
        return visited[head]
if __name__ == '__main__':
    arr = [1,2,3,4,5,6]
    i = 4
    print(arr[i-2:i])