from queue import PriorityQueue
from collections import *
import collections
from heapq import *

arr = [ i for i in [4,6,1,24,12,16,8,2,17,9]]
print(arr)
heapify(arr)
heappush(arr, 1)

for i in range(len(arr)):
    print(heappop(arr))


class Solution(object):
    def topKFrequent(self, words, k):
        count = collections.Counter(words)
        heap = [(-freq, word) for word, freq in count.items()]
        heapify(heap)
        return [heappop(heap)[1] for _ in range(k)]

# 剑指 Offer 31. 栈的压入、弹出序列
def validateStackSequences(pushed, popped):
        stack, i = [], 0
        for num in pushed:
            stack.append(num)
            while stack and stack[-1] == popped[i]:
                stack.pop()
                i += 1
        return not stack  # stack为空就说明是对的

test = ["I", "like", "go", "to", "school", "but", "school", "do", "not", "like", "me"]

print("topKFrequent")
print(Solution().topKFrequent(test, 2))

astr =  "anc"
print(astr[0])
stack = list([2,3,4,5])

print(stack.pop(3))
print(stack.pop())
print(stack.pop())
print(stack.pop())

print("stack len: ", len(stack))
if len(stack) == 0:
    print("空空如也")

print([2,3].remove(3))
lis = []
if lis:
    print("YES")
else:
    print("NO")

class Solution:
    def permutation(self, s: str):
        c, res = list(s), []
        def dfs(x):
            if x == len(c) - 1:
                res.append(''.join(c)) # 添加排列方案
                return
            dic = set()
            for i in range(x, len(c)):
                if c[i] in dic: continue # 重复，因此剪枝
                dic.add(c[i])
                c[i], c[x] = c[x], c[i] # 交换，将 c[i] 固定在第 x 位
                dfs(x + 1) # 开启固定第 x + 1 位字符
                c[i], c[x] = c[x], c[i] # 恢复交换
        dfs(0)
        return res


slu = Solution()
a = slu.permutation("bbb")
print(a)