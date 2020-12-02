#include<iostream>
#include<vector>
#include<queue>

using namespace std;

class Solution {
public:
    vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
        vector<int> res(k,-1);
        vector<int> temp(k);
        vector<int> v1(k);
        vector<int> v2(k);
        int n1,n2;
        for(n1=0;n1<=k&&n1<=nums1.size();n1++){
            n2=k-n1;
            if(n2<=nums2.size()){
                get_max(nums1,n1,v1);
                get_max(nums2,n2,v2);
                merge(v1,v2,n1,n2,temp,k);
                if(greater(temp,res)){
                    res=temp;
                }

            }
        }
        return res;
    }
    void get_max(vector<int>&nums,int n,vector<int>& v){
        if(n==0)return;
        deque<int> q;
        for(int i=0;i<nums.size()-n;i++){
            while(!q.empty()&&q.back()<nums[i])q.pop_back();
            q.push_back(nums[i]);
        }
        int index=0;
        for(int i=nums.size()-n;i<nums.size();i++){
            while(!q.empty()&&q.back()<nums[i]){
                q.pop_back();
            }
            q.push_back(nums[i]);
            v[index++]=q.front();
            q.pop_front();
        }
    }
    void merge(vector<int>& v1,vector<int>& v2,int n1,int n2,vector<int>& temp,int k){
        int p1=0,p2=0;
        for(int i=0;i<k;i++){
            if(p1==n1){
                temp[i]=v2[p2++];
            }
            else if(p2==n2){
                temp[i]=v1[p1++];
            }
            else if(v1[p1]>v2[p2]){
                temp[i]=v1[p1++];
            }
            else if(v1[p1]<v2[p2]){
                temp[i]=v2[p2++];
            }
            else{
                int p1_=p1+1,p2_=p2+1;
                temp[i]=v1[p1];
                while(p1_<n1&&p2_<n2&&v1[p1_]==v2[p2_]){
                    p1_++;p2_++;
                }
                if(p1_==n1){
                    p2++;
                }
                else if(p2_==n2){
                    p1++;
                }
                else if(v1[p1_]>v2[p2_]){
                    p1++;
                }
                else{
                    p2++;
                }
            }
        }
    }
    bool greater(vector<int>& a,vector<int>& b){
        for(int i=0;i<a.size();i++){
            if(a[i]>b[i])return true;
            else if(a[i]<b[i])return false;
        }
        return false;
    }
};


int main()
{
    Solution s;
    vector<int> nums1{2,5,6,4,4,0};
    vector<int> nums2{7,3,8,0,6,5,7,6,2};
    int k=15;
    s.maxNumber(nums1,nums2,k);
    return 0;
}