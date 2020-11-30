#include<iostream>
#include<vector>
#include<stack>
#include<string>
using namespace std;

class Solution{
public:
    vector<int> temp;
    int merge_sort(vector<int>& nums,int start,int end){
        if(start>=end)return 0;
        int res=0;
        int mid=(end-start)/2+start;
        res+=merge_sort(nums,start,mid);
        res+=merge_sort(nums,mid+1,end);
        res+=merge(nums,start,mid,mid+1,end);
        return res;
    }
    int merge(vector<int>& nums,int l1,int r1,int l2,int r2){
        int res=0;
        int p1=r1,p2=r2;
        while(p1>=l1&&p2>=l2){
            if(nums[p1]>2* (long)nums[p2]){res+=p2-l2+1;p1--;}
            else p2--;
        }
        for(int i=l1;i<=r2;i++){
            temp[i]=nums[i];
        }
        p1=l1;p2=l2;
        for(int k=l1;k<=r2;k++){
            if(p1>r1)nums[k]=temp[p2++];
            else if(p2>r2)nums[k]=temp[p1++];
            else if(temp[p1]<=temp[p2])nums[k]=temp[p1++];
            else nums[k]=temp[p2++];
        }
        return res;
    }
    int reversePairs(vector<int>& nums){
        temp=nums;
        return merge_sort(nums,0,nums.size()-1);
    }
};



int main()
{
    Solution s;
    vector<int> nums{1,3,2,3,1};
    s.reversePairs(nums);

    return 0;
}