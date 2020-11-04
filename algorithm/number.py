
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
