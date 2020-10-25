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

if __name__ == '__main__':
    arr = [1,2,3,4,5,6]
    i = 4
    print(arr[i-2:i])