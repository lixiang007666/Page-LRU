#include "stdio.h"
#include "math.h"
#include"malloc.h"
#include "stdlib.h"
#include <iostream>
#include "math.h"
#define OK 1
#define ERROR -1
#define Max 5
using namespace std;
typedef int status;
typedef int SElemType;
int k=0;//记录缺页次数
/*--------------------栈及其操作---------------------*/
typedef struct {
    SElemType  *base; //栈底指针   
    SElemType   *top;  //栈顶指针
    int  count;    //栈的大小
}SqStack;

//构造空栈
status InitStack (SqStack &S){   
	S.base=(SElemType *)malloc(Max * sizeof(SElemType));
	if (!S.base)   return(OVERFLOW); 
	S.count = 0;
	S.top = S.base;
	return(OK);
}

//入栈
status Push(SqStack &s,SElemType e)
{
	*s.top++=e;
	s.count++;
//	cout<<"插入"<<e<<endl;
	return OK;
}

//销毁栈
status DestroyStack(SqStack &S)
{
	
	S.top=NULL;
	S.base=NULL;
	delete[] S.base;
    S.count=0;
	return OK;
}

//判断栈是否为空
bool EmptyStack(SqStack s)
{
	if(s.count==0) return true;
	else          return false;
}
//是否已满
bool full(SqStack s)
{
	if(s.count==5) return true;
	return false;
}
//判断是否已经存在
int equeal(SqStack s,SElemType e)
{
	int num=s.count;
	if(EmptyStack(s)) return -1;
	for (int i=1;i<=num;i++)
	{
		if(*(s.top-i)==e)
			return i;
	}
	return -1;
}
//输出
void print(SqStack s){
	int a,i,num=s.count;
	//cout<<"有"<<num<<"个数"<<endl;
	for (i=0;i<num;i++)
	{
		a=*(s.base+i);
		cout<<a<<" ";
	}
	cout<<endl;
}
/*----------------页表---------------------*/
int pageLen=15;//页面数
int l=1024;  //页面大小
struct page{
	int pageNum;
	int memNum;
}p[15];
int initiate(){
	int i,j;
	for (i=0;i<pageLen;i++)
	{   
		j=rand()%11;
		p[i].pageNum=i;
		p[i].memNum=i+j;
	}
	return 1;
}
int locate(int n){
	for (int i=0;i<pageLen;i++)
	{
		if (p[i].pageNum==n)
		{
			return p[i].memNum;
		}
	}
	return -1;
}

//LRU置换算法
int count=0;//记录访问次数
int lru(SqStack &s,SElemType e)
{
	int i;
	int num=equeal(s,e);
	count++;
	cout<<"第"<<count<<"次访问页面"<<e;
	if (!full(s))
	{
		if (num==-1){
			cout<<"，不存在此页号,"<<e<<"入栈"<<endl;
			k++;
			Push(s,e);
		}
		else{
			cout<<"，已经存在，"<<e<<"置为栈顶"<<endl;
			for(i=num;i>1;i--){
				*(s.top-i)=*(s.top-i+1);
			}
			*(s.top-1)=e;
		}
	} 
	else
	{
		if(num==-1){
			k++;
			cout<<"，此页号不存在且栈满，栈底元素被换出，"<<e<<"为栈顶"<<endl;
			for(i=Max;i>1;i--)
				*(s.top-i)=*(s.top-i+1);
			*(s.top-1)=e;
		}
		else{
			cout<<"，页号存在且栈满"<<e<<"换为栈顶"<<endl;
			for(i=num;i>1;i--){
				*(s.top-i)=*(s.top-i+1);
			}
			*(s.top-1)=e;
		}
	}
	return 1;
}
//执行lru算法
int begin(){
	int i,n,m;
	SElemType a[100];
	SqStack s;
	InitStack(s);
	cout<<"请输入页面数：";
	cin>>n;
	if (n>100){
		cout<<"输入的数值太大！！"<<endl;
		return 0;
	}
	cout<<"请输入页面号序列(0~~9)："<<endl;
	for(i=0;i<n;i++){
		cin>>m;
		if(m<0||m>9){
			cout<<"输入错误，请重新输入！！"<<endl;
			i--;
			continue;
		}
		a[i]=m;
	}
	for (i=0;i<n;i++)
	{
		lru(s,a[i]);
		cout<<"结果为：";
		print(s);
	}
	DestroyStack(s);
	cout<<"一共缺页"<<k<<"次"<<endl;
    return 1;
}
int main(){
	int ok=0;
	initiate();
	while (ok!=3)
	{
		cout<<"                       **********菜单***********"<<endl;
		cout<<"                             1--执行lru算法"<<endl;
		cout<<"                             2--退出        "<<endl;
		cout<<"                       *************************"<<endl;
		cout<<"请输入菜单号：";
		cin>>ok;
		switch (ok)
		{
		case 1: begin(); break;
		default: break;
		}
	}
	return 1;
}
