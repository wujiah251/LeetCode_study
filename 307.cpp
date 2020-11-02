#include<iostream>
#include<vector>
#include<cmath>
using namespace std;


//动态规划解法
class NumArray{
public:
    vector<int> dp;
    NumArray(vector<int>& nums){
        dp=vector<int>(nums.size()+1,0);
        for(int i=0;i<nums.size();i++){
            dp[i+1]=dp[i]+nums[i];
        }
    }
    void update(int i,int val) {
        int diff=val-(dp[i+1]-dp[i]);
        for(int j=i+1;j<dp.size();j++)dp[j]+=diff;
    }
    int sumRange(int i, int j) {
        return dp[j+1]-dp[i];
    }
};


//线段树解法
class NumArray{
public:
    struct node{
        int left;
        int right;
        int sum;
        node(int l,int r,int s):left(l),right(r),sum(s){}
    };
    vector<node*> nodes;
    int H;
    int len;
    int init(int index,int left,int right,vector<int>& nums){
        if(left==right){
            nodes[index]=new node(left,right,nums[left]);
            return nums[left];
        }
        else{
            nodes[index]=new node(left,right,0);
            nodes[index]->sum+=init(index*2+1,left,(left+right)/2,nums);
            nodes[index]->sum+=init(index*2+2,(left+right)/2+1,right,nums);
            return nodes[index]->sum;
        }
    }
    NumArray(vector<int>& nums){
        len=nums.size();
        if(len==0){return;}
        if(len==1)H=len;
        else H=log2(len-1)+2;
        nodes=vector<node*>(pow(2,H)-1);
        init(0,0,len-1,nums);
    }
    void update(int i,int val) {
        if(i>=len||i<0)return;
        int index=0;
        int mid;
        while(nodes[index]->left<nodes[index]->right){
            mid=(nodes[index]->right+nodes[index]->left)/2;
            if(i<=mid){
                index=index*2+1;
            }
            else{
                index=index*2+2;
            }
        }
        int diff=val-nodes[index]->sum;
        while(index){
            nodes[index]->sum+=diff;
            index=(index-1)/2;
        }
        //更正根结点
        nodes[index]->sum+=diff;
    }
    int sum(int i,int j,int index){
        if(i==nodes[index]->left&&j==nodes[index]->right)return nodes[index]->sum;
        int mid=(nodes[index]->left+nodes[index]->right)/2;
        if(j<=mid){
            return sum(i,j,index*2+1);
        }
        if(i>mid){
            return sum(i,j,index*2+2);
        }
        return sum(i,mid,index*2+1)+sum(mid+1,j,index*2+2);
    }
    int sumRange(int i, int j) {
        if(len==0)return 0;
        return sum(i,j,0);
    }
};

//sqrt分解
class NumArray{
public:
    vector<int> num;
    vector<int> sqrt_sum;
    int len;
    int len_nums; //和数组中和有多少个数组组成
    int len_sum;//和数组长度
    // 0-len_nums-1;len_nums-len_nums*2-1......
    //后面有部分没有被记录在sqrt_sum里面，从len_sum*len_nums->len-1
    NumArray(vector<int>& nums):num(nums){
        len=nums.size();
        if(len==0)return;
        len_nums=sqrt(len);
        len_sum=len/len_nums;
        sqrt_sum=vector<int>(len_sum,0);
        for(int i=0;i<len_sum;i++){
            for(int j=0;j<len_nums;j++){
                sqrt_sum[i]+=num[i*len_nums+j];
            }
        }
    }
    void update(int i,int val) {
        if(i>=len||i<0)return;
        int diff=val-num[i];
        num[i]=val;
        if(i<len_sum*len_nums){
            sqrt_sum[i/len_nums]+=diff;
        }
    }
    int sumRange(int i, int j) {
        int l=i/len_nums,r=j/len_nums;
        if(l==r||l+1==r){
            int sum=0;
            for(int k=i;k<=j;k++)sum+=num[k];
            return sum;
        }
        else{
            int sum=0;
            for(int k=l+1;k<r;k++)sum+=sqrt_sum[k];
            for(int k=i;k<(l+1)*len_nums;k++)sum+=num[k];
            for(int k=j;k>=r*len_nums;k--)sum+=num[k];
            return sum;
        }
    }
};
int main()
{
    vector<int> nums{7,2,7,2,0};
    NumArray obj(nums);
    obj.update(4,6);
    obj.update(0,2);
    obj.update(0,9);
    obj.update(3,8);
    cout << obj.sumRange(0,4);
    return 0;
}

