#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

class Solution {
public:
    int getMoneyAmount(int n) {
        //动态规划
        vector<vector<int>> dp(n+1,vector<int>(n+1,-1));//以-1表示为访问过
        for(int i=1;i<=n;i++)dp[i][i]=0;
        return dfs(dp,1,n);
    }
    int dfs(vector<vector<int>>& dp,int i,int j){
        if(i>j)return 0;
        if(dp[i][j]>=0)return dp[i][j];
        else{
            int MAX=INT_MIN,res=INT_MAX;
            for(int k=(i+j)/2;k<=j;k++){
                MAX=max(dfs(dp,i,k-1),dfs(dp,k+1,j));
                res=min(res,MAX+k);
            }
            dp[i][j]=res;
            return res;
        }
    }
};

int main()
{
    Solution s;
    s.getMoneyAmount(4);
    return 0;
}