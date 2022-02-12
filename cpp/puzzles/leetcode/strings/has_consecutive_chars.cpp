#include<string>
#include<cassert>

class Solution{
    public:
        // last char at N-1, second last N-2, third last N-3
        bool has_consecutive_3_chars(const std::string& str)
        {
            for (size_t i = 0; i<= str.size()- 3; i++)
            {
                if (str[i] == str[i+1] && str[i] == str[i+2])
                {
                    return true;
                }
            }
            return false;
        }

                // last char at N-1, second last N-2, third last N-3
        bool has_consecutive_k_chars(const std::string& str, int k)
        {
            for (size_t i = 0; i<= str.size()- k; i++)
            {
                size_t b = i;
                size_t e = b + k - 1;
                bool has_consecutive = true;
                while (b <= e)
                {
                    if (str[b] != str[e])
                    {
                        has_consecutive = false;
                        break;
                    }
                    b++;
                    i--;
                }
                if (has_consecutive) return true;
            }
            return false;
        }

};


int main()
{
    Solution s;
    assert(s.has_consecutive_3_chars("youtttube"));
    assert(!s.has_consecutive_3_chars("youtube"));
    assert(s.has_consecutive_3_chars("youtubeee"));
    assert(s.has_consecutive_3_chars("yyyoutube"));


    return 0;
}