import Foundation


func example(_ name: String, clourse: ()->Void){
    print("\(name)")
    print("-------")
    clourse()
    print("-------")
}


example("最小覆盖子串") {
    /*
     给你一个字符串 S、一个字符串 T，请在字符串 S 里面找出：包含 T 所有字符的最小子串。
     输入: S = "ADOBECODEBANC", T = "ABC"
     输出: "BANC"
     */
    let S = "ADOBECODEBANC", T = "ABC"
    func minWindow(_ s: String, _ t: String) -> String {
        var min: Int = -1
        let startIndex = s.startIndex
        for i in 0..<s.count{
            for j in i..<s.count{
               let begin = s.index(startIndex, offsetBy: j)
               let end = s.index(begin, offsetBy: j)
               let sub = s[begin...end]
               var allContain = true
                for c in t{
                    if sub.contains(c) == false{
                        allContain = false
                    }
                }
                if allContain{
                    if(j-i+1) < min{
                      min = j - i + 1
                    }else{
                        break
                    }
                }
            }
        }
        return ""
    }
    print(minWindow(S, T))
    
}





