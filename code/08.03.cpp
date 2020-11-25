#include<iostream>
#include<vector>
using namespace std;



//暴力解法
class Solution {
public:
    int findMagicIndex(vector<int>& nums) {
        int len=nums.size();
        for(int i=0;i<len&&nums[i]<len;i++){
            if(nums[i]==i)return i;
        }
        return -1;
    }
};

class Solution{
public:
    int findMagicIndex(vector<int>& nums){
        int len=nums.size();
    }
};

int main()
{
    Solution s;
    vector<int> nums{-96, -87, -76, -66, -64, -57, -8, 4, 8,9,11};
    s.findMagicIndex(nums);
    return 0;
}