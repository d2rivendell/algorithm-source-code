from heapq import *

def example(text):
    def decorator(func):
       def wrapper(*args, **kw):
           print("=====" + text + "=======")
           return func(*args, **kw)
       return  wrapper
    return decorator
digits = [(1000, "M"), (900, "CM"), (500, "D"), (400, "CD"), (100, "C"), (90, "XC"),(50, "L"), (40, "XL"), (10, "X"), (9, "IX"), (5, "V"), (4, "IV"), (1, "I")]

#https://leetcode-cn.com/problems/integer-to-roman/
@example("12. 整数转罗马数字 ")
def intToRoman(num):
        """
        字符          数值
         I             1
         V             5
         X             10
         L             50
         C             100
         D             500
         M             1000
        :param num:
        :return:
        """
        roman_digits = []
        # Loop through each symbol.
        for value, symbol in digits:
            if num == 0: break
            # count, num = num // value, num % value
            count, num = divmod(num, value) #除整求余一起算
            roman_digits.append(symbol * count)
        return "".join(roman_digits)

#https://leetcode-cn.com/problems/roman-to-integer/
@example("13. 罗马数字转整数")
def romanToInt(s):
    """
      输入: "LVIII"
      输出: 58
      解释: L = 50, V= 5, III = 3.
    :param s:
    :return:
    """
    d = {'I': 1, 'IV': 4, 'V': 5, 'IX': 9, 'X': 10, 'XL': 40, 'L': 50,
         'XC': 90, 'C': 100, 'CD': 400, 'D': 500, 'CM': 900, 'M': 1000}
    res = 0
    while len(s) > 0:
        a = d.get(s[0:2], 0)
        b = d.get(s[0:1], 0)
        res += max(a, b)
        s = s[2:] if a != 0 else s[1:]
    return res

def pick_fruit(apples, picks):
     day = len(picks)
     output = [0] * day
     for a in apples:
        i = 0
        while a > 0 and i < day:
             p = picks[i] if a >= picks[i] else a
             output[i] = output[i] + p
             i += 1
             a -= p
     return output





def heapy(nums, i, n):
    node = nums[i]
    child = 0
    while 2 * i + 1 < n:
        child = 2 * i + 1
        if child + 1 < n and nums[child+1] < nums[child]:
            child += 1
        if nums[child] < node:
            nums[i] = nums[child]
        else:
            break
        i = child
    nums[i] = node

def heapSort(heapArr):
    N = len(heapArr)
    for i in range(N // 2 - 1, -1, -1):
        heapy(heapArr, i, N)

class Element:
      def __init__(self, row, col, val, count):
          self.row = row
          self.col = col
          self.val = val
          self.count = count

      def __eq__(self, other):
          return self.val == other.val

      def __lt__(self, other):
          return self.val < other.val

      def __gt__(self, other):
          return self.val > other.val

@example("N个排序好的数组合并成为一个排序的数组")
def mergeN(arrays):
    N = len(arrays) # 数组个数
    output = []
    heapArr = []
    for i in range(N):
        # 使用Element表示一个数组
        ele = Element(0,i, arrays[i][0], len(arrays[i]))
        heapArr.append(ele)
    heapSort(heapArr)
    while True:
        ele = heapArr[0]
        output.append(ele.val)
        if ele.row + 1 < ele.count:
            ele.row += 1
            ele.val = arrays[ele.col][ele.row]
            heapy(heapArr, 0, len(heapArr))
        else: # 当前数组满了
            # 堆的规模减1
            heapArr.pop(0)
            if len(heapArr) > 0:
                heapSort(heapArr)
            else:
                break
    return output


#https://leetcode-cn.com/problems/3sum/submissions/
@example("三数之和")
def threeSum(nums):
        """
        时间复杂度O(n^2)
        """
        nums.sort()
        output = []
        n = len(nums)
        for i, v in enumerate(nums):
            if i != 0 and nums[i] == nums[i - 1]:
                continue
            remain = -nums[i]
            l, r = i + 1, n - 1
            while l < r:
                temp = nums[l] + nums[r]
                if temp == remain:
                    output.append([v, nums[l], nums[r]])
                    while l + 1 < r and nums[l + 1] == nums[l]:
                        l += 1
                    while r - 1 > l and nums[r - 1] == nums[r]:
                        r -= 1
                    l += 1
                    r -= 1
                elif temp < remain:
                    l += 1
                else:
                    r -= 1
        return output

#https://leetcode-cn.com/problems/shu-ju-liu-zhong-de-zhong-wei-shu-lcof/
@example("剑指 Offer 41. 数据流中的中位数")
class MedianFinder(object):
    """
    建立一个 小顶堆 A和 大顶堆 B ，各保存列表的一半元素，且规定：
    偶数时：len(A) = N/2, len(B) = N/2
    奇数时：len(A) = N+1/2, len(B) = N-1/2
    """
    def __init__(self):
        self.A = []  # 小堆，存放大的一半
        self.B = []  # 大堆，存放小的一半 因为heap是最小堆， 可以取反实现大堆的功能

    def addNum(self, num):
        if len(self.A) != len(self.B):  # 奇数，到B中
            # 将num和A中的数对比，把最小值取出来放到B中
            heappush(self.A, num)
            heappush(self.B, -heappop(self.A))

        else:  # 偶数，放到A中
            # 将num和B中的数对比，把最大值取出来放到A中
            heappush(self.B, -num)
            heappush(self.A, -heappop(self.B))

    def findMedian(self):
        return self.A[0] if len(self.A) != len(self.B) else (self.A[0] - self.B[0]) / 2.0


if __name__ == '__main__':
    print(pick_fruit([10,20,10], [5,7,2]))
    arryas = [[8, 12, 23, 34, 45, 120, 121, 122, 130, 136],
              [100, 102, 103, 104, 105, 106, 108, 109, 110, 111],
             [1, 2, 3, 4, 115, 118, 119, 112, 123, 156]]
    out = mergeN(arryas)
    print(len(out))
    print(out)
    # print(intToRoman(234))
    # arr = [1,2,3]
    # res = arr[3:4]
    # print(res)
    # di = {'a': 1, 'b':2}
    # for key in di:
    #     print(key)
    # for (v, k) in enumerate(di):
    #     print(k,v)
