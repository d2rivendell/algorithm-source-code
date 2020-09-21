import collections

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
    if arr[-1][-1] is '.':#最后一个元素的符号
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
if __name__ == '__main__':
    arr=[0]
    print(arr[1:])
