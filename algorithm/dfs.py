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
@example("数组排列 -回溯法")
def permute(nums):
        if nums is None or len(nums) == 0:
          return []
        numsLen = len(nums)
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
                for i in range(idx, numsLen):
                    if isRepeat(idx, i):
                        continue
                    nums[idx], nums[i] = nums[i], nums[idx]
                    dfs(idx + 1)
                    nums[i], nums[idx] = nums[idx], nums[i]

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
