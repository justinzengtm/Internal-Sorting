#include <stdio.h>
#include <stdlib.h>
#define MaxSize 20
typedef int ElemType;

/*�������еĴ洢�ṹ*/
typedef struct SqList *PtrlSqList;
struct SqList {
	ElemType arr[MaxSize+1];
	int length;
};

/*��������*/
void Insert_Array(PtrlSqList P, int K); /*���в���Ԫ��*/
void PrintList(PtrlSqList P); /*�������*/
int GetLength(PtrlSqList P); /*������еĳ���*/
void Binary_Sort(PtrlSqList P, int length); /*�۰��������*/ 

int main(int argc, char const* argv[]) 
{
	int data=0;
	PtrlSqList P;
	P=(PtrlSqList)malloc(sizeof(struct SqList));
	P->arr[0]=0; /*�����0λ����Ϊ�ڱ�*/
	P->arr[1]=-1;
	
	printf("\n�봴������:");
	while (data!=-1) {
		scanf("%d", &data); 
		Insert_Array(P, data);
	}
	
	printf("\nԭ����Ϊ:");
	PrintList(P);
	/*������еĳ���*/
	P->length=GetLength(P);
	printf("\n���г���Ϊ:%d\n", P->length);
	printf("\n���ֲ����������:"); 
	/*ֱ�Ӳ�������*/
	Binary_Sort(P, P->length);
	printf("\n���ֲ��������:");
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
	
	return;
}

/*�������*/
void PrintList(PtrlSqList P) 
{
	int i=1;
	while (P->arr[i]!=-1) {
		printf("%d  ", P->arr[i]);
		i++;
	}
	
	return;
}

/*������г���*/
int GetLength(PtrlSqList P) 
{
	int i=1;
	while (P->arr[i]!=-1) {
		i++;
	}
	
	return (i-1);
}

/*���ֲ�������2*/
void Binary_Sort(PtrlSqList P, int length) 
{
	int front, rear;
	int i, j, Tmp, m;
	
	for (i=2; i<=length; i++) {
		P->arr[0]=P->arr[i];
		front=1;
		rear=i-1; /*��ΪҪ�����ź�����������������,����rear=i-1��ʼ*/ 
		/*���ֲ����ҳ����ź�������Ԫ��*/
		while (front<=rear) {
			m=(front+rear)/2;
			if (P->arr[m]>P->arr[0]) {
				/*֤���������ǰ�벿��*/
				rear=m-1;
			} else {
				/*���������ں�벿��*/ 
				front=m+1;
			}
		}
		printf("\nfront=%d, rear=%d, m=%d\n", front, rear, m);
		/*�ҵ�����*/
		/*front����λ�õ����,i�����ź����е��յ�*/ 
		/*�����ź������в���λ��fonrt��֮���Ԫ������Ų*/
		for (j=i; j>0 && j>=front; j--) {
			P->arr[j]=P->arr[j-1]; /*����Ųһλ*/
		}
		P->arr[front]=P->arr[0];
		PrintList(P);
		printf("\n");	
	}
}
