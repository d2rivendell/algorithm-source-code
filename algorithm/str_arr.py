import collections
import functools

def example(text):
    def decorator(func):
       def wrapper(*args, **kw):
           print("=====" + text + "=======")
           return func(*args, **kw)
       return  wrapper
    return decorator


@example("字符串翻转")
def reverseStr():
    L = ['Michael', 'Sarah', 'Tracy', 'Bob', 'Jack']
    s = "I am a student."
    arr = s.split(" ")
    if arr[-1][-1] == '.':#最后一个元素的符号
        arr[0] = arr[0] + '.'#放在第一个的前面
        arr[-1] = arr[-1][0:len(arr[-1]) - 1] #取出最后一个单词的最后一个标点符号
    print(" ".join(arr[::-1]))


@example("统计超过一半的元素")
def overhalf(gifts, n):
    if len(gifts) == 0:
        return 0
    if len(gifts) == 1:
        return gifts[1]

    dic = collections.defaultdict(int)
    mid = n / 2
    for v in gifts:
        if dic[v] is not None:
            l = dic[v]
            dic[v] = l + 1
            if l + 1 > mid:
                return v
        else:
            dic[v] = 1
    return 0

@example("15. 三数之和 https://leetcode-cn.com/problems/3sum/")
def threeSum(nums):
        nLen = len(nums)
        if nLen < 3:
            return []
        # 排序好 方便去重 这里是关键
        nums.sort()
        output = []
        for i in range(nLen):
            # 去重， 保证当前值和上个不同
            if i > 0 and nums[i - 1] == nums[i]:
                continue
            l = i + 1 #第二个
            r = nLen - 1#第三个
            remain = -nums[i]
            while l < r:  # 相等时要跳出循环，因为l和r保证是不同的数（不然怎么三数相加？）
                sum = nums[l] + nums[r]
                if sum == remain:
                    output.append([nums[i], nums[l], nums[r]])
                    # 去掉和l或者r相邻重复的值
                    while l + 1 < r and nums[l] == nums[l + 1]:
                        l += 1
                    while r - 1 > l and nums[r] == nums[r - 1]:
                        r -= 1
                    # 注意这里，要移动
                    l += 1
                    r -= 1
                elif sum < remain:
                    l += 1
                else:
                    r -= 1
        return output

@example("6. Z 字形变换 https://leetcode-cn.com/problems/zigzag-conversion/")
def convertZ(self, s: str, numRows: int) -> str:
    """
    将一个给定字符串根据给定的行数，以从上往下、从左到右进行 Z 字形排列。

    题解：
    """
    if s is None:
        return None
    # 行数
    rows = min(len(s), numRows)
    if rows == 1:
        return s
    #按行来划分
    res = ["" for i in range(rows)]
    down = False
    row = 0
    strList = list(s)
    for i in range(len(s)):
        res[row] = res[row] + strList[i]

        if row == 0:
            down = True
        elif row == rows - 1:
            down = False

        if down:
            row += 1
        else:
            row -= 1
    return ''.join(res)


def multiply(num1, num2):
    if num1 == '0' or num2 == '0':
        return '0'
    def add(s1, s2):
         res = ""
         n1 = len(s1)
         n2 = len(s2)
         carry = 0
         while n1 > 0 or n2 > 0 or carry > 0:
             sum = 0
             if n1 > 0:
                 sum += int(s1[n1 - 1])
                 n1 -= 1
             if n2 > 0:
                 sum += int(s2[n2 - 1])
                 n2 -= 1
             sum += carry
             res += str(sum % 10)
             carry = sum // 10
         return res[::-1]
    def singleMul(s, c):
        res = ""
        n = len(s)
        carry = 0
        base = int(c)
        while n > 0 or carry > 0:
            sum = carry
            if n > 0:
              sum += int(s[n-1]) * base
            res += str(sum % 10)
            carry = sum // 10
            n -= 1

        return res[::-1]

    num2Len = len(num2)
    n = num2Len
    res = '0'
    while n > 0:
        temp = singleMul(num1, num2[n - 1])
        for i in range(num2Len - n):
            temp += '0'
        res = add(res, temp)
        n -= 1
    return res


@example("罗马数字转整数") #https://leetcode-cn.com/problems/roman-to-integer/
def romanToInt(s):
        d = {'I': 1, 'IV': 4, 'V': 5, 'IX': 9, 'X': 10, 'XL': 40, 'L': 50,
             'XC': 90, 'C': 100, 'CD': 400, 'D': 500, 'CM': 900, 'M': 1000}
        res = 0
        while len(s) > 0:
            a = d.get(s[0:2], 0)
            b = d.get(s[0:1], 0)
            res += max(a, b)
            s = s[2:] if a != 0 else s[1:]
        return res

