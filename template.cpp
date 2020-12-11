#include<iostream>
#include<vector>
#include<queue>
#include<sstream>
// #pragma GCC optimize("Ofast,no-stack-protector")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
// #pragma GCC optimize("unroll-loops")
using namespace std;

class Solution {
public:
    int str2int(const string& str){
        stringstream ss;
        ss<<str;
        int res;
        ss>>res;
        return res;
    }
    int calculate(string s) {
        vector<string> temp;// 存放数字、运算符号
        int p=0;
        while(p<s.size()){
            switch(s[p]){
                case '+':temp.push_back("+");p++;break;
                case '-':temp.push_back("-");p++;break;
                case '*':temp.push_back("*");p++;break;
                case '/':temp.push_back("/");p++;break;
                case ' ':p++;break;
                default:
                    int j=p+1;
                    for(;j<s.size()&&s[j]>='0'&&s[j]<='9';j++);
                    temp.push_back(s.substr(p,j-p));
                    p=j;
            }
            
        }
        deque<int> s1;
        deque<char> s2;
        int num=1,sum=0;
        p=0;
        while(p<temp.size()){
            switch(temp[p][0]){
                case '+':s2.push_back('+');break;
                case '-':s2.push_back('-');break;
                case '*':
                    num=s1.back();s1.pop_back();
                    num*=str2int(temp[++p]);
                    s1.push_back(num);
                    break;
                case '/':
                    num=s1.back();s1.pop_back();
                    num/=str2int(temp[++p]);
                    s1.push_back(num);
                    break;
                default:
                    s1.push_back(str2int(temp[p]));
            }
            p++;
        }
        int a,b;
        while(!s2.empty()){
            a=s1.front();s1.pop_front();
            b=s1.front();s1.pop_front();
            char sign=s2.front();s2.pop_front();
            if(sign=='+')s1.push_front(a+b);
            else s1.push_front(a-b);
        }
        return s1.front();
    }
};


int main()
{
    Solution s;
    string str{"3 + 2  *4+2+2-111+232*3/2/3*1"};
    cout << s.calculate(str); 
    return 0;
}