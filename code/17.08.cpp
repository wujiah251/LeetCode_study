#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

class Solution {
public:
    static bool cmp(pair<int,int>&a,pair<int,int>&b){
        return a.first==b.first? a.second<b.second:a.first<b.first;
    }
    int bestSeqAtIndex(vector<int>& height, vector<int>& weight) {
        return 0;
    }
};

int main()
{
    Solution s;
    vector<int> height{2868,5485,1356,1306,6017,8941,7535,4941,6331,6181},weight{5042,3995,7985,1651,5991,7036,9391,428,7561,8594};
    s.bestSeqAtIndex(height,weight);
    vector<int> a(5,1);
    a.resize(2);
    
    return 0;
}