#https://leetcode-cn.com/problems/integer-to-roman/
@example("整数转罗马数字")
def intToRoman(num):
    roman_digits = []
    digits = [(1000, "M"), (900, "CM"), (500, "D"), (400, "CD"), (100, "C"), (90, "XC"),
              (50, "L"), (40, "XL"), (10, "X"), (9, "IX"), (5, "V"), (4, "IV"), (1, "I")]
    for (number, symbol) in digits:
        a = num // number
        num = num % number
        if a == 0:
            continue
        roman_digits.append(symbol * a)
    return ''.join(roman_digits)

#https://leetcode-cn.com/problems/compare-version-numbers/
@example("165. 比较版本号")
def compareVersion(version1, version2):
    v1 = version1.split('.')
    v2 = version2.split('.')
    l = max(len(v1), len(v2))

    # 补0这样 后面少很多判断
    if len(v1) < l:
        v1 += ['0'] * (l - len(v1))
    elif len(v2) < l:
        v2 += ['0'] * (l - len(v2))

    cur = 0
    while i < l:
        v_1, v_2 = int(v1[cur]), int(v2[cur])
        if v_1 < v_2:
            return -1
        elif v_1 > v_2:
            return 1
        cur += 1

    return 0


#https://leetcode-cn.com/problems/ba-shu-zu-pai-cheng-zui-xiao-de-shu-lcof/
@example("剑指 Offer 45. 把数组排成最小的数")
def minNumber(nums):
    """
       输入: [3,30,34,5,9]
       输出: "3033459"

       思路： 若 x + y > y + x, 则 x > y
             若 x + y < y + x, 则 x < y
        如： "330"  > "303"
            "30" < "3"
    :param nums:
    :return:
    """
    strs = list(map(str, nums))
    def compareStr(s1, s2):
        a, b = s1 + s2, s2 + s1
        return 1 if a > b else -1
    strs = sorted(strs, key=functools.cmp_to_key(compareStr))
    return "".join(strs)


#输入：s = "3[a]2[bc]"
#输出："aaabcbc"
#输入：s = "3[a2[c]]"
#输出："accaccacc"
@example("解压字符串")
def decodeString(s: str):
        stack = []
        for c in s:
            if c == ']':
               temp = []
               while len(stack) > 0 and stack[-1] != '[':
                 temp += stack.pop()
               stack.pop() # pop '['
               num = []
               while len(stack) > 0 and stack[-1].isdigit():
                  num += stack.pop()
               n = ''.join(num[::-1]) # 数字要逆序
               # 可能会有嵌套的场景，比如：3[a2[c]] ---> 3[acc]，需要丢回栈内，
               # 解析下一个`]`后变成 accaccacc
               stack += int(n) * temp[::-1]
            else:
                stack.append(c)
        return ''.join(stack)

#https://leetcode-cn.com/problems/minimum-window-substring/
@example("76. 最小覆盖子串")
def minWindow(s, t):
        # need用来记录当前窗口内的字符， 在-1， 不在+1
        need = collections.defaultdict(int)
        for c in t:
            need[c] += 1
        res = (0, len(s) + 1)
        # needCount == 0 时 说明窗口内满足
        needCount = len(t)
        left = 0
        for j, c in enumerate(s):
            if need[c] > 0:
                needCount -= 1
            need[c] -= 1
            if needCount == 0:  # 窗口内包含所求的字符
                while True:  # 排除掉左边的元素
                    leftC = s[left]
                    if need[leftC] == 0:  # 找到了最左边的
                        break
                    else:
                        left += 1  # 左窗口往右移
                        need[leftC] += 1  # 移出窗口要+1
                # 走到这里，窗口不能再缩小了 需要记录窗口大小
                if j - left < res[1] - res[0]:
                    res = (left, j)

                need[s[left]] += 1  # 左窗口往右移,  继续查找
                left += 1
                needCount += 1
        return "" if res[1] - res[0] > len(s) else s[res[0]: res[1] + 1]


def customCmp(a, b):
    return 1 if a > b else -1
if __name__ == '__main__':
    # print(multiply("123", "456"))
    # arr = [1,2,3,4,5,6,7,8,9,10]
    #
    # print(arr[:-4])
    # print(decodeStr("ef3[a]2[bc]gh"))
    # print(decodeStr("3[a2[c]]"))

    b = "".join(["6", "7", "8"])
    # a = ["1", "2", "4"]
    # a += b
    print(b)



