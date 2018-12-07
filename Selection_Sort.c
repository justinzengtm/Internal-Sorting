#include <stdio.h>
#include <stdlib.h>
#define MaxSize 20
#define ElemType int

/*�������еĴ洢�ṹ*/
typedef struct SqList *PtrlSqList;
struct SqList {
	ElemType arr[MaxSize+1];
	int length;
};

/*��������*/
void Swap(int i, int Min, PtrlSqList P); /*����Ԫ��λ��*/ 
PtrlSqList CreatList(); /*��ʼ������*/
void Selection_Sort(PtrlSqList P, int N); /*ѡ������*/
void Insert_Array(PtrlSqList P, int K); /*���в���Ԫ��*/
void PrintList(PtrlSqList P); /*�������*/
int GetLength(PtrlSqList P); /*������г���*/

int main(int argc, char const* argv[])
{
	PtrlSqList P=CreatList();
	int data=0;
	
	printf("�봴������:");
	while (data!=-1) {
		scanf("%d", &data);
		Insert_Array(P, data);
	}
	
	/*���ԭ����*/
	printf("\nԭ����Ϊ:");
	PrintList(P);
	
	/*������г���*/
	P->length=GetLength(P);
	printf("\n���г���Ϊ:%d\n", P->length);
	
	/*ѡ������*/
	Selection_Sort(P, P->length);
	
	printf("\nѡ�����������:");
	PrintList(P);
	
}

/*����Ԫ��λ��*/
void Swap(int i, int Min, PtrlSqList P) 
{
	int Tmp=P->arr[i];
	P->arr[i]=P->arr[Min];
	P->arr[Min]=Tmp;	
} 

/*��ʼ������*/
PtrlSqList CreatList()
{
	PtrlSqList P;
	P=(PtrlSqList)malloc(sizeof(struct SqList));
	P->arr[0]=0; /*�ڱ�*/
	P->arr[1]=-1; 
	
	return P;
} 

/*ѡ������*/
void Selection_Sort(PtrlSqList P, int N) 
{
	int i, j, Min;
	
	printf("\nѡ���������:\n");
	for (i=1; i<N; i++) {
		/*һ��ʼ�������п�����������,���ԴӴ����������ó�����ó�Ԫ�ظ�ֵ��Min*/ 
		Min=i;
		/*i+1֮�����Ǵ�������,i+1ǰ�����ź�����*/
		for (j=i+1; j<=N; j++) {
			/*���ĳһλ�õ�Ԫ��С��Minλ�õ�Ԫ��*/
			if (P->arr[j]<P->arr[Min]) {
				/*�ͽ���,Min���СԪ�ص�λ��*/
				Min=j;
			}
		}
		/*��󽻻���СԪ��P->arr[Min]�ʹ��������е���Ԫ�ص�λ�ü�P->arr[i]*/
		if (i==Min) {
			continue;
		} else {
			Swap(i, Min, P); 
			PrintList(P);
			printf("\n");
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
