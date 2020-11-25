#include<vector>
using namespace std;

class Solution {
public:
    void swap(int& a,int& b){
        int temp=a;
        a=b;
        b=temp;
    }
    int removeElement(vector<int>& nums, int val) {
        int p1=0,p2=0;
        for(;p1<nums.size();p1++){
            if(nums[p1]==val){
                while(p2<nums.size()&&(nums[p2]==val||p2<=p1))p2++;
                if(p2==nums.size())break;
                swap(nums[p1],nums[p2]);
                p2++;
            }
        }
        while(nums.back()==val)nums.pop_back();
        return nums.size();
    }
};

int main()
{
    Solution s;
    vector<int> nums{0,1,2,2,3,0,4,2};
    s.removeElement(nums,2);
    return 0;
}