//https://leetcode.com/problems/longest-palindromic-substring/

#include <iostream>
#include <cassert>
#include <string>

using namespace std;

class SolutionSlow
{
    public :
        bool is_palindrome(const std::string& s)
        {
            auto b = s.begin();
            auto e = s.end() - 1;
            while(b < e)
            {
                if (*b != *e) return false;
                b++;
                e--;
            }
            return true;
        }

        string longestPalindrome_slower(string s) 
        {
            std::string lp = "";
            for (int i=0;i<s.size(); i++)
            {
                for (int j=i+1; j<=s.size();j++)
                {
                    auto ss = s.substr(i,j-i);
                    if (is_palindrome(ss))
                    {
                        if (ss.size() > lp.size())
                            lp = ss;
                    }
                }
            }
            return lp;
        }
};

class Solution {
public:
    // std::string s="babad";
    string longestPalindrome(string s) {
        if (s.empty()) return s;

        auto max_palindrome_length = 1;
        auto begin_palindrome = 0;

        // odd length
        for (int mid=0;mid<s.size(); mid++)
        {
            for (int increment_by=1; ; increment_by++)        
            {
                auto left_of_mid = mid - increment_by; 
                auto right_of_mid = mid + increment_by;
                if (left_of_mid < 0 || right_of_mid >= s.size() || s[left_of_mid] != s[right_of_mid])
                {
                    break;
                }

                // max length greter than before
                // mark length and begin                
                if ((right_of_mid-left_of_mid)+1 > max_palindrome_length) 
                {
                    max_palindrome_length = right_of_mid-left_of_mid+1;
                    begin_palindrome = left_of_mid;
                }
           
            }
        }

        // even length string
        for (int mid=0; mid<s.size() - 1; mid++)
        {
            for (int increment_by=1; ; increment_by++)        
            {
                // increment_by ==> 1 , mid , mid +1
                // increment_by ==> 2 . mid-1, mid+2
                auto left_of_mid = mid - increment_by + 1; 
                auto right_of_mid = mid + increment_by;
                if (left_of_mid < 0 || right_of_mid >= s.size() || s[left_of_mid] != s[right_of_mid])
                {
                    break;
                }

                // max length greter than before
                // mark length and begin                
                if ((right_of_mid-left_of_mid)+1 > max_palindrome_length) 
                {
                    max_palindrome_length = right_of_mid-left_of_mid + 1;
                    begin_palindrome = left_of_mid;
                }
           
            }
        }
        
        return s.substr(begin_palindrome,max_palindrome_length);
    }
};


int main()
{
    {
        std::string s="babad";
        Solution S;
        auto r = S.longestPalindrome(s);
        assert(r=="bab");
    }

    {
        std::string s="cbbd";
        Solution S;
        auto r = S.longestPalindrome(s);
        assert(r=="bb");
    }

    {
        std::string s="a";
        Solution S;
        auto r = S.longestPalindrome(s);
        assert(r=="a");
    }

    {
        std::string s="ac";
        Solution S;
        auto r = S.longestPalindrome(s);
        assert(r=="a");
    }

    {
        std::string s="gphyvqruxjmwhonjjrgumxjhfyupajxbjgthzdvrdqmdouuukeaxhjumkmmhdglqrrohydrmbvtuwstgkobyzjjtdtjroqpyusfsbjlusekghtfbdctvgmqzeybnwzlhdnhwzptgkzmujfldoiejmvxnorvbiubfflygrkedyirienybosqzrkbpcfidvkkafftgzwrcitqizelhfsruwmtrgaocjcyxdkovtdennrkmxwpdsxpxuarhgusizmwakrmhdwcgvfljhzcskclgrvvbrkesojyhofwqiwhiupujmkcvlywjtmbncurxxmpdskupyvvweuhbsnanzfioirecfxvmgcpwrpmbhmkdtckhvbxnsbcifhqwjjczfokovpqyjmbywtpaqcfjowxnmtirdsfeujyogbzjnjcmqyzciwjqxxgrxblvqbutqittroqadqlsdzihngpfpjovbkpeveidjpfjktavvwurqrgqdomiibfgqxwybcyovysydxyyymmiuwovnevzsjisdwgkcbsookbarezbhnwyqthcvzyodbcwjptvigcphawzxouixhbpezzirbhvomqhxkfdbokblqmrhhioyqubpyqhjrnwhjxsrodtblqxkhezubprqftrqcyrzwywqrgockioqdmzuqjkpmsyohtlcnesbgzqhkalwixfcgyeqdzhnnlzawrdgskurcxfbekbspupbduxqxjeczpmdvssikbivjhinaopbabrmvscthvoqqbkgekcgyrelxkwoawpbrcbszelnxlyikbulgmlwyffurimlfxurjsbzgddxbgqpcdsuutfiivjbyqzhprdqhahpgenjkbiukurvdwapuewrbehczrtswubthodv";
        Solution S;
        auto r = S.longestPalindrome(s);
        std::cout << r << std::endl;
    }
}