#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;


//暴力解法，没过
class Solution{
public:
    vector<int> contain;
    bool canPartitionKSubsets(vector<int>& nums,int k){
        int sum=0;
        for(int i=0;i<nums.size();i++)sum+=nums[i];
        if(sum%k)return false;
        contain=vector<int>(k,sum/k);
        return dfs(nums,0);
    }
    bool dfs(vector<int> &nums,int index){
        if(index==nums.size())return true;
        for(int i=0;i<contain.size();i++){
            if(contain[i]>=nums[index]){
                contain[i]-=nums[index];
                if(dfs(nums,index+1))return true;
                contain[i]+=nums[index];
            }
        }
        return false;
    }
};
//暴力解法优化
//先对nums进行排序，优先放入大的数字
class Solution{
public:
    vector<int> contain;
    bool canPartitionKSubsets(vector<int>& nums,int k){
        int sum=0;
        for(int i=0;i<nums.size();i++)sum+=nums[i];
        if(sum%k)return false;
        contain=vector<int>(k,sum/k);
        sort(nums.begin(),nums.end(),[](int &a,int &b){return a>=b;});
        return dfs(nums,0);
    }
    bool dfs(vector<int> &nums,int index){
        if(index==nums.size())return true;
        for(int i=0;i<contain.size();i++){
            if(contain[i]>=nums[index]){
                contain[i]-=nums[index];
                if(dfs(nums,index+1))return true;
                contain[i]+=nums[index];
            }
        }
        return false;
    }
};



int main()
{
    return 0;
}