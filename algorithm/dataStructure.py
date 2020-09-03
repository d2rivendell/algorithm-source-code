from queue import PriorityQueue
from collections import Counter
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


test = ["I", "like", "go", "to", "school", "but", "school", "do", "not", "like", "me"]

print("topKFrequent")
print(Solution().topKFrequent(test, 2))



stack = list([2,3,4,5])
print(stack.pop())
print(stack.pop())
print(stack.pop())
print(stack.pop())

print("stack len: ", len(stack))
if len(stack) == 0:
    print("空空如也")
