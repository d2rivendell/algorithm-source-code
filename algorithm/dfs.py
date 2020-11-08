import collections

def example(text):
    def decorator(func):
       def wrapper(*args, **kw):
           print("=====" + text + "=======")
           return func(*args, **kw)
       return  wrapper
    return decorator



@example("17. 电话号码的字母组合 -回溯法")
def letterCombinations(digits):
    """
        :type digits: str
        :rtype: List[str]
        """
    phone = {'2': ['a', 'b', 'c'],
                '3': ['d', 'e', 'f'],
                '4': ['g', 'h', 'i'],
                '5': ['j', 'k', 'l'],
                '6': ['m', 'n', 'o'],
                '7': ['p', 'q', 'r', 's'],
                '8': ['t', 'u', 'v'],
                '9': ['w', 'x', 'y', 'z']}
                    
    def backtrack(combination, next_digits):
                # next_digits不能再分的时候
                if len(next_digits) == 0:
                    output.append(combination)
                # next_digits还能分的时候
                else:
                    for letter in phone[next_digits[0]]:
                        backtrack(combination + letter, next_digits[1:])
                                            
    output = []
    if digits:
       backtrack("", digits)
    return output

#针对字符串的排列 https://leetcode-cn.com/problems/zi-fu-chuan-de-pai-lie-lcof/
@example("全排列 -回溯法")
def strArrange(str):
    listStr = list(str)
    output = []
    def backtree(combination, next):
        if len(next) == 0:
            output.append(combination)
            return
        else:
            for (idx, sub) in enumerate(next):
                next_copy = next.copy()
                # 不使用used表，直接移除掉使用过的传给下一层
                next_copy.pop(idx)
                backtree(combination+sub, next_copy)

    backtree("", listStr)
    return output

#https://leetcode-cn.com/problems/permutations/submissions/
#nums无重复数字
@example("数组排列 -回溯法")
def permute(nums):
        if nums is None or len(nums) == 0:
          return []
        numsLen = len(nums)
        output = []
        # 使用used记录上一层已经使用的数字，确保下一层不会重复使用
        # 这种情况只有数组中元素不重复的时候才有用， 有局限性
        used = []
        res = []
        for i in range(numsLen):
            res.append(0)

        def dfs(idx):
            if idx == numsLen:
                output.append(res[:])
                return
            else:
                for v in nums:
                    if v in used:
                        continue
                    res[idx] = v
                    used.append(v)
                    dfs(idx + 1)
                    #恢复used表， res不需要恢复，回溯的时候会覆盖掉
                    used.remove(v)

        dfs(0)
        return output

#使用交换的思路处理
@example("全排列 -回溯法2")
def permute2(nums):
    if nums is None or len(nums) == 0:
        return []
    numsLen = len(nums)
    output = []

    def swap(arr, i, j):
        temp = arr[i]
        arr[i] = arr[j]
        arr[j] = temp

    def dfs(idx):
        if idx == numsLen:
            # output.append(nums.copy())
            output.append(nums[:])
        else:
            for i, v in enumerate(nums):
                if i < idx:
                    continue
                # 交换 i 和idx的位置的元素
                nums[idx], nums[i] = nums[i], nums[idx]
                # swap(nums,idx, i)
                dfs(idx + 1)
                # 恢复
                nums[i], nums[idx] = nums[idx], nums[i]
                # swap(nums,i, idx)

    dfs(0)
    return output


#https://leetcode-cn.com/problems/permutations-ii/
@example("不重复全排列 -回溯法2")
def permuteUnique(nums):
        if nums is None or len(nums) == 0:
            return []
        numsLen = len(nums)
        output = []

        def isRepeat(idx, i):
            # [idx, i-1] 之间是否有和i重复的
            while idx <= i - 1:
                if nums[idx] == nums[i]:
                    return True
                idx += 1
            return False

        def dfs(idx):
            if idx == numsLen:
                # output.append(nums.copy())
                output.append(nums[:])
            else:
                # 二：dic = set()  #或者可以每一层都可以用一个set来记录。
                for i in range(idx, numsLen):
                    # 二：if nums[i] in dic:
                    if isRepeat(idx, i):
                        continue
                    nums[idx], nums[i] = nums[i], nums[idx]
                    dfs(idx + 1)
                    nums[i], nums[idx] = nums[idx], nums[i]

        dfs(0)
        return output


