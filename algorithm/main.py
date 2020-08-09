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

@example("17. 电话号码的字母组合")
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
                    # the combination is done
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

if __name__ == '__main__':
 print(overhalf([1,2,3,2,2],5))
 reverseStr()
 print(letterCombinations("23"))
