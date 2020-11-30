#include<iostream>
#include<vector>
#include<stack>
#include<string>
using namespace std;

class Solution {
public:
    int minMoves(vector<int>&& nums, int limit) {
        vector<int> sum(2*limit+1,0);//0-limit*2
        int n=nums.size();
        int Max,Min;
        for(int i=0,j;i<n/2;i++){
            j=n-i-1;
            cout << nums[i] << nums[j] << limit << endl;
            Max=max(nums[i]+limit,limit+nums[j]);
            Min=min(nums[i]+1,1+nums[j]);
            // [Min,Max]这个范围是可以只操作一次达到得
            for(int k=2;k<=limit*2;k++){
                if(k==nums[i]+nums[j])continue;
                else if(k<=Max&&k>=Min)sum[k]++;
                else sum[k]+=2;
            
            }
        }
        int res=INT_MAX;
        for(int k=2;k<=limit*2;k++){
            res=min(sum[k],res);
        }
        return res;
    }
};
class Solution {
public:
    int minMoves(vector<int>&& nums, int limit) {
        vector<int> diff(2*limit+2,0);//0-limit*2+1
        int n=nums.size();
        int Max,Min,Sum;
        for(int i=0,j;i<n/2;i++){
            j=n-i-1;
            Max=max(nums[i]+limit,limit+nums[j]);
            Min=min(nums[i]+1,1+nums[j]);
            // [Min,Max]这个范围是可以只操作一次达到得
            diff[2]+=2;
            diff[Min]-=2;
            diff[Min]+=1;
            diff[Sum]-=1;
            diff[Sum+1]+=1;
            diff[Max+1]-=1;
            diff[Max+1]+=2;
            diff[2*limit+1]+=2;
        }
        int res=INT_MAX,temp=0;
        for(int k=2;k<=limit*2;k++){
            temp+=diff[k];
            res=min(temp,res);
        }
        return res;
    }
};


int main()
{
    Solution s;
    s.minMoves({1,2,4,3},4);

    return 0;
}