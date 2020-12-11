#include<iostream>
#include<vector>
#include<set>
#include<unordered_set>
#include<cmath>
using namespace std;

class Solution {
public:
    int count(int n){
        int res=0;
        while(n){
            n&=n-1;
            res++;
        }
        return res;
    }
    int minimumIncompatibility(vector<int>& nums, int k) {
        int n=nums.size();
        int size=n/k;
        // 预处理所有规模为n/k的子集的不兼容性
        vector<int> value(1<<n,-1);
        for(int i=0,Max=1<<n;i<Max;i++){
            if(count(i)==size){
                unordered_set<int> set;
                bool flag=true;
                for(int j=0;j<n;j++){
                    if(i&(1<<j)){
                        if(set.find(nums[j])!=set.end()){
                            flag=false;
                            break;
                        }
                        else set.insert(nums[j]);
                    }
                }
                if(flag){
                    int Max=INT_MIN,Min=INT_MAX;
                    for(int j=0;j<n;j++){
                        if(i&(1<<j)){
                            Max=max(Max,nums[j]);
                            Min=min(Min,nums[j]);
                        }
                    }
                    value[i]=Max-Min;
                }
            }
        }//与处理完毕
        vector<int> dp(1<<n,-1);
        dp[0]=0;
        // 动态规划
        for(int mask=1;mask<(1<<n);++mask){
            if(count(mask)%size==0){
                for(int sub=mask;sub;sub=(sub-1)&mask){
                    if(value[sub]!=-1&&dp[mask^sub]!=-1){
                        if(dp[mask]==-1){
                            dp[mask]=dp[mask^sub]+value[sub];
                        }
                        else{
                            dp[mask]=min(dp[mask^sub]+value[sub],dp[mask]);
                        }
                    }
                }
            }
        }
        
        return dp[(1<<n)-1];
    }
};

int main(){
    Solution s;
    vector<int> nums{1,2,1,4};
    cout << s.minimumIncompatibility(nums,2);
    return 0;
}


