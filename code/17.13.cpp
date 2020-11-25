#include<iostream>
#include<vector>
#include<string>
#include<cmath>
#include<algorithm>
using namespace std;



// //动态规划暴力解法
// class Solution {
// public:
//     int respace(vector<string>& dictionary, string sentence) {
//         int len=sentence.size();
//         vector<int> dp(len+1);
//         dp[0]=0;
//         for(int i=1;i<=len;i++){
//             dp[i]=dp[i-1]+1;
//             for(auto &word:dictionary){
//                 if(word.size()>i)continue;
//                 if(sentence.substr(i-word.size(),word.size())==word)
//                     dp[i]=min(dp[i-word.size()],dp[i]);
//             }
//         }
//         return dp[len];
//     }
// };

//动态规划+字典树(倒着存储)
class Solution{
public:
    struct node{
        bool end;
        node* next[26];
        node(bool end):end(end){
            for(int i=0;i<26;i++)next[i]=nullptr;
        }
    };
    node* root;
    void insert(string& word){
        node* cur=root;
        for(char &ch:word){
            if(cur->next[ch-'a'])cur=cur->next[ch-'a'];
            else{
                cur=cur->next[ch-'a']=new node(false);
            }
        }
        cur->end=true;
    }
    bool search(string&& word){
        node* cur=root;
        for(char &ch:word){
            if(cur->next[ch-'a'])cur=cur->next[ch-'a'];
            else return false;
        }
        return cur->end;
    }
    int respace(vector<string>& dictionary,string sentence){
        int len=sentence.size();
        vector<int> dp(len+1);
        dp[0]=0;
        root=new node(false);
        int MAX=0;
        for(auto item:dictionary){
            reverse(item.begin(),item.end());
            insert(item);
        }
        int a=0;
        for(int i=1;i<=len;i++){
            dp[i]=dp[i-1]+1;
            node* cur=root;
            for(int j=i-1;j>=0;j--){
                // j->i-1
                char ch=sentence[j];
                if(cur->next[ch-'a'])cur=cur->next[ch-'a'];
                else break;
                if(cur->end)dp[i]=min(dp[j],dp[i]);
            }
        }

        return dp[len];
    }
};



int main(){
    vector<string> dictionary{"looked","just","like","her","brother"};
    string sentence("jesslookedjustliketimherbrother");
    Solution s;
    s.respace(dictionary,sentence);
    return 0;
}