@example("22. 括号生成 https://leetcode-cn.com/problems/generate-parentheses/")
def generateParenthesis(n):
    """
     剪枝处理： '('的个数不大于n, 当 
    """
    if n == 0:
        return []
    # 回溯算法, '('符号要小于n-1个
    output = []

    def dfs(res, left, right):
        """
        left:  res中'{'的个数为left-1
        right: res中'}'的个数为right-1
        """
        if len(res) == n * 2:
            output.append(res)
        else:
            #先添加一个左括号
            if left < n:
                dfs(res + '(', left + 1, right)

            #当左边括号大于右边时 右边 f才有可能加括号
            if right < left:
                dfs(res + ')', left, right + 1)

    dfs('', 0, 0)
    return output

@example("10. 正则表达式匹配 https://leetcode-cn.com/problems/regular-expression-matching/")
def isMatch(s, p):
    """
        '.' 匹配任意单个字符
        '*' 匹配零个或多个前面的那一个元素
    """
    l1 = len(s)
    l2 = len(p)
    i = 0
    j = 0
    if l1 == 0:
        if l2 == 0:
            return True
        elif j + 1 < l2 and p[j + 1] == '*':  # s匹配完了， p剩下的看能不能都当作空气
            return isMatch(s, p[j + 2:])
        return False
    if l2 == 0:
        return False

    if s[i] == p[j] or p[j] == '.':#当前字符匹配
        # ⚠️(aaa, ab*a*c*a)
        if j + 1 < l2 and p[j + 1] == '*':#如果下一个是*号
            res = isMatch(s[i:], p[j + 2:])  #1️⃣把（p[j]+*）当作空气 消耗掉， i不动
            if res == False:#当作空气的方案行不通
                return isMatch(s[i + 1:], p[j:]) #(2️⃣p[j]+*）匹配当前， 不消耗（可能后面还要用到， 消耗留给1️⃣👆）
            else:
                return True
        else:  # 下一个不是*，把当前的p[j]用掉， i也往前挪
            return isMatch(s[i + 1:], p[j + 1:])
    else:#当前字符不匹配
        if j + 1 < l2 and p[j + 1] == '*':#如果下一个是*号
           return isMatch(s[i:], p[j + 2:])  #当前p[j]位置结合下一个* 当作空气
        else:
           return False

# 组合 https://leetcode-cn.com/problems/combinations
@example("77. 组合")
def combine( n, k) :
    """
        给定两个整数 n 和 k，返回 1 ... n 中所有可能的 k 个数的组合。
        输入: n = 4, k = 2  ----->C(2,4)
        输出:
        [
        [2,4],
        [3,4],
        [2,3],
        [1,2],
        [1,3],
        [1,4],
        ]
    """
    if k == 0 or n == 0:
        return []
    output = []
    res = []
    def dfs(cur,n, res):
            #⚠️这一步放在剪枝前面 否则会被跳过
            if len(res) == k:
                output.append(res[:])
                return
            #剪枝1
            #   if cur == n + 1:
            #       print(cur, res)
            #       return
            #剪枝2 剩下无法和res凑够k个
            if len(res) + (n - cur + 1) < k:
                #   print("-",cur,"-")
                return
            #有两种可能
            #1.把当前数字作为一个组合元素
            res.append(cur)
            dfs(cur+1, n, res)
            #2. 当前数字不作为组合元素
            res.remove(cur)
            dfs(cur+1, n, res)
    dfs(1,n,res)
    return output

#https://leetcode-cn.com/problems/subsets/
@example("子集")
def subsets(nums):
    """
        输入: nums = [1,2,3]
        输出:
        [
        [3],
          [1],
          [2],
          [1,2,3],
          [1,3],
          [2,3],
          [1,2],
          []
        ]
    """
    if nums is None:
        return []
    n = len(nums)
    output = []
    res = []
    def dfs(idx, res):
        if idx == n:
            output.append(res[:])
            return
        #1.选取当前的位置作为子集的一部分
        res.append(nums[idx])
        dfs(idx+1, res)
        #2.跳过当前
        res.remove(nums[idx])
        dfs(idx+1, res)
    
    dfs(0, res)
    return output

