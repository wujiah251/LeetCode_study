#include<iostream>
#include<vector>
#include<cmath>
#include<map>
#include<set>
using namespace std;
//暴力方法，时间超时
class Solution {
public:
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        int res=0;
        for(int i=0;i<nums.size();i++){
            long sum=0;
            for(int j=i;j<nums.size();j++){
                sum+=nums[j];
                if(sum>=lower&&sum<=upper)res++;
            }
        }
        return res;
    }
};

//平衡树解法
//从左向右遍历，sum[i]存储从0-i的前缀和
//将前缀和存储在平衡树(nultiset，允许重复键值的红黑树)
//使用lower_bound和upper_bound来搜索边界值
//distance用来做差值

class Solution{
public:
    int countRangeSum(vector<int>& nums,int lower,int upper){
        int len=nums.size();
        long sum=0;
        int res=0;
        multiset<long> presum;
        presum.insert(0);
        for(int i=0;i<len;i++){
            sum+=nums[i];
            /*lower <= sum - presum <= upper
            presum>=sum-upper
            presum<=sum-lower
            */
            auto left=presum.lower_bound(sum-upper); //lower_bound(key)返回大于等于key的迭代器
            auto right=presum.upper_bound(sum-lower); //upper_bound(key)返回大于k的第一个元素
            //right-left就是个数
            for(;left!=right;left++,res++);
            //或者res+=distance(left,right);
            presum.insert(sum);
        }
        return res;
    }
};
//归并排序
class Solution{
public:
    int lower,upper;
    vector<long> sum;
    vector<long> temp;
    int countRangeSum(vector<int>& nums,int low,int up){
        lower=low;
        upper=up;
        if(nums.size()==0)return 0;
        int left=0,right=nums.size();
        sum=vector<long>(nums.size()+1);
        sum[0]=0;
        for(int i=1;i<sum.size();i++)sum[i]=sum[i-1]+nums[i-1];
        temp=vector<long>(nums.size()+1);;
        return mergesort(left,right);
    }
    int mergesort(int left,int right){
        if(left==right)return 0;
        int mid=(left+right)/2;
        int res=0;
        res+=mergesort(left,mid);
        res+=mergesort(mid+1,right);
        res+=merge(left,mid,right);
        return res;
    }
    int merge(int left,int mid,int right){
        for(int i=left;i<=right;i++)temp[i]=sum[i];
        int L=left,p1=mid+1,p2=mid+1;
        int res=0;
        while(L<=mid){
            // [L]-[p1-1],[L]-[p2]
            while(p1<=right&&sum[p1]-sum[L]<lower)p1++;
            while(p2<=right&&sum[p2]-sum[L]<=upper)p2++;
            res+=p2-p1;
            L++;
        }
        p1=left,p2=mid+1;
        for(int k=left;k<=right;k++){
            if(p1>mid){
                sum[k]=temp[p2++];
            }
            else if(p2>right){
                sum[k]=temp[p1++];
            }
            else if(temp[p1]<=temp[p2]){
                sum[k]=temp[p1++];
            }
            else{
                sum[k]=temp[p2++];
            }
        }
        return res;
    }
};


int main()
{
    vector<int> nums{-2,1,-1,4,-3,10,5,2,-1};
    int lower=-2,upper=2;
    Solution s;
    cout << s.countRangeSum(nums,lower,upper);
    return 0;
}