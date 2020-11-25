#include<iostream>
#include<vector>
#include<queue>
#include<string>
#include<algorithm>
using namespace std;

class Solution {
public:
    bool check_end(vector<string>& board){
        //检查是否结束
        //行/列检查
        for(int i=0;i<3;i++){
            if(board[i][0]==' ')continue;
            if(board[i][0]==board[i][1]&&board[i][1]==board[i][2])return true;
        }
        for(int i=0;i<3;i++){
            if(board[0][i]==' ')continue;
            if(board[0][i]==board[1][i]&&board[1][i]==board[2][i])return true;
        }
        //斜向检查
        if(board[1][1]==' ')return false;
        if(board[0][0]==board[1][1]&&board[1][1]==board[2][2])return true;
        if(board[2][0]==board[1][1]&&board[1][1]==board[0][2])return true;
        return false;
    }
    int check_num(vector<string>& board){
        //数目检查
        int num1=0,num2=0;
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                if(board[i][j]=='X')num1++;
                else if(board[i][j]=='O')num2++;
        return num1-num2;
    }
    bool validTicTacToe(vector<string>& board) {
        int num=check_num(board);
        if(num>1||num<0)return false;
        char ch=(num==0)? 'O':'X';
        bool flag=false;
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(board[i][j]==ch){
                    flag=true;
                    board[i][j]=' ';
                    if(dfs(board,ch=='X'? 'O':'X')){board[i][j]=ch;return true;}
                    board[i][j]=ch;
                }
            }
        }
        if(!flag)return true;
        return false;
    }
    bool dfs(vector<string>& board,char ch){
        if(check_end(board))return false;
        bool flag=false;
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(board[i][j]==ch){
                    flag=true;
                    board[i][j]=' ';
                    if(dfs(board,ch=='X'? 'O':'X')){board[i][j]=ch;return true;}
                    board[i][j]=ch;
                }
            }
        }
        if(!flag)return true;
        return false;
    }
};

int main(){
    return 0;
}