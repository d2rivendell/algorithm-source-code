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

example("最小覆盖子串") {
    
    /*
     给你一个字符串 S、一个字符串 T，请在字符串 S 里面找出：包含 T 所有字符的最小子串。
     输入: S = "ADOBECODEBANC", T = "ABC"
     输出: "BANC"
     */
    let S = "asdfghbnm", T = "bn"//T中有重复字符怎么办
    func minWindow(_ s: String, _ t: String) -> String {
        if s.count < t.count{
            return ""
        }
        var begin = 0
        var end = 0
        let totalCount = s.count
        var min = s.count+1
        for i in 0..<s.count{
            var dict: [Character: Int] = [:]
            for j in i..<totalCount{
                var isContainAll = true
                
                var subStr = s.subString(begin: i, end: j)
                subStr.forEach({ (c) in
                    if let e = dict[c] {
                        dict[c] = e + 1
                    }else{
                        dict[c] = 1
                    }
                })
                for c in t{
                    if let v = dict[c], v > 0{
                        dict[c] = v-1
                    }else{
                        isContainAll = false
                    }
                }
                if isContainAll,
                    j - i < min{
                    begin = i
                    end = j
                    min = j - i
                    break
                }
            }
        }
        if min == s.count + 1{
            return ""
        }
        return s.subString(begin: begin, end: end)
    }
    print(Date.init())
    print(minWindow(S, T))
    print(Date.init())
    
}


