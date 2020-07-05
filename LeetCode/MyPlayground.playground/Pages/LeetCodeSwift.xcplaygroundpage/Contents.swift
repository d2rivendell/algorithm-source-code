import Foundation


func example(_ name: String, clourse: ()->Void){
    print("\(name)")
    print("-------")
    clourse()
    print("-------")
}

extension String{
    func subString(begin: Int, end: Int) -> String{
         let startIndex = self.startIndex
         let beginIndex = self.index(startIndex, offsetBy: begin)
         let endIndex = self.index(beginIndex, offsetBy: end - begin)
         return self[beginIndex...endIndex].description
    }
}

example("最小覆盖子串, 为啥该方法在swift下耗时这么长") {
    
    /*
     给你一个字符串 S、一个字符串 T，请在字符串 S 里面找出：包含 T 所有字符的最小子串。
     输入: S = "ADOBECODEBANC", T = "ABC"
     输出: "BANC"
     */
    let S = "zcaethzkc", T = "ak"//T中有重复字符怎么办
    func minWindow(_ s: String, _ t: String) -> String {
        //need统计滑动窗口内外的字符,窗口外t中的目标字符是>=1(有重复)非目标字符是0, 在窗口t中目标字符是0，外其他字符<0
        var need: [Character: Int] = [:]
        t.forEach({ (cc) in
            let count = need[cc] ?? 0
            need[cc] = count + 1
        })//现在need里面记录的是要查找的字符
        var needCount = t.count//t的个数
        var i = 0
        var win = (0, s.count+1)
        let startIndex = s.startIndex
        for (idx, c) in s.enumerated(){
            let tCount = need[c] ?? 0
            if tCount > 0{//找到了
                needCount -= 1
            }
            need[c] = tCount - 1//
            if needCount==0{//1. [i, idx]窗口范围内找到了含有字符T
                //但是这个范围之内可能是[x1,x2, z1,z2,x3,z3] (z是要查找的字符，x是无关字符)
                //需要把窗口已到z2处作为新窗口，查找可能更小的
                print("啥？")
                while true {
                    let insideC = s[s.index(startIndex, offsetBy: i)]
                    let tCount = need[insideC] ?? 0
                    if tCount == 0{//3. [i, idx]内找第一个目标字符，把窗口在此位置前移,放出一个目标字符
                        if(idx - i) < win.1 - win.0{//窗口更小，更新窗口
                            win = (i, idx)
                        }
                        need[insideC] = tCount+1//移出窗口要+1
                        i += 1//窗口前一位
                        needCount += 1
                        print(needCount)
                        break
                    }
                    i += 1//2. 把窗口前移
                    need[insideC] = tCount + 1//非目标字符移出窗口后+1
                }
            }
        }
        if win.1 - win.0 > s.count{
             return ""
        }else{
            let begin = s.index(startIndex, offsetBy: win.0)
            let end = s.index(startIndex, offsetBy: win.1)
            return s[begin...end].description
        }
       
    }
    print(Date.init())
    print(minWindow(S, T))
    print(Date.init())
    

}




example("最长回文") {
    /*
     给定一个字符串 s，找到 s 中最长的回文子串。你可以假设 s 的最大长度为 1000。
     
     示例 1：
     
     输入: "babad"
     输出: "bab"
     注意: "aba" 也是一个有效答案
     https://leetcode-cn.com/problems/longest-palindromic-substring/
     */
    func longestPalindrome(_ s: String) -> String {
        if s.count == 0 || s.count == 1{
            return s
        }
        var array: [Character] = []
        let startIndex = s.startIndex
        var w1 = 0
        var w2 = s.count + 1
        var res:[Character] = []
        var mWin = (w1, w2)
        for (idx, ch) in s.enumerated(){
            array.append(ch)
            print(array)
            if isPalindrome(ch: array){
                print(array)
                if idx - w1 < mWin.1 - mWin.0{
                    res = array
                   
                    mWin = (w1, idx)
                }
                w1 += 1//窗口往前移动一步
                array = Array(array.dropFirst())//把第一个丢掉
            }
            w2 = idx
        }
        print(res)
        if res.count < s.count{
            return res.reduce("", { $0 + String($1)})
        }else{
            return ""
        }
    }
    
    func isPalindrome(ch: [Character]) -> Bool{
        let count = ch.count
        if count == 0 || count == 1{ //入口已经做判断了
            return false
        }
        var begin = 0
        var end = count
        while begin < end {
            if ch[begin] != ch[end-1]{
                return false
            }
            begin += 1
            end -= 1
        }
        return true
    }
    print(longestPalindrome("cbbd"))
}

