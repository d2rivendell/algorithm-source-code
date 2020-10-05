
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


if __name__ == '__main__':
    print(intToRoman(234))
    arr = [1,2,3]
    res = arr[3:4]
    print(res)
    di = {'a': 1, 'b':2}
    for key in di:
        print(key)
    for (v, k) in enumerate(di):
        print(k,v)
