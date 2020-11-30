#include<iostream>
#include<vector>
#include<cmath>
#include<queue>
using namespace std;

class Solution {
public:
    int minimumDeviation(vector<int>&& nums) {
        multiset<int> set;
        int num,res=INT_MAX;
        for(int i=0;i<nums.size();i++){
            num=(nums[i]%2)? (nums[i]<<1):nums[i];
            set.insert(num);
        }
        while(*set.rbegin()%2==0){
            num=*set.rbegin();
            set.erase(num);
            set.insert(num/2);
            res=min(res,*set.rbegin()-*set.begin());
        }
        return res;
    }
};

int main()
{
    Solution s;
    s.minimumDeviation({3,5});
    return 0;
}