#include<string>
using namespace std;


//双指针法
class Solution {
public:
    void swap(char& a,char& b){
        char temp=a;
        a=b;
        b=temp;
    }
    bool canTransform(string start, string end) {
        int p1=0,p2=0;
        if(start.size()!=end.size())return false;
        int len=start.size();
        while(p1<len&&p2<len){
            while(p1<len&&start[p1]=='X')p1++;
            while(p2<len&&end[p2]=='X')p2++;
            if(p1>=len||p2>=len)continue;
            if(start[p1]!=end[p2]||(start[p1]=='L'&&p1<p2)||(start[p1]=='R'&&p1>p2))return false;
            else{p1++;p2++;}
        }
        while(p1<len&&start[p1]=='X')p1++;
        while(p2<len&&end[p2]=='X')p2++;
        return p1==p2;
    }
};

int main()
{
    string a("RXXLRXRXL"),b("XRLXXRRLX");
    Solution s;
    s.canTransform(a,b);
    return 0;
}