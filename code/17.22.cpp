#include<iostream>
#include<list>
#include<vector>
#include<algorithm>
#include<queue>
#include<string>
#include<unordered_map>
#include<unordered_set>
using namespace std;


class Solution {
public:
    bool check(string &a,string &b){
        int sum=0;
        for(int i=0;i<a.size();i++){
            if(a[i]!=b[i])sum++;
            if(sum>1)return false;
        }
        return true;
    }
    vector<string> findLadders(string startWord, string endWord, vector<string> wordList) {
        int len=wordList.size();
        unordered_set<string> words;
        unordered_map<string,int> word2id; // word->id
        vector<string> id2word(len); // id->word
        int index=0;
        // 处理字典内容
        for(string &word:wordList){
            word2id[word]=index;
            id2word[index]=word;
            words.insert(word);
            index++;
        }
        // endword不在字典中则返回{}
        if(words.find(endWord)==words.end())return {};
        // startword不在字典中则插入
        if(words.find(startWord)==words.end()){
            words.insert(startWord);
            word2id[startWord]=index;
            id2word.push_back(startWord);
        }
        //生成无向图邻接表表示方法
        vector<vector<int>> edges(id2word.size());
        for(int i=0;i<id2word.size();i++){
            for(int j=i+1;j<id2word.size();j++){
                if(check(id2word[i],id2word[j])){
                    edges[i].push_back(j);
                    edges[j].push_back(i);
                }
            }
        }
        //单方向广度优先搜索
        queue<int> q;
        q.push(word2id[startWord]);
        vector<int> length(id2word.size(),INT_MAX);
        int t=0;
        while(!q.empty()){
            int len=q.size();
            for(int i=0;i<len;i++){
                int cur=q.front();q.pop();
                if(t<length[cur])length[cur]=t;
                else continue;
                for(int j:edges[cur]){
                    if(t+1<length[j]){
                        q.push(j);
                    }
                }
            }
            t++;
        }
        if(length[word2id[endWord]]==INT_MAX)return {};
        list<string> res;
        int pre=word2id[endWord];
        t=length[pre];
        res.push_back(endWord);
        t--;
        while(t>=0){
            for(int i:edges[pre]){
                if(length[i]==t){res.push_front(id2word[i]);pre=i;;break;}
            }
            t--;
        }
        vector<string> Res;
        copy(res.begin(),res.end(),std::back_inserter(Res));
        return Res;
    }
};

int main(){

    Solution s;
    s.findLadders("hit","cog",{"hot","dot","dog","lot","log","cog"});

    return 0;
}