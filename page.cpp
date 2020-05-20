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
int k=0;//��¼ȱҳ����
/*--------------------ջ�������---------------------*/
typedef struct {
    SElemType  *base; //ջ��ָ��   
    SElemType   *top;  //ջ��ָ��
    int  count;    //ջ�Ĵ�С
}SqStack;

//�����ջ
status InitStack (SqStack &S){   
	S.base=(SElemType *)malloc(Max * sizeof(SElemType));
	if (!S.base)   return(OVERFLOW); 
	S.count = 0;
	S.top = S.base;
	return(OK);
}

//��ջ
status Push(SqStack &s,SElemType e)
{
	*s.top++=e;
	s.count++;
//	cout<<"����"<<e<<endl;
	return OK;
}

//����ջ
status DestroyStack(SqStack &S)
{
	
	S.top=NULL;
	S.base=NULL;
	delete[] S.base;
    S.count=0;
	return OK;
}

//�ж�ջ�Ƿ�Ϊ��
bool EmptyStack(SqStack s)
{
	if(s.count==0) return true;
	else          return false;
}
//�Ƿ�����
bool full(SqStack s)
{
	if(s.count==5) return true;
	return false;
}
//�ж��Ƿ��Ѿ�����
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
//���
void print(SqStack s){
	int a,i,num=s.count;
	//cout<<"��"<<num<<"����"<<endl;
	for (i=0;i<num;i++)
	{
		a=*(s.base+i);
		cout<<a<<" ";
	}
	cout<<endl;
}
/*----------------ҳ��---------------------*/
int pageLen=15;//ҳ����
int l=1024;  //ҳ���С
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

//LRU�û��㷨
int count=0;//��¼���ʴ���
int lru(SqStack &s,SElemType e)
{
	int i;
	int num=equeal(s,e);
	count++;
	cout<<"��"<<count<<"�η���ҳ��"<<e;
	if (!full(s))
	{
		if (num==-1){
			cout<<"�������ڴ�ҳ��,"<<e<<"��ջ"<<endl;
			k++;
			Push(s,e);
		}
		else{
			cout<<"���Ѿ����ڣ�"<<e<<"��Ϊջ��"<<endl;
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
			cout<<"����ҳ�Ų�������ջ����ջ��Ԫ�ر�������"<<e<<"Ϊջ��"<<endl;
			for(i=Max;i>1;i--)
				*(s.top-i)=*(s.top-i+1);
			*(s.top-1)=e;
		}
		else{
			cout<<"��ҳ�Ŵ�����ջ��"<<e<<"��Ϊջ��"<<endl;
			for(i=num;i>1;i--){
				*(s.top-i)=*(s.top-i+1);
			}
			*(s.top-1)=e;
		}
	}
	return 1;
}
//ִ��lru�㷨
int begin(){
	int i,n,m;
	SElemType a[100];
	SqStack s;
	InitStack(s);
	cout<<"������ҳ������";
	cin>>n;
	if (n>100){
		cout<<"�������ֵ̫�󣡣�"<<endl;
		return 0;
	}
	cout<<"������ҳ�������(0~~9)��"<<endl;
	for(i=0;i<n;i++){
		cin>>m;
		if(m<0||m>9){
			cout<<"����������������룡��"<<endl;
			i--;
			continue;
		}
		a[i]=m;
	}
	for (i=0;i<n;i++)
	{
		lru(s,a[i]);
		cout<<"���Ϊ��";
		print(s);
	}
	DestroyStack(s);
	cout<<"һ��ȱҳ"<<k<<"��"<<endl;
    return 1;
}
int main(){
	int ok=0;
	initiate();
	while (ok!=3)
	{
		cout<<"                       **********�˵�***********"<<endl;
		cout<<"                             1--ִ��lru�㷨"<<endl;
		cout<<"                             2--�˳�        "<<endl;
		cout<<"                       *************************"<<endl;
		cout<<"������˵��ţ�";
		cin>>ok;
		switch (ok)
		{
		case 1: begin(); break;
		default: break;
		}
	}
	return 1;
}
