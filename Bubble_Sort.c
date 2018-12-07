#include <stdio.h>
#include <stdlib.h>
#define MaxSize 20
typedef int ElemType;

/*���ż�¼�Ĵ洢�ṹ*/
typedef struct SqList *PtrlSqList;
struct SqList{
	ElemType arr[MaxSize+1]; /*r[0]��Ϊ�ڱ�*/
	int length; /*˳���ĳ���*/ 
}; /*˳�������*/

/*��������*/
void Insert_Array(PtrlSqList P, int K); /*���в���Ԫ��*/
int GetListLength(PtrlSqList P); /*�������еĳ���*/
void PrintList(PtrlSqList P); /*�������*/
void Swap(PtrlSqList P, int i); /*Ԫ��i��i+1λ�û���*/
void Bubble_Sort(PtrlSqList P, int N); /*����ð������*/

int main(int argc, char const* argv[]) 
{
	int data;
	PtrlSqList P;
	P=(PtrlSqList)malloc(sizeof(struct SqList));
	P->arr[1]=-1;
	P->arr[0]=0;
	
	printf("�봴������:");
	do {
		scanf("%d", &data);
		Insert_Array(P, data);
	} while (data!=-1);
	
	P->length=GetListLength(P);
	//P.r[]={34, 8, 64, 51, 32, 31};
	Bubble_Sort(P, P->length);
	
	printf("\nð�������:");
	PrintList(P);
	
	return 0;
}

/*���в���Ԫ��*/
void Insert_Array(PtrlSqList P, int K)
{
	int i=1;
	while (P->arr[i]!=-1) {
		i++;
	}
	P->arr[i]=K;
	P->arr[i+1]=-1;
}

/*�������еĳ���*/
int GetListLength(PtrlSqList P) 
{
	int count=0;
	int i=1;
	
	while (P->arr[i]!=-1) {
		count++;
		i++;
	}

	return count;
}

/*�������*/
void PrintList(PtrlSqList P) 
{
	int i=1; 
	while (P->arr[i]!=-1) {
		printf("%d\t", P->arr[i]);
		i++;
	}
} 

/*Ԫ��i��i+1λ�û���*/
void Swap(PtrlSqList P, int j) 
{
	ElemType Temp;
	Temp=P->arr[j];
	P->arr[j]=P->arr[j+1];
	P->arr[j+1]=Temp; 
}

/*����ð������*/
void Bubble_Sort (PtrlSqList P, int N)  
{
	/*P�Ǵ�������,N��Ҫ����ĸ���*/
	int i,j,flag;
	flag=0; /*flag����Ƿ���ִ��Swap����*/
	
	for (i=N; i>0; i--) {
		flag=0; /*ÿ����һ������,flag����Ϊ0*/
		for (j=1; j<i; j++) {
			if (P->arr[j]>P->arr[j+1]) {
				Swap(P, j);
				flag=1;
			}
		}
		/*�������һ������,ȫ���޽���,֤�����������*/
		if (flag==0) {
			break; /*������ʣ�µ�ѭ��*/
		}
	}
}
