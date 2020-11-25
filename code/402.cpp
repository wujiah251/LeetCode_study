#include<iostream>
#include<vector>
#include<stack>
#include<string>

using namespace std;
class Solution {
public:
    string removeKdigits(string num, int k) {
        deque<char> s;
        for(int i=0;i<num.size();i++){
            while(!s.empty()&&s.back()>num[i]&&k>0){
                s.pop_back();
                k--;
            }
            s.push_back(num[i]);
        }
        while(k){
            s.pop_back();
            k--;
        }
       while(!s.empty()&&s.front()=='0')s.pop_front();
        if(s.empty())return "0";
        string res(s.size(),'0');
        for(int i=0;i<res.size();i++){
            res[i]=s.front();
            s.pop_front();
        }
        return res;
    }
};



int main()
{
    Solution s;
    s.removeKdigits("1432219",3);
    return 0;
}