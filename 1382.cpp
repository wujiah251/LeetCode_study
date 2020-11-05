#include<iostream>
#include<vector>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

//思路：先顺序读取到数组在生成平衡二叉树
class Solution {
public:
    TreeNode* balanceBST(TreeNode* root) {
        if(!root)return nullptr;
        vector<int> res;
        dfs(root,res);
        return dfs(res,0,res.size()-1);        
    }
    void dfs(TreeNode* cur,vector<int>& res){
        if(cur->left)dfs(cur->left,res);
        res.push_back(cur->val);
        if(cur->right)dfs(cur->right,res);
    }
    TreeNode* dfs(vector<int>& res,int left,int right){
        if(left>right)return nullptr;
        int mid=(left+right)/2;
        TreeNode* node= new TreeNode(res[mid]);
        node->left=dfs(res,left,mid-1);
        node->right=dfs(res,mid+1,right);
        return node;
    }
};


int main()
{
    return 0;
}