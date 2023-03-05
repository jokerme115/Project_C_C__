#include<iostream>
using namespace std;
int main(){
    char m;
    int a,b,c,d,i,j,q,p;
    a=b=c=d=i=j=q=p=0;
    int i1[100001];
    int i2[100001];
    while((m=getchar())!='E'){
        // 记录赛况
        if(m=='W'){
            a++;c++;
        }else if(m=='L'){
            b++;d++;
        }
        // 11分制记录单局比赛结构
        if((a>=11&&a-b>1)||(b>=11&&b-a>1)){
            i1[i++]=a;
            i1[i++]=b;
            a=b=0;
        }
        // 21分制记录单局比赛结果
        if((c>=21&&c-d>1)||(d>=21&&d-c>1)){
            i2[j++]=c;
            i2[j++]=d;
            c=d=0;
        }
    }
    // 输出11分制结果
    while(q<i) cout<<i1[q++]<<':'<<i1[q++]<<endl;
    cout<<a<<':'<<b<<endl;
    cout<<endl;
    // 输出21分制结果
    while(p<j) cout<<i2[p++]<<':'<<i2[p++]<<endl;
    cout<<c<<':'<<d<<endl;
    return 0;
}
