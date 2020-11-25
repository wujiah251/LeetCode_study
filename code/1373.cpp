#include<iostream>
#include<vector>
using namespace std;



struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};



//返回状态
//vector<int>(4)
//0-是否是一棵搜索树
//1-最小值
//2-最大值
//3-和
//注：如果递归要返回很多参数的情况下多考虑数组

class Solution {
public:
    int Result;
    int maxSumBST(TreeNode* root) {
        if(!root)return 0;
        Result=0;
        dfs(root);
        return Result;
    }
    vector<int> dfs(TreeNode* cur){
        vector<int> res(4);
        if(!cur->left&&!cur->right){
            res[0]=1;
            res[1]=res[2]=res[3]=cur->val;
            Result=max(res[3],Result);
            return res;
        }
        else if(!cur->left){
            auto R=dfs(cur->right);
            res[0]=(cur->val<R[1])&&R[0];
            res[1]=min(cur->val,R[1]);
            res[2]=max(cur->val,R[2]);
            res[3]=R[3]+cur->val;
            if(res[0])Result=max(res[3],Result);
            return res;
        }
        else if(!cur->right){
            auto L=dfs(cur->left);
            res[0]=(cur->val>L[2])&&L[0];
            res[1]=min(cur->val,L[1]);
            res[2]=max(cur->val,L[2]);
            res[3]=L[3]+cur->val;
            if(res[0])Result=max(res[3],Result);
            return res;
        }
        else{
            auto L=dfs(cur->left),R=dfs(cur->right);
            res[0]=L[0]&&R[0]&&(cur->val>L[2])&&(cur->val<R[1]);
            res[1]=min(cur->val,min(L[1],R[1]));
            res[2]=max(cur->val,max(L[2],R[2]));
            res[3]=L[3]+R[3]+cur->val;
            if(res[0])Result=max(res[3],Result);
            return res;
        }
    }
};

int main()
{
    return 0;
}