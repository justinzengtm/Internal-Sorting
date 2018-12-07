#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define ElemType int
#define MaxSize 100
#define MaxData 1000 

/*�������еĴ洢�ṹ*/
typedef struct SqList *PtrlSqList;
struct SqList{
	ElemType arr[MaxSize+1]; /*arr[0]��Ϊ�ڱ�*/
	int length; /*���еĳ���*/
};

/*��������*/
PtrlSqList CreatList(); /*���еĴ���*/
int GetListLength(PtrlSqList P); /*�������еĳ���*/
void Swap(ElemType *a, ElemType *b); /*����Ԫ��*/
void PrintList(PtrlSqList P, int count); /*�������*/
void Insert_Array(PtrlSqList P, int K); /*���в���Ԫ��*/
void AdjustMaxHeap(PtrlSqList P, ElemType i, int length); /*�����ѵ�������,����Ϊ����*/
void Heap_Sort(PtrlSqList P, int N); /*������*/

/*������*/
int main(int agrc, char const* argv[]) 
{
	bool IsFull, IsEmpty;
	int i;
	ElemType InsertData, DeleteItem, data=0;
	
	/*����һ����������*/
	PtrlSqList P=CreatList();
	printf("�봴����������:");
	while (data!=-1) {
		scanf("%d", &data);
		if (data!=-1) {
			Insert_Array(P, data);
		}
	} 
	
	/*��ô������г���*/
	P->length=GetListLength(P);
	
	/*�����������*/
	printf("\n��������Ϊ:");
	PrintList(P, 0); 
	printf("\nP->lenght=%d\n", P->length); 

	/*������*/ 
	printf("\n���������:\n");
	Heap_Sort(P, P->length);
	printf("\n�����������:");
	PrintList(P, 0);
	return 0;
} 

/*���еĴ���*/
PtrlSqList CreatList() 
{
	PtrlSqList P=(PtrlSqList)malloc(sizeof(struct SqList));
	P->arr[0]=0; /*�ڱ�*/
	P->arr[1]=-1;
	
	return P; 
}

/*�������еĳ���*/
int GetListLength(PtrlSqList P) 
{
	int i=1;
	while (P->arr[i]!=-1) {
		i++;
	}

	return (i-1);
}

/*����Ԫ��*/
void Swap(ElemType *a, ElemType *b) 
{
	ElemType t=*a;
	*a=*b;
	*b=t;
} 

/*�������*/
void PrintList(PtrlSqList P, int count) 
{
	int i=1;
	int j; 
	if (count!=0) {
		printf("��%d������:", count);
		while (P->arr[i]!=-1) {
		printf("%d  ", P->arr[i]);
		i++;
		}
	} else {
		while (P->arr[i]!=-1) {
		printf("%d  ", P->arr[i]);
		i++;
		}
	}
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

/*�����ѵ�������,����Ϊ����*/
void AdjustMaxHeap(PtrlSqList P, ElemType i, int length) 
{
	int Head, Max; /*���ú�����ɾ��������һ��*/
	ElemType Tmp; /*��ʱ�����Ǹ�Ҫ����λ�õ�Ԫ��*/
	
	Tmp=P->arr[i]; /*��Ҫ����λ�õ�Ԫ�ظ���һ����ʱ����*/
	for (Head=i; Head*2<=length; Head=Max) {
		Max=Head*2;
		if (Max!=length && P->arr[Max]<P->arr[Max+1]) {
			Max++;
		}
		if (Tmp>P->arr[Max]) {
			break;
		} else {
			P->arr[Head]=P->arr[Max];
		}
	} 
	P->arr[Head]=Tmp;
}

/*������*/
void Heap_Sort(PtrlSqList P, int N) 
{
	int i=0; 
	/*�����һ�����ĸ���㿪ʼ���ϵ���*/
	for (i=N/2; i>0; i--) {
		/*�Ѵ��������е�Ԫ�ص���������*/
		AdjustMaxHeap(P, i, N);
	}
	/*���������Ѻ������*/
	printf("���������Ѻ������Ϊ:");
	PrintList(P, 0); 
	
	printf("\n\n"); /*Ϊ�����۵Ļ���*/
	/*��ʼ������*/
	for (i=N; i>0; i--) {
		//printf("��ʱi=%d\n", i);
		Swap(&P->arr[1], &P->arr[i]);
		/*һ�˶������,�Ѵ������м�������������,����һ�˶�����*/
		AdjustMaxHeap(P, 1, i-1);
		PrintList(P, (N-i+1));
		printf("\n");
	}
}
