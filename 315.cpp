#include<iostream>
#include<vector>
#include<cmath>
#include<map>
using namespace std;


// //暴力解
// class Solution {
// public:
//     vector<int> countSmaller(vector<int>& nums){
//         vector<int> res(nums.size(),0);
//         for(int i=0;i<nums.size();i++){
//             for(int j=nums.size()-1;j>i;j--)
//                 if(nums[j]<nums[i])res[i]++;
//         }
//         return res;
//     }
// };

class Solution{
public:
    vector<int> res; //result
    vector<int> index; //array of indexes
    vector<int> temp; //temporary array to store indexes
    vector<int> countSmaller(vector<int>& nums){
        res=vector<int>(nums.size(),0);
        index=vector<int>(nums.size());
        temp=vector<int>(nums.size());
        for(int i=0;i<nums.size();i++)index[i]=i;
        int mid=nums.size()/2;
        sort(nums,0,mid);
        sort(nums,mid+1,nums.size()-1);
        merge(nums,0,mid,mid+1,nums.size()-1);
        return res;
    }
    void sort(vector<int>& nums,int left, int right){
        if(left>=right)return;
        int mid=(left+right)/2;
        sort(nums,left,mid);
        sort(nums,mid+1,right);
        merge(nums,left,mid,mid+1,right);
    }
    void merge(vector<int>& nums,int left1, int right1,int left2,int right2){
        for(int i=left1;i<=right2;i++)temp[i]=index[i];
        int p1=left1,p2=left2;
        int k=left1; //point to the next location of number that will be insert
        while(k<=right2){
            if(p2>right2){
                //not all of left array been insert
                index[k]=temp[p1];
                res[index[k]]+=(p2-left2);
                p1++;
                k++;
            }
            else if(p1>right2){
                index[k]=temp[p2];
                p2++;
                k++;
            }
            else if(nums[temp[p1]]<=nums[temp[p2]]){
                index[k]=temp[p1];
                res[index[k]]+=(p2-left2); //number of (p2-left2) nums less nums[temp[p1]];
                p1++; //one number from left array is inserted into index[k]
                k++; //next location inserted
            }
            else{
                index[k]=temp[p2];
                p2++;
                k++;
            }
        }
    }
};


int main()
{
    vector<int> nums{5,2,6,1};
    Solution s;
    auto res=s.countSmaller(nums);
    return 0;
}