#include<iostream>
#include<vector>
#include<cmath>
#include<map>
#include<set>
using namespace std;


//暴力解
class Solution {
public:
    vector<int> countSmaller(vector<int>& nums){
        vector<int> res(nums.size(),0);
        for(int i=0;i<nums.size();i++){
            for(int j=nums.size()-1;j>i;j--)
                if(nums[j]<nums[i])res[i]++;
        }
        return res;
    }
};

//归并排序法
//升序
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

//线段树方法
class Solution {
public:
    struct node{
        int left;
        int right;
        int count;
        node(int l,int r,int c):left(l),right(r),count(c){}
    }; //区间[left,right]的数目
    vector<node*> tree;
    vector<int> countSmaller(vector<int>& nums) {
        if(!nums.size())return {};
        set<int> set;//用于离散化
        for(int i:nums)set.insert(i);
        map<int,int> map;//num->num;
        int index=0;
        for(auto item:set){
            map[item]=index++;
        }
        int H=(index==1)? 1:log2(index-1)+2;
        int left=0,right=index-1;
        tree = vector<node*>(pow(2,H)-1,nullptr);
        vector<int> res(nums.size());
        init(0,left,right);
        for(int i=nums.size()-1;i>=0;i--){
            res[i]=count(0,left,right,map[nums[i]]-1);
            insert(0,left,right,map[nums[i]]);
        }
        return res;
    }
    void init(int index,int left,int right){
        tree[index]=new node(left,right,0);
        if(left<right){
            int mid=(left+right)/2;
            init(index*2+1,left,mid);
            init(index*2+2,mid+1,right);
        }
    }
    void insert(int index,int left,int right,int num){
        tree[index]->count++;
        if(left==right)return;
        int mid=(left+right)/2;
        if(num<=mid)insert(index*2+1,left,mid,num);
        else insert(index*2+2,mid+1,right,num);
    }
    int count(int index,int left,int right,int num){
        if(num<left)return 0;
        if(num==right)return tree[index]->count;
        else{
            int mid=(left+right)/2;
            if(num<=mid)return count(index*2+1,left,mid,num);
            else{
                return count(index*2+1,left,mid,mid)+count(index*2+2,mid+1,right,num);
            }
        }
    }
};

//二叉搜索树方法
//用二叉树保存右边的数，每个结点保存了数值-val和计数器-每个结点左子树（左子树所有结点val小于等于当前结点val）规模
class Solution{
public:
    struct node{
        node* left;
        node* right;
        int val;
        int count;
        node(int val,int count):val(val),count(count),left(nullptr),right(nullptr){}
    };
    node* root;
    vector<int> countSmaller(vector<int>& nums){
        if(nums.size()==0)return {};
        int len=nums.size();
        vector<int> res(len);
        for(int i=len-1;i>=0;i--){
            root=insertAndcount(root,nums[i],res,i);
        }
        return res;
    }
    node* insertAndcount(node* cur,int num,vector<int>& res,int i){
        if(!cur){
            return new node(num,0);
        }
        if(cur->val>=num){
            cur->count++;
            cur->left=insertAndcount(cur->left,num,res,i);
        }
        else{
            res[i]+=1+cur->count;
            cur->right=insertAndcount(cur->right,num,res,i);    
        }
        return cur;
    }
};

//树状数组不会。。。。
//下次再写

int main()
{
    vector<int> nums{5,2,6,1};
    Solution s;
    auto res=s.countSmaller(nums);
    return 0;
}