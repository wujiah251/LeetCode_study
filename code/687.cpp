#include<iostream>
#include<cmath>
using namespace std;


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
 
class Solution {
public:
    int ans;
    int longestUnivaluePath(TreeNode* root) {
        ans=0;
        dfs(root);
        return ans;
    }
    int dfs(TreeNode* cur){
        if(!cur)return 0;
        int left=dfs(cur->left);
        int right=dfs(cur->right);
        int Left=0,Right=0;
        if(cur->left&&cur->left->val==cur->val)Left=left+1;
        if(cur->right&&cur->right->val==cur->val)Right=right+1;
        ans=max(ans,Left+Right);
        return max(Left,Right);
    }
};

int main()
{
    return 0;
}