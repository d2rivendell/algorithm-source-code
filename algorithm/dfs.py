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
                    # iterate over all letters which map
                    # the next available digit
                    for letter in phone[next_digits[0]]:
                        # append the current letter to the combination
                        # and proceed to the next digits
                        backtrack(combination + letter, next_digits[1:])
                                            
    output = []
    if digits:
       backtrack("", digits)
    return output

@example("排列 -回溯法")
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
                next_copy.pop(idx)
                backtree(combination+sub, next_copy)

    backtree("", listStr)
    return output

#https://leetcode-cn.com/problems/permutations/submissions/
@example("数组排列 -回溯法")
def permute(nums):
        numsLen = len(nums)
        if nums is None or numsLen == 0:
            return []
        output = []
        #使用used记录上一层已经使用的数字，确保下一层不会重复使用
        used = []
        #法一：传递result给下一个dfs前把当前result copy以下
        # def dfs(idx, res):
        #     if idx == numsLen:
        #         output.append(res)
        #         return
        #     else:
        #         for v in nums:
        #             if v in used:
        #                 continue
        #             used.append(v)
#             copy_res = res.copy()#传递给下一层之前需要拷贝
        #             copy_res.append(v)
        #             dfs(idx + 1,  copy_res)
        #             #恢复
        #             used.remove(v)
        # dfs(0, [])

        #法二： 传递result给下一个dfs后，把最后一个移除掉。 最后一层出结果时copy result
        # def dfs(idx, res):
        #     if idx == numsLen:
        #         output.append(res.copy())
        #         return
        #     else:
        #         for v in nums:
        #             if v in used:
        #                 continue
        #             used.append(v)
        #             # copy_res = res.copy()
        #             # copy_res.append(v)
        #             res.append(v)
        #             dfs(idx + 1, res)
        #             # 恢复
        #             used.remove(v)
        #             res.pop()
        #
        # dfs(0, [])

        #法三， 使用同个result， 最后一层出结果时再copy
        res = []
        for i in range(numsLen):
            res.append(0)

        def dfs(idx):
            if idx == numsLen:
                output.append(res.copy())
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


if __name__ == '__main__':
 #print(overhalf([1,2,3,2,2],5))
 #reverseStr()
 print(letterCombinations("23"))
 print(strArrange("abc"))

 str = "dasb"
 toLi = list("dsb")
 print(toLi)
 print(''.join(toLi))
