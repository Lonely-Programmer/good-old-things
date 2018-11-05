#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <cstring>
#include <ctype.h>
using namespace std;

struct node
{
    int pts;
    int **dat;
    node *prev;
    node *next;
};

class zy2048
{
    enum winState {playing,lose,win,both};
    friend ostream &operator<<(ostream &os,const zy2048 &obj);

private:
    const int order;
    int **data;
    int score;
    int cnt;
    winState state;
    node *head;
    node *r;
    void zeroTop(int c);

public:
    zy2048(int n);
    ~zy2048();
    int maxNum() const;
    void rev();
    void trn();
    void upward();
    void downward();
    void leftward();
    void rightward();
    void appear();
    bool efficient();
    void winlose();
    void record();
    void undo();
    void play();
};

zy2048::zy2048(int n):order(n),score(0),cnt(0),state(playing),head(new node),r(head)
{
    int i,j;
    data=new int*[n];
    for(i=0;i<n;i++)
        data[i]=new int[n];
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            data[i][j]=0;

    srand(time(NULL));
    head->prev=NULL;
    record();
}

zy2048::~zy2048()
{
    int i;
    for(i=0;i<order;i++)
        delete [] data[i];
    delete [] data;
    node *p=head,*q=head;
    while(q)
    {
        q=q->next;
        delete p;
        p=q;
    }
}

int zy2048::maxNum() const
{
    int i,j;
    int max=0;
    for(i=0;i<order;i++)
        for(j=0;j<order;j++)
            max=data[i][j]>max ? data[i][j] : max;
    return max;
}

void zy2048::zeroTop(int c)
{
    int i,pos=0;
    int zeroNum=0;
    for(i=0;i<order;i++)
        if(data[c][i]==0)
            zeroNum++;
    for(i=0;i<order;i++)
        if(data[c][i]!=0)
        {
            data[c][pos]=data[c][i];
            pos++;
        }
    for(i=order-zeroNum;i<order;i++)
        data[c][i]=0;
}

void zy2048::rev()
{
    int i,j;
    int tmp;
    for(i=0;i<order;i++)
        for(j=0;j<order/2;j++)
        {
            tmp=data[i][j];
            data[i][j]=data[i][order-j-1];
            data[i][order-j-1]=tmp;
        }
}

void zy2048::trn()
{
    int i,j;
    int tmp;
    for(i=0;i<order;i++)
        for(j=i+1;j<order;j++)
        {
            tmp=data[i][j];
            data[i][j]=data[j][i];
            data[j][i]=tmp;
        }
}

void zy2048::upward()
{
    trn();
    leftward();
    trn();
}

void zy2048::downward()
{
    trn();
    rightward();
    trn();
}

void zy2048::leftward()
{
    int i,j;
    for(i=0;i<order;i++)
        for(j=0;j<order-1;j++)
        {
            zeroTop(i);
            if(data[i][j]==data[i][j+1])
            {
                data[i][j]=data[i][j]+data[i][j+1];
                data[i][j+1]=0;
                score+=data[i][j];
            }
        }
}

void zy2048::rightward()
{
    rev();
    leftward();
    rev();
}

void zy2048::appear()
{
    int appearNum;
    int x,y;
    appearNum=rand()%10==0 ? 4 : 2;
    do
    {
        x=rand()%order;
        y=rand()%order;
    }while(data[x][y]!=0);
    data[x][y]=appearNum;
}

void zy2048::winlose()
{
    int i,j;
    if(maxNum()>=2048)
        state=win;
    for(i=0;i<order;i++)
        for(j=0;j<order;j++)
            if(data[i][j]==0)
                return;
    for(i=0;i<order;i++)
        for(j=0;j<order-1;j++)
            if(data[i][j]==data[i][j+1] || data[j][i]==data[j+1][i])
                return;
    state=winState(state+lose);
}


bool zy2048::efficient()
{
    int i,j;
    for(i=0;i<order;i++)
        for(j=0;j<order;j++)
            if(r->dat[i][j]!=data[i][j])
                return true;
    return false;
}

void zy2048::record()
{
    int i,j;
    r->next=new node;
    r->next->prev=r;
    r=r->next;
    r->pts=score;
    r->dat=new int*[order];
    for(i=0;i<order;i++)
    {
        r->dat[i]=new int[order];
        for(j=0;j<order;j++)
            r->dat[i][j]=data[i][j];
    }
    r->next=NULL;
    cnt++;
}

void zy2048::undo()
{
    int i,j;
    node *p=r->prev;

    for(i=0;i<order;i++)
        delete []r->dat[i];
    delete r->dat;
    delete r;
    r=p;
    r->next=NULL;

    score=r->pts;
    for(i=0;i<order;i++)
        for(j=0;j<order;j++)
            data[i][j]=r->dat[i][j];
    cnt--;
}

ostream &operator<<(ostream &os,const zy2048 &obj)
{
    int i,j;
    int width=obj.maxNum()==0 ? 3 : log(obj.maxNum())/log(10)+3;
    for(i=0;i<obj.order;i++)
    {
        for(j=0;j<obj.order;j++)
            os<<left<<setw(width)<<obj.data[i][j]<<' ';
        os<<endl;
    }
    os<<"Your score: "<<obj.score<<endl;

    return os;
}
void zy2048::play()
{
    char dire[81];
    char d;
    appear();
    cnt=-1;

    while(true)
    {
        if(efficient())
        {
            appear();
            record();
        }
        winlose();
        cout<<endl<<"Step "<<cnt<<":"<<endl;
        cout<<*this<<endl<<endl;
        if(state==lose || state==both)
            break;
        cout<<"Please enter a direction(w/s/a/d) [Press z to undo, q to quit] :";
        cin.getline(dire,80,'\n');
        if(strlen(dire)>1)
        {
            cout<<"Wrong input!"<<endl;
            continue;
        }
        d=dire[0];

        switch(toupper(d))
        {
            case 'W': upward(); break;
            case 'S': downward(); break;
            case 'A': leftward(); break;
            case 'D': rightward(); break;
            case 'Z':
                if(r->prev!=head->next)
                    undo();
                else
                    cout<<"Cannot undo anymore!"<<endl;
                continue;
            case 'Q': break;
            default: cout<<"Wrong input!"<<endl; continue;
        }
        if(toupper(d)=='Q')
            break;

        if(!efficient())
            cout<<"This move is not efficient!"<<endl;
    }

    switch(state)
    {
        case lose: cout<<"You lose!"<<endl; break;
        case both: cout<<"You both win and lose!"<<endl;
    }
}

int main()
{
    zy2048 a(4);
    a.play();
    return 0;
}
