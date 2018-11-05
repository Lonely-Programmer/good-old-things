#include <iostream>
#include <cstring>
#include <cmath>
#include <windows.h>
using namespace std;
class seqStack
{
private:
    double *data;
    int maxSize;
    int top_p;

    void doubleSpace();
public:
    seqStack(int size=20) {maxSize=size; top_p=-1; data=new double[maxSize];}
    ~seqStack() {delete data;}
    bool isEmpty() {return top_p==-1;}
    void push(double x);
    double pop() {return data[top_p--];}
    double top() {return data[top_p];}
};

void seqStack::doubleSpace()
{
    int i;
    double *tmp=data;
    data=new double[maxSize*2];
    for(i=0;i<maxSize;i++)
        data[i]=tmp[i];
    maxSize*=2;
    delete tmp;
}

void seqStack::push(double x)
{
    if(top_p==maxSize-1) doubleSpace();
    data[++top_p]=x;
}
class calc
{
private:
    char exp[100];
    double ans;
    int legal;

    bool isOneOper(int pos);
    bool getNext(int &pos,char &type,double &num);
    void get2Num(seqStack &obj,double &num1,double &num2);
    double binResult(char op,double num1,double num2);
public:
    calc(char *s) {strcpy(exp,s); legal=0;}
    double result();
    int getError() {return legal;}
};

bool calc::isOneOper(int pos)
{
    pos--;
    while(pos>=0 && exp[pos]==' ')
        pos--;
    if(pos==-1) return true;
    if(exp[pos]==')' || (exp[pos]>='0' && exp[pos]<='9')) return false;
    return true;
}
bool calc::getNext(int &pos,char &type,double &num)
{
    while(exp[pos]==' ')
        pos++;

    if(exp[pos]=='\0') return false;
    if((exp[pos]>='0' && exp[pos]<='9') || exp[pos]=='.')
    {
        type='n';
        num=0;
        while(exp[pos]>='0' && exp[pos]<='9')
        {
            num*=10;
            num+=(exp[pos]-'0');
            pos++;
        }
        if(exp[pos]=='.')
        {
            pos++;
            double factor=1;
            while(exp[pos]>='0' && exp[pos]<='9')
            {
                factor/=10;
                num+=(exp[pos]-'0')*factor;
                pos++;
            }
        }
        return true;
    }
    else
    {
        type='o';
        num=exp[pos];
        if(num==':') {legal=1; return false;}
        if(num=='-' && isOneOper(pos)) num=':';
        pos++;
        return true;
    }
}

void calc::get2Num(seqStack &obj,double &num1,double &num2)
{
    if(obj.isEmpty())
    {
        legal=1;
        return;
    }
    num2=obj.pop();
    if(obj.isEmpty())
    {
        legal=1;
        return;
    }
    num1=obj.pop();
}
double calc::binResult(char op,double num1,double num2)
{
    if(op=='+') return num1+num2;
    if(op=='-') return num1-num2;
    if(op=='*') return num1*num2;
    if(op=='/' && num2!=0) return num1/num2;
    if(op=='/' && num2==0) {legal=2; return 0;}
    if(op=='^' && num1==0 && num2<=0) {legal=2; return 0;}
    if(op=='^') return pow(num1,num2);

    legal=1;
    return 0;
}
double calc::result()
{
    int pos=0;
    double num;
    double num1,num2;
    char op;
    seqStack numS,operS;

    while(getNext(pos,op,num))
    {
        if(op=='n')
            numS.push(num);
        else
        {
            op=num;
            if(op=='(')
                operS.push(op);
            else if(op==')')
            {
                while(!operS.isEmpty())
                {
                    op=operS.pop();
                    if(op=='(') break;
                    if(op==':')
                    {
                        if(numS.isEmpty())
                        {
                            legal=1;
                            break;
                        }
                        numS.push(-numS.pop());
                        continue;
                    }
                    get2Num(numS,num1,num2);
                    numS.push(binResult(op,num1,num2));
                }
                if(op!='(') legal=1;
            }
            else if(op=='+' || op=='-')
            {
                while(!operS.isEmpty() && operS.top()!='(')
                {
                    op=operS.pop();
                    if(op==':')
                    {
                        if(numS.isEmpty())
                        {
                            legal=1;
                            break;
                        }
                        numS.push(-numS.pop());
                        continue;
                    }
                    get2Num(numS,num1,num2);
                    numS.push(binResult(op,num1,num2));
                }
                operS.push(num);
            }
            else if(op=='*' || op=='/')
            {
                while(!operS.isEmpty())
                {
                    op=operS.top();
                    if(op=='(' || op=='+' || op=='-') break;
                    operS.pop();
                    if(op==':')
                    {
                        if(numS.isEmpty())
                        {
                            legal=1;
                            break;
                        }
                        numS.push(-numS.pop());
                        continue;
                    }
                    get2Num(numS,num1,num2);
                    numS.push(binResult(op,num1,num2));
                }
                operS.push(num);
            }
            else if(op==':')
            {
                operS.push(op);
            }
            else if(op=='^')
            {
                operS.push(op);
            }
        }
        if(legal==1)
            return 0;
        else if(legal==2)
            return 0;
    }

    while(!operS.isEmpty())
    {
        op=operS.top();
        if(op=='(')
        {
            operS.pop();
            continue;
            //legal=1;
            //break;
        }
        if(op==':')
        {
            operS.pop();
            if(numS.isEmpty())
            {
                legal=1;
                break;
            }
            numS.push(-numS.pop());
            continue;
        }
        op=operS.pop();
        get2Num(numS,num1,num2);
        numS.push(binResult(op,num1,num2));
    }
    ans=numS.pop();
    if(!numS.isEmpty()) legal=1;

    if(legal==1)
        return 0;
    else if(legal==2)
        return 0;
    return ans;
}

int main()
{
    char tmp[101];
    while(true)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY);
        cout<<"Please input an expression: ";

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN);
        cin.getline(tmp,100,'\n');
        calc a(tmp); //(5+6*(7+3)/3)/4+5
        double ans=a.result();
        int legal=a.getError();

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY);
        cout<<">>>The result is: ";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_BLUE);
        if(legal==0)
            cout<<ans<<endl;
        else if(legal==1)
            cout<<"Syntax ERROR!"<<endl;
        else if(legal==2)
            cout<<"Math ERROR!"<<endl;
        cout<<endl;
    }

    return 0;
}
