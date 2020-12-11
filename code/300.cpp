#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
using namespace std;

// class Solution {
// public:
//     int lengthOfLIS(vector<int>& nums) {
//         if(nums.size()==0)return 0;
//         vector<int> dp(nums.size());//dp[i]表示前i+1个元素末尾为第i个元素的最长上升子序列长度，一定有性质：if i<j then dp[i]<dp[j]
//         // dp[i]=max(dp[j])+1,七张0<=j<i，且num[j]<num[i]
//         for(int i=0;i<nums.size();i++){
//             dp[i]=1;
//             for(int j=0;j<i;j++){
//                 if(nums[j]<nums[i]){
//                     dp[i]=max(dp[i],dp[j]+1);
//                 }
//             }
//         }
//         return *max_element(dp.begin(),dp.end());
//     }
// };

class Solution {
public:
    int upper_bound(vector<int> &dp,int len,int num){
        int l=1,r=len,mid;
        while(l<=r){
            if(dp[l]>=num)return l-1;
            else if(dp[r]<num)return r;
            mid=(r-l)/2+l;
            if(dp[mid]>=num)r=mid-1;
            else l=mid+1;
        }
        return r-1;
    }
    int lengthOfLIS(vector<int>& nums) {
        if(nums.size()==0)return 0;
        vector<int> dp(nums.size()+1);
        dp[1]=nums[0];
        int len=1;
        for(int i=1;i<nums.size();i++){
            if(dp[len]<nums[i]){
                dp[++len]=nums[i];
                continue;
            }
            auto index=upper_bound(dp,len,nums[i]);
            dp[index+1]=nums[i];
        }
        return len;
    }
};

int main(){
    Solution s;
    vector<int> nums{10,9,2,5,3,7,101,4};
    cout << s.lengthOfLIS(nums);
    return 0;
}
