from queue import PriorityQueue
from collections import Counter
import collections
import heapq

arr = [ i for i in [4,6,1,24,12,16,8,2,17,9]]
print(arr)
heap = heapq.heapify(arr)
heapq.heappush(arr, 1)
for i in range(len(arr)):
    print( heapq.heappop(arr))



class Solution(object):
    def topKFrequent(self, words, k):
        count = collections.Counter(words)
        heap = [(-freq, word) for word, freq in count.items()]
        heapq.heapify(heap)
        return [heapq.heappop(heap)[1] for _ in range(k)]