@example("组合总和") #https://leetcode-cn.com/problems/combination-sum/
def combinationSum(candidates, target):
    """
     找出 candidates 中所有可以使数字和为 target 的组合。candidates 中的数字可以无限制重复被选取。
     示例 1：
     输入：candidates = [2,3,6,7], target = 7,
     所求解集为：
     [
       [7],
       [2,2,3]
     ]
    """
    output = []
    n = len(candidates)
    res = []

    def dfs(idx, remain):
        if remain == 0:
            output.append(res[:])
            return
        if idx == n or remain < 0:
            return
        # 1.一直选择当前
        res.append(candidates[idx])
        dfs(idx, remain - candidates[idx])
        # 2. 不选当前
        res.remove(candidates[idx])
        dfs(idx + 1, remain)

    dfs(0, target)
    return output

@example("N皇后") #https://leetcode-cn.com/problems/n-queens/
def solveNQueens(n):
        output = []
        record = [-1] * n
        def isValid(row, col):
            for pre_row in range(row):
                pre_col = record[pre_row]
                # 纵向和对角线不能存在  ｜x1-x2｜ = |y1-y2|
                if col == pre_col or abs(col - pre_col) == row - pre_row:
                    return False
            return True
        def findQueue(idx):
             if(idx == n):
                 arr = []
                 for i in range(n):#行
                     temp = ['.'] * n
                     temp[record[i]] = 'Q'
                     arr.append(''.join(temp))
                 output.append(arr)
             else:
                 for col in range(n):
                     if isValid(idx, col):
                         record[idx] = col
                         findQueue(idx+1)
        findQueue(0)
        return output


# https://leetcode-cn.com/problems/restore-ip-addresses/
@example("93. 复原IP地址")
def restoreIpAddresses(s):
    """
          例如："0.1.2.201" 和 "192.168.1.1" 是 有效的 IP 地址，但是
          "0.011.255.245"、"192.168.1.312" 和 "192.168@1.1" 是 无效的 IP 地址。
    :return:
    """
    output = []
    n = len(s)
    if n < 4 or n > 12:
        return []

    def checkValid(arr):
        v = int(arr[0]) * 100 + int(arr[1]) * 10 + int(arr[2])
        return v <= 255

    def dfs(strArr, res):
        if len(strArr) == 0 and len(res) == 4:
            output.append(".".join(res))
        else:
            if len(strArr) == 0:
                return
            if len(res) == 4:
                return
            if strArr[0] != "0":
                if len(strArr) >= 3 and checkValid(strArr[:3]):
                    dfs(strArr[3:], res + ["".join(strArr[:3])])
                if len(strArr) >= 2:
                    dfs(strArr[2:], res + ["".join(strArr[:2])])
                if len(strArr) >= 1:
                    dfs(strArr[1:], res + ["".join(strArr[:1])])
            else:
                dfs(strArr[1:], res + ["".join(strArr[:1])])
    dfs(list(s), [])
    return output

#https://leetcode-cn.com/problems/fu-za-lian-biao-de-fu-zhi-lcof/
@example("剑指 Offer 35. 复杂链表的复制")
class Node:
    def __init__(self, x, next=None, random=None):
        self.val = int(x)
        self.next = next
        self.random = random
def copyRandomList(head):
    """
    :type head: Node
    :rtype: Node
    """
    visited = {}

    def dfs(node):
        if node is None:
            return node
        if node in visited:
            return visited[node]
        newNode = Node(node.val, None, None)
        visited[node] = newNode
        newNode.next = dfs(node.next)
        newNode.random = dfs(node.random)
        return newNode

    return dfs(head)
if __name__ == '__main__':
 #print(overhalf([1,2,3,2,2],5))
 #reverseStr()
 print(letterCombinations("23"))
 print(strArrange("abc"))
 print(permute([1,2,3]))
 arr = ["I"] * 2
 arr.append("M" * 3)
 print(arr)
 # str = "dasb"
 # toLi = list("dsb")
 # print(toLi)
 # print(''.join(toLi))
 # vb = [1,2]
 # vb += [3]
 # print(vb)
 # table = {}
 # print(table.get('1',  3))
 #
 # string = '.*'
 # print(string[0+2:])
 # print(isMatch("ab", ".*c"))
 arr = [1,2,3]
 arr_2 = map(str, arr)
 print(list(arr_2))



