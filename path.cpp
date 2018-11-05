#include <iostream>
#include <cstdio>
#include <queue>
#include <stack>
#include <windows.h>
using namespace std;

struct Point
{
    int x;
    int y;
    int step;
    Point() {}
    Point(int a,int b,int c) {x=a; y=b; step=c;}
};
int main()
{
    int i,j;
    int n,m;
    int x1,y1,x2,y2;
    int ans;
    int nxt[4][2]={{0,1},{1,0},{0,-1},{-1,0}};
    char **a;
    bool **flag;
    Point **pre;
    Point tmp;
    queue<Point> z;
    stack<Point> path;

    cin>>n>>m;
    cin>>x1>>y1>>x2>>y2;
    a=new char*[n+1];
    flag=new bool*[n+1];
    pre=new Point*[n+1];
    for(i=0;i<=n;i++)
    {
        a[i]=new char[m+1];
        flag[i]=new bool[m+1];
        pre[i]=new Point[m+1];
    }
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=m;j++)
        {
            cin>>a[i][j];
            flag[i][j]=false;
        }
    }
    flag[x1][y1]=true;
    z.push(Point(x1,y1,0));
    pre[x1][y1]=Point(x1,y1,0);
    if(x1==x2 && y1==y2)
        ans=0;

    if(a[x1][y1]=='x')
    {
        for(i=1;i<=n;i++)
        {
            for(j=1;j<=m;j++)
            {
                if(flag[i][j])
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_BLUE);
                else
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
                if(i==x1 && j==y1)
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN);
                else if(i==x2 && j==y2)
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_BLUE);
                cout<<a[i][j]<<' ';
            }
            cout<<endl;
        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN);
        cout<<endl<<"Unreachable!"<<endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);

        for(i=0;i<=n;i++)
        {
            delete[] a[i];
            delete[] flag[i];
            delete[] pre[i];
        }
        delete []a;
        delete []flag;
        delete []pre;
        return 0;
    }

    while(!z.empty())
    {
        int tmpx,tmpy;
        tmp=z.front();
        for(i=0;i<4;i++)
        {
            tmpx=tmp.x+nxt[i][0];
            tmpy=tmp.y+nxt[i][1];
            if(tmpx<=0 || tmpy<=0 || tmpx>n || tmpy>m) continue;
            if(a[tmpx][tmpy]=='x') continue;
            if(!flag[tmpx][tmpy])
            {
                flag[tmpx][tmpy]=true;
                pre[tmpx][tmpy]=Point(tmp.x,tmp.y,tmp.step+1);
                if(tmpx==x2 && tmpy==y2)
                {
                    ans=tmp.step+1;
                    break;
                }
                z.push(Point(tmpx,tmpy,tmp.step+1));
            }
        }
        if(flag[x2][y2]) break;
        z.pop();
    }
    if(flag[x2][y2])
    {
        for(i=1;i<=n;i++)
            for(j=1;j<=m;j++)
                flag[i][j]=false;

        path.push(Point(x2,y2,ans+1));
        while(path.top().step>1)
        {
            tmp=path.top();
            path.push(pre[tmp.x][tmp.y]);
            flag[tmp.x][tmp.y]=true;
        }
        flag[x1][y1]=true;
        for(i=1;i<=n;i++)
        {
            for(j=1;j<=m;j++)
            {
                if(flag[i][j])
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_BLUE);
                else
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
                if(i==x1 && j==y1)
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN);
                else if(i==x2 && j==y2)
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_BLUE);
                cout<<a[i][j]<<' ';
            }
            cout<<endl;
        }

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN);
        cout<<endl<<ans<<" step(s):"<<endl<<endl;
        while(!path.empty())
        {
            tmp=path.top();
            cout<<"Step "<<tmp.step-1<<" -> "<<'('<<tmp.x<<','<<tmp.y<<')'<<endl;
            path.pop();
        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
    }
    else
    {
        for(i=1;i<=n;i++)
        {
            for(j=1;j<=m;j++)
            {
                if(flag[i][j])
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_BLUE);
                else
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
                if(i==x1 && j==y1)
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN);
                else if(i==x2 && j==y2)
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN|FOREGROUND_BLUE);
                cout<<a[i][j]<<' ';
            }
            cout<<endl;
        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN);
        cout<<endl<<"Unreachable!"<<endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
    }
    for(i=0;i<=n;i++)
    {
        delete[] a[i];
        delete[] flag[i];
        delete[] pre[i];
    }
    delete []a;
    delete []flag;
    delete []pre;

    return 0;
}
